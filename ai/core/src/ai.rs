use crate::{ai_core::AiState, item::Item, packet::Packet, CoreError, Result};
use std::convert::Into;
use std::sync::Arc;
use tokio::sync::{mpsc, Mutex};

#[derive(Debug, Clone)]
pub enum AiCommand {
    Forward,
    Right,
    Left,
    Look,
    Inventory,
    Broadcast(String),
    ConnectNbr,
    Fork,
    Eject,
    Take(String),
    Set(String),
    Incantation,
    Stop,
}

impl Into<Packet> for AiCommand {
    fn into(self) -> Packet {
        match self {
            AiCommand::Forward => Packet::Forward,
            AiCommand::Right => Packet::Right,
            AiCommand::Left => Packet::Left,
            AiCommand::Look => Packet::Look,
            AiCommand::Inventory => Packet::Inventory,
            AiCommand::ConnectNbr => Packet::ConnectNbr,
            AiCommand::Broadcast(msg) => Packet::Broadcast(msg),
            AiCommand::Fork => Packet::Fork,
            AiCommand::Eject => Packet::Eject,
            AiCommand::Take(item) => Packet::Take(item),
            AiCommand::Set(item) => Packet::Take(item),
            AiCommand::Incantation => Packet::Incantation,
            AiCommand::Stop => Packet::Forward, //placehoder
        }
    }
}

pub async fn ai_decision(state: &Arc<Mutex<AiState>>) -> Option<AiCommand> {
    let state = state.lock().await;

    if state.inventory.is_empty() {
        Some(AiCommand::Look)
    } else {
        Some(AiCommand::Forward)
    }
}
