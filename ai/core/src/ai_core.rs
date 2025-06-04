use std::sync::{Arc, Mutex};

use lib_tcp::tcp_client::AsyncTcpClient;
use tokio::sync::mpsc;

use crate::server_response::ServerResponse;
use crate::ai::GameCommand;
use crate::init::ClientInfos;
use crate::packet::Packet;
use crate::tile::Tile;
use crate::item::Item;
use crate::{CoreError, Result};

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
    client: AsyncTcpClient,
    state: Arc<Mutex<AiState>>,
    send_queue: mpsc::UnboundedSender<Packet>,
    receive_queue: mpsc::UnboundedReceiver<ServerResponse>,
    command_queue: mpsc::UnboundedSender<GameCommand>,
}
