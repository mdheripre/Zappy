use crate::{ai_state::AiState, broadcast::Message, broadcast::MessageType, item::Item, packet::Packet, Result};
use std::{env, process::Stdio, sync::Arc, time::Duration};
use tokio::{process::Command, sync::Mutex};

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

/// create a child process with a new env variable so the program can recognize his condition
///
/// # Errors
/// child process creation might fail and return a CoreError::
///
/// # Examples
///
/// ```no_run
/// use crate::...;
///
/// async {
///   let result = spawn_child_process().await;
/// };
/// ```
pub async fn spawn_child_process() -> Result<()> {
    let exe_path = env::current_exe()?;
    let args: Vec<String> = std::env::args().skip(1).collect();
    let child = Command::new(exe_path)
        .args(&args)
        .env("IS_CHILD", "1")
        .stdin(Stdio::null())
        .stdout(Stdio::null())
        .stderr(Stdio::null())
        .spawn()?;

    println!("Spawned child with PID: {:?}", child.id());
    Ok(())
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

    if state.last_command().is_some() {
        return None;
    }
    if state.time() == 0 {
        if !state.broadcast().get_received_messages().is_empty() {
            state.broadcast().clear();
        }
        let msg = Message::new(*state.client_num() as u32, *state.message_id(), MessageType::Hello, None);
        state.inc_time();
        *state.last_command() = Some(AiCommand::Broadcast(msg.to_string()));
        state.broadcast().send_message(msg.clone());
        return Some(AiCommand::Broadcast(msg.to_string()));
    }
    while !state.broadcast().get_received_messages().is_empty() {
        if let Some(msg) = state.broadcast().pop_received() {
            match msg.msg_type() {
                MessageType::Hello => {
                    *state.teammate_nb() += 1;
                    if *state.alpha() {
                        let mut str: String = String::from(state.teammate_nb().to_string());
                        str.push(':');
                        str.push_str(state.team_inventory().as_broadcast().as_str());
                        let output_msg = Message::new(*state.client_num() as u32, *state.message_id(), MessageType::Welcome, Some(str));
                        *state.last_command() = Some(AiCommand::Broadcast(output_msg.to_string()));
                        return Some(AiCommand::Broadcast(output_msg.to_string()));
                    } else {
                        *state.id_getter_queue() += 1;
                    }
                }
                MessageType::Welcome => {
                    if !*state.welcomed() && *state.id_getter_queue() == 0 {
                        if *state.alpha() && state.time() <= 10 {
                            println!("Now a beta");
                            *state.alpha() = false;
                        }
                        if let Some(content) = msg.content() {
                            let parts: Vec<u32> = content.split(':').map(|x| x.parse().unwrap()).collect();
                            *state.client_num() = parts[0] as i32;
                            state.team_inventory().linemate = parts[1] as usize;
                            state.team_inventory().deraumere = parts[2] as usize;
                            state.team_inventory().sibur = parts[3] as usize;
                            state.team_inventory().mendiane = parts[4] as usize;
                            state.team_inventory().phiras = parts[5] as usize;
                            state.team_inventory().thystame = parts[6] as usize;
                        }
                    }
                    if *state.id_getter_queue() != 0 {
                        *state.id_getter_queue() -= 1;
                    }
                }
                MessageType::Gather => {}
                MessageType::Dead => {}
                MessageType::Need => {}
            }
        }
    }
    state.inc_time();
    if state.is_there_things_in_map() && state.destination().is_none() {
        *state.destination() = state.chose_destination_tile()
    }
    if let Some(dest) = state.destination().clone() {
        let dest_diff = dest.distance_as_pair(state.position());
        if dest_diff.0 == 0 && dest_diff.1 == 0 {
            if dest.nb_items <= 1 {
                *state.destination() = None;
            }
            let command = state.chose_best_item(dest.get_items().keys().cloned().collect());
            *state.last_command() = command.clone();
            return command;
        }
        if !state.direction().is_along(dest_diff) {
            let command = Some(state.direction().get_best_turn_to(dest_diff));
            *state.last_command() = command.clone();
            return command;
        }
        *state.last_command() = Some(AiCommand::Forward);
        return Some(AiCommand::Forward);
    }
    match state.previous_command() {
        Some(AiCommand::Look) => {
            *state.last_command() = Some(AiCommand::Forward);
            Some(AiCommand::Forward)
        }
        _ => {
            *state.last_command() = Some(AiCommand::Look);
            Some(AiCommand::Look)
        }
    }
}
