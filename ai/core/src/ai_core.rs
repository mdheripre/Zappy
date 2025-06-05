use std::sync::Arc;

use clap::builder::Str;
use lib_tcp::tcp_client::AsyncTcpClient;
use lib_tcp::TcpError;
use tokio::sync::{mpsc, Mutex};
use tokio::time::{sleep, Duration};

use crate::ai::{ai_decision, command_to_packet, AiCommand};
use crate::init::{init_client, ClientInfos};
use crate::item::Item;
use crate::packet::{Packet, PacketSender};
use crate::server_response::ServerResponse;
use crate::tile::Tile;
use crate::{CoreError, Result, ServerInfos};

#[derive(Debug, Clone)]
pub struct AiState {
    pub client_num: i32,
    pub position: (i32, i32),
    pub inventory: Vec<Item>,
    pub world_map: Vec<Vec<Tile>>,
    pub is_running: bool,
}

impl AiState {
    pub fn new(ci: ClientInfos) -> Self {
        Self {
            client_num: ci.client_num,
            position: (ci.x, ci.y),
            inventory: Vec::new(),
            world_map: Vec::new(),
            is_running: true,
        }
    }
}

pub struct AiCore {
    client: Arc<Mutex<AsyncTcpClient>>,
    state: Arc<Mutex<AiState>>,
    send_queue: mpsc::UnboundedSender<Packet>,
    recv_queue: mpsc::UnboundedReceiver<ServerResponse>,
    cmd_queue: mpsc::UnboundedSender<AiCommand>,
    err_queue: mpsc::UnboundedReceiver<String>,
    send_rx: mpsc::UnboundedReceiver<Packet>,
    recv_tx: mpsc::UnboundedSender<ServerResponse>,
    cmd_rx: mpsc::UnboundedReceiver<AiCommand>,
    err_tx: mpsc::UnboundedSender<String>,
}

impl AiCore {
    pub async fn new(infos: &ServerInfos) -> Result<Self> {
        let (client, client_infos) = init_client(infos).await?;

        let (send_tx, send_rx_) = mpsc::unbounded_channel::<Packet>();
        let (recv_tx_, recv_rx) = mpsc::unbounded_channel::<ServerResponse>();
        let (cmd_tx, cmd_rx_) = mpsc::unbounded_channel::<AiCommand>();
        let (err_tx_, err_rx_) = mpsc::unbounded_channel::<String>();

        let state = Arc::new(Mutex::new(AiState::new(client_infos)));

        Ok(AiCore {
            client: Arc::new(Mutex::new(client)),
            state,
            send_queue: send_tx,
            recv_queue: recv_rx,
            cmd_queue: cmd_tx,
            err_queue: err_rx_,
            send_rx: send_rx_,
            recv_tx: recv_tx_,
            cmd_rx: cmd_rx_,
            err_tx: err_tx_,
        })
    }

    pub async fn run(&mut self) -> Result<()> {
        self.sender_thread().await?;
        self.recv_thread().await?;
        self.ai_thread().await?;
        self.core_loop().await
    }

    async fn sender_thread(&mut self) -> Result<()> {
        let sender_client = Arc::clone(&self.client);
        let mut send_rx = std::mem::replace(&mut self.send_rx, mpsc::unbounded_channel().1);
        tokio::spawn(async move {
            println!("sender thread starting..");
            while let Some(packet) = send_rx.recv().await {
                let mut client = sender_client.lock().await;
                if let Err(e) = client.send_packet(packet).await {
                    eprintln!("failed to send packet {}", e);
                    break;
                }
            }
            println!("sender thread closing..");
        });
        Ok(())
    }

    async fn recv_thread(&mut self) -> Result<()> {
        let recv_client = Arc::clone(&self.client);
        let recv_tx = self.recv_tx.clone();
        let err_tx = self.err_tx.clone();
        tokio::spawn(async move {
            println!("recv thread starting..");
            let mut msg_buffer = String::new();
            loop {
                let buffer = {
                    let mut client = recv_client.lock().await;
                    client.try_recv().await
                };
                match buffer {
                    Ok(Some(data)) => {
                        msg_buffer.push_str(&data);
                        while let Some(newline_pos) = msg_buffer.find('\n') {
                            let full_msg = msg_buffer[..newline_pos].to_string();
                            msg_buffer.drain(..=newline_pos);
                            let parsed = ServerResponse::from_string(&full_msg);
                            if recv_tx.send(parsed).is_err() {
                                break;
                            }
                        }
                    }
                    Ok(None) => {
                        continue;
                    }

                    Err(e) => {
                        let _ = err_tx.send(format!("{}", e));
                        break;
                    }
                }
                sleep(Duration::from_millis(10)).await;
            }
            println!("recv thread closing..");
        });
        Ok(())
    }

    async fn ai_thread(&mut self) -> Result<()> {
        let ai_state = Arc::clone(&self.state);
        let ai_cmd_queue = self.cmd_queue.clone();
        tokio::spawn(async move {
            println!("ai thread starting..");
            loop {
                {
                    let state = ai_state.lock().await;
                    if !state.is_running {
                        break;
                    }
                }
                let command = ai_decision(&ai_state).await;
                if let Some(cmd) = command {
                    if ai_cmd_queue.send(cmd).is_err() {
                        break;
                    }
                }
                sleep(Duration::from_millis(10)).await;
            }
            println!("ai thread starting..");
        });
        Ok(())
    }

    async fn core_loop(&mut self) -> Result<()> {
        let mut cmd_rx = std::mem::replace(&mut self.cmd_rx, mpsc::unbounded_channel().1);
        println!("core loop starting..");
        loop {
            if let Ok(error) = self.err_queue.try_recv() {
                return Err(CoreError::ConnectionClosed(error));
            }
            {
                let state = self.state.lock().await;
                if !state.is_running {
                    break;
                }
            }

            while let Ok(response) = self.recv_queue.try_recv() {
                self.handle_server_response(response).await;
            }

            while let Ok(command) = cmd_rx.try_recv() {
                match command {
                    AiCommand::Stop => {
                        let mut state = self.state.lock().await;
                        state.is_running = false;
                        break;
                    }
                    _ => {
                        let packet = command_to_packet(command);
                        self.send_queue.send(packet)?;
                    }
                }
            }
            self.update_state().await;
            sleep(Duration::from_millis(50)).await;
        }
        println!("Ai loop closing..");
        Ok(())
    }

    async fn handle_server_response(&self, response: ServerResponse) {
        println!("Received: {:?}", response);

        let _state = self.state.lock().await;
        match response {
            ServerResponse::Ok => {
                // command executed succeeded
            },
            ServerResponse::Ko => {
                // command executed failed
            }
            _ => {}
        }
    }

    async fn update_state(&self) {
        let _state = self.state.lock().await;
    }

}
