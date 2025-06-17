use crate::{ai_core::AiState, item::Item, packet::Packet, CoreError, Result};
use std::{sync::Arc, time::Duration};
use tokio::{sync::Mutex, time::sleep};

/// Possible AI command to the server
///
/// # Variants
/// - see packet enum.
///
/// # Examples
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
    Take(Item),
    Set(Item),
    Incantation,
    Stop,
}

/// Transform AiCommand into Packet
///
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
            AiCommand::Take(item) => Packet::Take(item.to_string()),
            AiCommand::Set(item) => Packet::Set(item.to_string()),
            AiCommand::Incantation => Packet::Incantation,
            AiCommand::Stop => Packet::Forward, //placehoder
        }
    }
}

/// Ai algorithm enty point
///
/// # Arguments
/// - `state` (`&Arc<Mutex<AiState>>`) - pointer to zappy game state.
///
/// # Returns
/// - `Option<AiCommand>` - Return the command to execute.
///
pub async fn ai_decision(state: &Arc<Mutex<AiState>>) -> Option<AiCommand> {
    let mut state = state.lock().await;

    tokio::time::sleep(Duration::from_millis(500)).await;

    if state.last_command.is_some() {
        return None;
    }
    
    if state.is_there_things_in_map() && state.destination.is_none() {
        state.destination = state.chose_destination_tile()
    }
    if let Some(dest) = state.destination.clone() {
        let dest_diff = dest.distance_as_pair(state.position);
        if dest_diff.0 == 0 && dest_diff.1 == 0 {
            if dest.nb_items <= 1 {
                state.destination = None;
            }
            let command = state.chose_best_item(dest.get_items().keys().cloned().collect());
            state.last_command = command.clone();
            return command
        }
        if !state.direction.is_along(dest_diff) {
            let command = Some(state.direction.get_best_turn_to(dest_diff));
            state.last_command = command.clone();
            return command
        }
        state.last_command = Some(AiCommand::Forward);
        return Some(AiCommand::Forward)
    }
    match state.previous_command {
        Some(AiCommand::Look) => {
            state.last_command = Some(AiCommand::Forward);
            Some(AiCommand::Forward)
        },
        _ => {
            state.last_command = Some(AiCommand::Look);
            Some(AiCommand::Look)
        },
    }
}
