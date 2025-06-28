use crate::ai_direction::Direction;
use crate::broadcast::Message;
use crate::tile::Tile;
use crate::{ai_state::AiState, broadcast::MessageType, item::Item, packet::Packet, Result};
use std::{env, process::Stdio, sync::Arc};
use tokio::sync::MutexGuard;
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
    Broadcast(Message),
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
            AiCommand::Broadcast(msg) => Packet::Broadcast(msg.to_string()),
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
//        .stdin(Stdio::null())
//        .stdout(Stdio::null())
//        .stderr(Stdio::null())
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

    if state.last_command().is_some() || state.ready_to_incant() {
        return None;
    }
    if !*state.welcomed() && state.time() >= 30 {
        *state.welcomed_mut() = true;
        *state.alpha_mut() = true;
    }
    if is_dying(&mut state) {
        let msg = state.new_message(MessageType::Dead, None);
        return forward_command(&mut state, Some(AiCommand::Broadcast(msg)));
    }
    if state.gathering() {
        return interpret_broadcast(&mut state);
    }
    update_destination(&mut state);
    if let Some(command) = send_hello(&mut state)
        .or_else(|| interpret_broadcast(&mut state))
        .or_else(|| br_gather(&mut state))
        .or_else(|| request_inventory(&mut state))
        .or_else(|| dead_command(&mut state))
        .or_else(|| {
            state
                .last_item()
                .clone()
                .and_then(|item| broadcast_taken_item(&mut state, item))
        })
        .or_else(|| fork_new_ai(&mut state))
        .or_else(|| {
            state
                .destination()
                .clone()
                .and_then(|dest| get_command_to_destination(&mut state, dest))
        })
        .or_else(|| look_or_forward(&mut state))
    {
        return forward_command(&mut state, Some(command));
    }
    None
}

pub fn forward_command(
    state: &mut MutexGuard<'_, AiState>,
    command: Option<AiCommand>,
) -> Option<AiCommand> {
    if let Some(AiCommand::Broadcast(_)) = command.clone() {
        *state.message_id_mut() += 1;
    }
    *state.last_command_mut() = command.clone();
    state.inc_time();
    command
}

fn dead_command(state: &mut MutexGuard<'_, AiState>) -> Option<AiCommand> {
    match is_dying(state) {
        true => {
            let msg = state.new_message(MessageType::Dead, None);
            forward_command(state, Some(AiCommand::Broadcast(msg)))
        }
        false => None
    }
}

fn is_dying(state: &mut MutexGuard<'_, AiState>) -> bool {
    let current_time = state.uptime().as_millis() as u64;
    let cooldown = 5000;

    let last_dead_message= state.broadcast().sent().iter()
        .filter(|msg| matches!(msg.0.msg_type(), MessageType::Dead))
        .map(|msg| msg.1)
        .max();

    match last_dead_message {
        Some(last_time) => {
            let time_since_last = current_time - last_time;
            state.inventory().food() <= 1 && time_since_last >= cooldown
        }
        None => {
            state.inventory().food() <= 1
        }
    }
}

pub fn interpret_broadcast(state: &mut MutexGuard<'_, AiState>) -> Option<AiCommand> {
    while !state.broadcast().get_received_messages().is_empty() {
        if let Some(msg) = state.broadcast_mut().pop_received() {
            match msg.1.msg_type() {
                MessageType::Hello => {
                    *state.teammate_nb_mut() += 1;
                    if *state.alpha() {
                        let mut str: String = state.teammate_nb().to_string();
                        str.push(':');
                        str.push_str(state.team_inventory().as_broadcast().as_str());
                        let output_msg = state.new_message(MessageType::Welcome, Some(str));
                        return forward_command(
                            state,
                            Some(AiCommand::Broadcast(output_msg)),
                        );
                    } else {
                        *state.id_getter_queue_mut() += 1;
                    }
                }
                MessageType::Welcome => {
                    if !*state.welcomed() && *state.id_getter_queue_mut() == 0 {
                        *state.welcomed_mut() = true;
                        if let Some(content) = msg.1.content() {
                            let parts: Vec<usize> =
                                content.split(':').map(|x| x.parse().unwrap()).collect();
                            *state.team_inventory_mut().linemate_mut() = parts[1];
                            *state.team_inventory_mut().deraumere_mut() = parts[2];
                            *state.team_inventory_mut().sibur_mut() = parts[3];
                            *state.team_inventory_mut().mendiane_mut() = parts[4];
                            *state.team_inventory_mut().phiras_mut() = parts[5];
                            *state.team_inventory_mut().thystame_mut() = parts[6];
                        }
                    }
                    if state.id_getter_queue() != 0 {
                        *state.id_getter_queue_mut() -= 1;
                    }
                }
                MessageType::Item => {
                    if let Some(content) = msg.1.content() {
                        if let Ok(item) = content.parse::<Item>() {
                            state.team_inventory_mut().add_item(&item);
                        }
                    }
                }
                MessageType::Gather => {
                    println!("gather received AAAAAAAAAAAAA {:?}", state.client_num());
                    *state.gathering_mut() = true;
                    return match msg.0 {
                        0 => {
                            *state.ready_to_incant_mut() = true;
                            forward_command(state, Some(AiCommand::Broadcast(state.new_message(MessageType::Here, None))))
                        },
                        1 | 2 | 8 => forward_command(state, Some(AiCommand::Forward)),
                        3 | 4 | 5 => forward_command(state, Some(AiCommand::Left)),
                        6 | 7 => forward_command(state, Some(AiCommand::Right)),
                        _ => forward_command(state, Some(AiCommand::Left))
                    }
                }
                MessageType::Here => {
                    *state.ready_nb_mut() += 1;
                }
                MessageType::Dead => {}
                MessageType::Need => {}
            }
        }
    }
    None
}

pub fn send_hello(state: &mut MutexGuard<'_, AiState>) -> Option<AiCommand> {
    if state.time() == 0 {
        if !state.broadcast().get_received_messages().is_empty() {
            state.broadcast_mut().clear();
        }
        let msg = state.new_message(MessageType::Hello, None);
        state.inc_time();
        *state.last_command_mut() = Some(AiCommand::Broadcast(msg.clone()));
        return Some(AiCommand::Broadcast(msg));
    }
    None
}

pub fn get_command_to_destination(
    state: &mut MutexGuard<'_, AiState>,
    dest: Tile,
) -> Option<AiCommand> {
    let dest_diff = dest.distance_as_pair(state.position());
    if dest_diff.0 == 0 && dest_diff.1 == 0 {
        if dest.nb_items() <= 1 {
            *state.destination_mut() = None;
        }
        let command = state.chose_best_item(dest.items().keys().cloned().collect());
        return forward_command(state, command);
    }
    if !state.direction().is_along(dest_diff) {
        let command = Some(state.direction().get_best_turn_to(dest_diff));
        return forward_command(state, command);
    }
    forward_command(state, Some(AiCommand::Forward))
}

pub fn update_destination(state: &mut MutexGuard<'_, AiState>) {
    if state.is_there_things_in_map() && state.destination().is_none() {
        *state.destination_mut() = state.chose_destination_tile()
    }
}

pub fn look_or_forward(state: &mut MutexGuard<'_, AiState>) -> Option<AiCommand> {
    match state.previous_command() {
        Some(AiCommand::Look) => { 
            let rand_nb: u32 = rand::random_range(0..=2);
            match rand_nb {
                0 => forward_command(state, Some(AiCommand::Forward)),
                1 => forward_command(state, Some(AiCommand::Left)),
                _ => forward_command(state, Some(AiCommand::Right)),
            }
        },
        _ => forward_command(state, Some(AiCommand::Look)),
    }
}

pub fn broadcast_taken_item(state: &mut MutexGuard<'_, AiState>, item: Item) -> Option<AiCommand> {
    *state.last_item_mut() = None;
    let msg = state.new_message(MessageType::Item, Some(item.to_string()));
    forward_command(state, Some(AiCommand::Broadcast(msg)))
}

pub fn fork_new_ai(state: &mut MutexGuard<'_, AiState>) -> Option<AiCommand> {
    if *state.teammate_nb_mut() <= 10 && state.inventory().food() >= 3 && *state.alpha() {
        *state.need_inventory_request_mut() = true;
        return forward_command(state, Some(AiCommand::Fork));
    }
    None
}

pub fn br_gather(state: &mut MutexGuard<'_, AiState>) -> Option<AiCommand> {
    if *state.alpha() && state.team_inventory().is_ready() {
        match state.previous_command() {
            Some(AiCommand::Broadcast(_)) => {
                return forward_command(state, Some(AiCommand::Look));
            }
            _ => {
                let message = state.new_message(MessageType::Gather, None);
                return forward_command(state, Some(AiCommand::Broadcast(message)));
            }
        }
    }
    None
}

pub fn request_inventory(state: &mut MutexGuard<'_, AiState>) -> Option<AiCommand> {
    if state.time() - state.last_inventory_request() >= 10 || state.need_inventory_request() {
        *state.last_inventory_request_mut() = state.time() + 1;
        *state.need_inventory_request_mut() = false;
        return forward_command(state, Some(AiCommand::Inventory));
    }
    None
}
