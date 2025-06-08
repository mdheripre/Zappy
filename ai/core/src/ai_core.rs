use std::sync::Arc;

use lib_tcp::tcp_client::AsyncTcpClient;
use tokio::sync::{mpsc, Mutex};

use crate::ai::{ai_decision, AiCommand};
use crate::init::{init_client, ClientInfos};
use crate::item::Item;
use crate::packet::{Packet, PacketSender};
use crate::server_response::ServerResponse;
use crate::tile::Tile;
use crate::{CoreError, Result, ServerInfos};

/// Zappy game state
///
/// # Fields
///
/// - `client_num` (`i32`) - number of available slots.
/// - `position` (`(i32`) - position on the map.
/// - `inventory` (`Vec<Item>`) - inventory content.
/// - `world_map` (`Vec<Vec<Tile>>`) - map empty at start.
/// - `is_running` (`bool`) - checker.
///
/// # Examples
///
/// ```
/// use crate::...;
///
/// let s = AiState {
///     client_num: value,
///     position: value,
///     inventory: value,
///     world_map: value,
///     is_running: value,
/// };
/// ```
#[derive(Debug, Clone)]
pub struct AiState {
    pub client_num: i32,
    pub position: (i32, i32),
    pub inventory: Vec<Item>,
    pub world_map: Vec<Tile>,
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

/// Ai core structure for thread communication and main loop
///
/// # Fields
///
/// - `client` (`Arc<Mutex<AsyncTcpClient>>`) - TCP client.
/// - `state` (`Arc<Mutex<AiState>>`) - zappy game state.
/// - `send_queue` (`mpsc`) - Packet sender.
/// - `recv_queue` (`mpsc`) - ServerResponse receiver.
/// - `cmd_queue` (`mpsc`) - AiCommand sender.
/// - `err_queue` (`mpsc`) - Error receiver.
/// - `send_rx` (`mpsc`) - Packet receiver.
/// - `recv_tx` (`mpsc`) - ServerResponse sender.
/// - `cmd_rx` (`mpsc`) - AiCommand receiver.
/// - `err_tx` (`mpsc`) - Error sender.
///
/// # Examples
///
/// ```
/// use crate::...;
///
/// let s = AiCore {
///     client: value,
///     state: value,
///     send_queue: value,
///     recv_queue: value,
///     cmd_queue: value,
///     err_queue: value,
///     send_rx: value,
///     recv_tx: value,
///     cmd_rx: value,
///     err_tx: value,
/// };
/// ```
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
    /// AiCore constructor
    ///
    /// # Arguments
    /// - `infos` (`&ServerInfos`) - infos given by the server.
    ///
    /// # Returns
    /// - `Result<Self>` - AiCore struct.
    ///
    /// # Errors
    /// Tcp errors.
    ///
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

    /// launch the program core
    /// lauch sender / recv / ai threads and core loop
    ///
    /// # Errors
    /// CoreError.
    ///
    pub async fn run(&mut self) -> Result<()> {
        self.sender_thread().await?;
        self.recv_thread().await?;
        self.ai_thread().await?;
        self.core_loop().await
    }

    /// thread to send packets to the server
    /// clone a pointer to the TcpClient, read the Packet channel and send Packet to the server
    ///
    /// # Errors
    /// CoreError.
    ///
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

    /// thread to receive packet from the server
    /// clone a pointer to the TcpClient, read the TcpClient socket, send data in the Packet channel
    /// If an Error occurs, it is propagated throught the error channel
    ///
    /// # Errors
    /// CoreError.
    ///
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
            }
            println!("recv thread closing..");
        });
        Ok(())
    }

    /// thread to generate Ai decisions
    /// clone a pointer to the TcpClient, wait for a command to be decided by the AI and send it on the AiCommand channel
    ///
    /// # Errors
    /// CoreError.
    ///
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
            }
            println!("ai thread starting..");
        });
        Ok(())
    }

    /// main loop that allow communication between threads and update the zappy game state
    /// It alose reads the ServerResponse channel and handle it (self.handle_server_response)
    ///
    /// # Errors
    /// CoreError.
    ///
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
                        let packet = command.into();
                        self.send_queue.send(packet)?;
                    }
                }
            }
            self.update_state().await;
        }
        println!("Ai loop closing..");
        Ok(())
    }

    /// Handle server responses
    /// Take a server response and send it to the AI thread throught a channel
    /// # Arguments
    ///
    /// - `response` (`ServerResponse`) - ServerResponse to handle.
    ///
    async fn handle_server_response(&self, response: ServerResponse) {
        println!("Received: {:?}", response);

        let _state = self.state.lock().await;
        match response {
            ServerResponse::Ok => {
                // command executed succeeded
            }
            ServerResponse::Ko => {
                // command executed failed
            }
            _ => {}
        }
    }

    /// update the zappy game state
    ///
    async fn update_state(&self) {
        let _state = self.state.lock().await;
    }
}
