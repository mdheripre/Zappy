use std::sync::Arc;

use lib_tcp::tcp_client::AsyncTcpClient;
use tokio::sync::{mpsc, Mutex};

use crate::ai::{ai_decision, spawn_child_process, AiCommand};
use crate::ai_state::AiState;
use crate::init::init_client;
use crate::packet::{Packet, PacketSender};
use crate::server_response::ServerResponse;
use crate::tile::Tile;
use crate::{CoreError, Result, ServerInfos};

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
    resp_queue: mpsc::UnboundedSender<ServerResponse>,
    resp_rx: mpsc::UnboundedReceiver<ServerResponse>,
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

        let (send_tx_, send_rx_) = mpsc::unbounded_channel::<Packet>();
        let (recv_tx_, recv_rx_) = mpsc::unbounded_channel::<ServerResponse>();
        let (resp_tx_, resp_rx_) = mpsc::unbounded_channel::<ServerResponse>();
        let (cmd_tx_, cmd_rx_) = mpsc::unbounded_channel::<AiCommand>();
        let (err_tx_, err_rx_) = mpsc::unbounded_channel::<String>();

        let state = Arc::new(Mutex::new(AiState::new(client_infos, infos.is_child)));

        Ok(AiCore {
            client: Arc::new(Mutex::new(client)),
            state,
            send_queue: send_tx_,
            recv_queue: recv_rx_,
            cmd_queue: cmd_tx_,
            err_queue: err_rx_,
            resp_queue: resp_tx_,
            resp_rx: resp_rx_,
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
                            let _ = recv_tx.send(parsed).map_err(CoreError::SendChannelErrorSR);
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
        let mut resp_queue = std::mem::replace(&mut self.resp_rx, mpsc::unbounded_channel().1);
        tokio::spawn(async move {
            println!("ai thread starting..");
            loop {
                {
                    let state = ai_state.lock().await;
                    if !state.is_running() {
                        break;
                    }
                }

                let command = ai_decision(&ai_state).await;
                {
                    let mut state = ai_state.lock().await;
                    *state.last_command() = command.clone();
                }
                if let Some(cmd) = command {
                    if ai_cmd_queue.send(cmd).is_err() {
                        break;
                    }
                }
                // block until the server respond, the state has already been updated.
                // You can use the response type for more decision control
                resp_queue.recv().await;
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
                if !state.is_running() {
                    break;
                }
            }

            while let Ok(response) = self.recv_queue.try_recv() {
                self.handle_server_response(response).await?;
            }

            while let Ok(command) = cmd_rx.try_recv() {
                match command {
                    AiCommand::Stop => {
                        let mut state = self.state.lock().await;
                        state.set_running(false);
                        break;
                    }
                    _ => {
                        let packet = command.into();
                        self.send_queue.send(packet)?;
                    }
                }
            }
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
    async fn handle_server_response(&mut self, response: ServerResponse) -> Result<()> {
        println!("Received: {:?}", response);

        let mut state = self.state.lock().await;
        let last_command = state.last_command().clone();
        *state.last_command() = None;
        *state.previous_command() = last_command.clone();
        match &response {
            ServerResponse::Ok => match last_command {
                Some(AiCommand::Take(item)) => {
                    state.inventory().add_item(&item);
                    state.remove_item_from_map(&item);
                }
                Some(AiCommand::Set(item)) => {
                    let _ = state.inventory().remove_item(&item);
                    state.add_item_to_map(&item);
                }
                Some(AiCommand::Forward) => {
                    state.forward();
                }
                Some(AiCommand::Left) => {
                    *state.direction() = state.direction().left();
                }
                Some(AiCommand::Right) => {
                    *state.direction() = state.direction().right();
                }
                Some(AiCommand::Fork) => {
                    spawn_child_process().await?;
                }
                Some(AiCommand::Broadcast(msg)) => {}
                _ => {
                    println!("Received Ok but no command was sent.")
                }
            },
            ServerResponse::Ko => {
                if let Some(AiCommand::Take(item)) = last_command {
                    state.remove_item_from_map(&item);
                }
            }
            ServerResponse::Look(items) => {
                let mut i = 0;
                for item in items {
                    let tile = Tile::new_from_response(item.clone(), i, state.clone());
                    state
                        .world_map()
                        .retain(|t| t.position() != tile.position());
                    state.world_map().push(tile);
                    i += 1;
                }
            }
            ServerResponse::ClientNum(num) => {
                state.set_client_num(*num);
            }
            ServerResponse::Inventory(food) => {
                state.inventory().food = *food as usize;
            }
            ServerResponse::Message(msg) => {
                if let Err(e) = state.broadcast().receive_message(msg) {
                    eprintln!("Error in message received: {}", e);
                }
            }
            ServerResponse::Dead => {
                state.set_running(false);
            }
            _ => {}
        }
        self.resp_queue
            .send(response)
            .map_err(CoreError::SendChannelErrorSR)
    }
}
