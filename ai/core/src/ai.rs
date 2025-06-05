use crate::{ai_core::AiState, item::Item, packet::Packet, CoreError, Result};
use std::convert::Into;
use std::sync::Arc;
use tokio::sync::{mpsc, Mutex};

/// Possible AI command to the server
///
/// # Variants
///
/// - see packet enum.
///
/// # Examples
///
/// ```
/// use crate::...;
///
/// let aicommand = AiCommand::Forward;
/// match aicommand {
///     AiCommand::Forward => handle_unit,
///     AiCommand::Right => handle_unit,
///     AiCommand::Left => handle_unit,
///     AiCommand::Look => handle_unit,
///     AiCommand::Inventory => handle_unit,
///     AiCommand::Broadcast(v0) => handle_tuple,
///     AiCommand::ConnectNbr => handle_unit,
///     AiCommand::Fork => handle_unit,
///     AiCommand::Eject => handle_unit,
///     AiCommand::Take(v0) => handle_tuple,
///     AiCommand::Set(v0) => handle_tuple,
///     AiCommand::Incantation => handle_unit,
///     AiCommand::Stop => handle_unit,
/// }
/// ```
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

/// Transform AiCommand into Packet
///
/// # Arguments
///
/// - `command` (`AiCommand`)
///
/// # Returns
///
/// - `Self`.
///
/// # Examples
///
/// ```
/// use crate::...;
///
/// let command = AiCommand::Forward;
/// let packet = command.into();
/// ```
impl From<AiCommand> for Packet {
    fn from(command: AiCommand) -> Self {
        match command {
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

/// Ai algorithm enty point
///
/// # Arguments
///
/// - `state` (`&Arc<Mutex<AiState>>`) - pointer to zappy game state.
///
/// # Returns
///
/// - `Option<AiCommand>` - Return the command to execute.
///
/// # Examples
///
/// ```no_run
/// use crate::...;
///
/// async {
///   let result = ai_decision().await;
/// };
/// ```
pub async fn ai_decision(state: &Arc<Mutex<AiState>>) -> Option<AiCommand> {
    let state = state.lock().await;

    if state.inventory.is_empty() {
        Some(AiCommand::Look)
    } else {
        Some(AiCommand::Forward)
    }
}
