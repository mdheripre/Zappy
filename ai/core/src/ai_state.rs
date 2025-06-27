use std::time::Instant;

use crate::ai::AiCommand;
use crate::ai_direction::Direction;
use crate::broadcast::{Broadcast, Message, MessageType};
use crate::init::ClientInfos;
use crate::inventory::Inventory;
use crate::item::Item;
use crate::tile::Tile;
use rand::Rng;
use tokio::time;

/// Zappy game state
///
/// # Fields  
///
/// - `client_num` (`i32`) - number of available slots.
/// - `position` ((`i32`, `i32`)) - position on the map.
/// - `inventory` (`Inventory`) - inventory content.
/// - `world_map` (`Vec<Tile>`) - map empty at start.
/// - `running` (`bool`) - checker.
/// - `role` (`Role`) - AI role.
/// - `time` (`i32`) - time since the start of the game. (to implement)
/// - `direction` (`Direction`) - current direction.
/// - `last_command` (`Option<AiCommand>`) - last command sent to the server (resets when receiving the response).
/// - `previous_command` (`Option<AiCommand>`) - previous command sent to the server (resets at new command).
/// - `destination` (`Option<Tile>`) - destination tile to reach.
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
///     running: value,
///     role: value,
///     time: value,
///     direction: value,
///     last_command: value,
///     previous_command: value,
///     destination: value,
/// };
/// ```
#[derive(Debug, Clone)]
pub struct AiState {
    client_num: i32,
    position: (i32, i32),
    inventory: Inventory,
    world_map: Vec<Tile>,
    running: bool,
    is_alpha: bool,
    time: i32,
    direction: Direction,
    last_command: Option<AiCommand>,
    previous_command: Option<AiCommand>,
    destination: Option<Tile>,
    broadcast: Broadcast,
    id_getter_queue: u32,
    welcomed: bool,
    teammate_nb: u32,
    message_id: u32,
    team_inventory: Inventory,
    last_item: Option<Item>,
    last_inventory_request: i32,
    need_inventory_request: bool,
    start_time: Instant,
}

impl AiState {
    pub fn new(ci: ClientInfos) -> Self {
        Self {
            client_num: rand::rng().random(),
            position: (ci.x, ci.y),
            inventory: Inventory::new(),
            team_inventory: Inventory::new(),
            world_map: vec![],
            running: true,
            is_alpha: false,
            time: 0,
            direction: Direction::North,
            last_command: None,
            previous_command: None,
            destination: None,
            broadcast: Broadcast::new(),
            id_getter_queue: 0,
            welcomed: false,
            teammate_nb: 1,
            message_id: 0,
            last_item: None,
            last_inventory_request: 0,
            need_inventory_request: false,
            start_time: Instant::now(),
        }
    }

    pub fn running(&self) -> bool {
        self.running
    }

    pub fn running_mut(&mut self) -> &mut bool {
        &mut self.running
    }

    pub fn client_num(&self) -> i32 {
        self.client_num
    }

    pub fn client_num_mut(&mut self) -> &mut i32 {
        &mut self.client_num
    }

    pub fn position(&self) -> (i32, i32) {
        self.position
    }

    pub fn position_mut(&mut self) -> &mut (i32, i32) {
        &mut self.position
    }

    pub fn last_inventory_request(&self) -> i32 {
        self.last_inventory_request
    }

    pub fn last_inventory_request_mut(&mut self) -> &mut i32 {
        &mut self.last_inventory_request
    }

    pub fn need_inventory_request(&self) -> bool {
        self.need_inventory_request
    }

    pub fn need_inventory_request_mut(&mut self) -> &mut bool {
        &mut self.need_inventory_request
    }

    pub fn inventory(&self) -> &Inventory {
        &self.inventory
    }

    pub fn inventory_mut(&mut self) -> &mut Inventory {
        &mut self.inventory
    }

    pub fn team_inventory(&self) -> &Inventory {
        &self.team_inventory
    }

    pub fn team_inventory_mut(&mut self) -> &mut Inventory {
        &mut self.team_inventory
    }

    pub fn world_map(&self) -> &Vec<Tile> {
        &self.world_map
    }

    pub fn world_map_mut(&mut self) -> &mut Vec<Tile> {
        &mut self.world_map
    }

    pub fn last_item(&self) -> &Option<Item> {
        &self.last_item
    }

    pub fn last_item_mut(&mut self) -> &mut Option<Item> {
        &mut self.last_item
    }

    pub fn alpha(&self) -> &bool {
        &self.is_alpha
    }

    pub fn alpha_mut(&mut self) -> &mut bool {
        &mut self.is_alpha
    }

    pub fn id_getter_queue(&self) -> u32 {
        self.id_getter_queue
    }

    pub fn id_getter_queue_mut(&mut self) -> &mut u32 {
        &mut self.id_getter_queue
    }

    pub fn welcomed(&self) -> &bool {
        &self.welcomed
    }

    pub fn welcomed_mut(&mut self) -> &mut bool {
        &mut self.welcomed
    }

    pub fn teammate_nb(&self) -> u32 {
        self.teammate_nb
    }

    pub fn teammate_nb_mut(&mut self) -> &mut u32 {
        &mut self.teammate_nb
    }

    pub fn message_id(&self) -> u32 {
        self.message_id
    }

    pub fn message_id_mut(&mut self) -> &mut u32 {
        &mut self.message_id
    }

    pub fn time(&self) -> i32 {
        self.time
    }

    pub fn time_mut(&mut self) -> &mut i32 {
        &mut self.time
    }

    pub fn inc_time(&mut self) {
        self.time += 1;
    }

    pub fn direction(&self) -> &Direction {
        &self.direction
    }

    pub fn direction_mut(&mut self) -> &mut Direction {
        &mut self.direction
    }

    pub fn last_command(&self) -> &Option<AiCommand> {
        &self.last_command
    }

    pub fn last_command_mut(&mut self) -> &mut Option<AiCommand> {
        &mut self.last_command
    }

    pub fn previous_command(&self) -> &Option<AiCommand> {
        &self.previous_command
    }

    pub fn previous_command_mut(&mut self) -> &mut Option<AiCommand> {
        &mut self.previous_command
    }

    pub fn destination(&self) -> &Option<Tile> {
        &self.destination
    }

    pub fn destination_mut(&mut self) -> &mut Option<Tile> {
        &mut self.destination
    }

    pub fn broadcast(&self) -> &Broadcast {
        &self.broadcast
    }

    pub fn broadcast_mut(&mut self) -> &mut Broadcast {
        &mut self.broadcast
    }

    pub fn uptime(&self) -> time::Duration {
        self.start_time.elapsed()
    }
    /// Make the AI move forward in the current direction
    pub fn forward(&mut self) {
        match self.direction {
            Direction::North => self.position.1 -= 1,
            Direction::South => self.position.1 += 1,
            Direction::East => self.position.0 += 1,
            Direction::West => self.position.0 -= 1,
        }
    }

    /// Choose a destination tile based on the items needed in the inventory
    /// # Returns
    /// - `Option<Tile>` - The tile with the highest value based on the items needed and distance.
    pub fn chose_destination_tile(&self) -> Option<Tile> {
        let mut max_value: f64 = 0.0;
        let mut selected_tile: Option<Tile> = None;
        for tile in &self.world_map {
            let mut value: f64 = 0.0;
            let mut distance: f64 = tile.distance(self.position);
            if distance == 0.0 {
                distance = 0.5
            }
            for item in tile.items() {
                if *item.0 == Item::Food {
                    value += (item.0.needed() as f64 - self.inventory.get_count(item.0) as f64)
                        / (item.0.probability() * distance)
                } else {
                    value += (item.0.needed() as f64 - self.team_inventory.get_count(item.0) as f64)
                        / (item.0.probability() * distance)
                }
            }
            if value > max_value {
                max_value = value;
                selected_tile = Some(tile.clone());
            }
        }
        selected_tile
    }

    /// Choose the best item to take based on the items needed in the inventory
    /// # Arguments
    /// - `items` (`Vec<Item>`) - List of items to choose from.
    /// # Returns
    /// - `Option<AiCommand>` - The command to take the best item.
    pub fn chose_best_item(&self, items: Vec<Item>) -> Option<AiCommand> {
        let mut max_value: f64 = 0.0;
        let mut selected_item: Option<Item> = None;
        for item in items {
            let value: f64 = if item == Item::Food {
                (item.needed() as f64 - self.inventory.get_count(&item) as f64) / item.probability()
            } else {
                (item.needed() as f64 - self.team_inventory.get_count(&item) as f64)
                    / item.probability()
            };
            if value > max_value {
                max_value = value;
                selected_item = Some(item.clone());
            }
        }
        selected_item.as_ref()?;
        selected_item.map(AiCommand::Take)
    }

    /// Check if there are items in the map
    /// # Returns
    /// - `bool` - True if there are items in the map, false otherwise.
    pub fn is_there_things_in_map(&self) -> bool {
        for tile in &self.world_map {
            if !tile.items().is_empty() {
                return true;
            }
        }
        false
    }

    /// Remove a given item from the map
    /// # Arguments
    /// - `item` (`&Item`) - Item to remove from the map.
    pub fn remove_item_from_map(&mut self, item: &Item) {
        for tile in &mut self.world_map {
            if tile.position() == self.position {
                tile.take(item.clone());
                *tile.nb_items_mut() -= 1;
            }
        }
        if let Some(dest) = self.destination.clone() {
            for tile in &self.world_map {
                if tile.position() == dest.position() {
                    self.destination = Some(tile.clone());
                }
            }
        }
    }

    /// Add a given item to the map
    /// # Arguments
    /// - `item` (`&Item`) - Item to add to the map.
    pub fn add_item_to_map(&mut self, item: &Item) {
        for tile in &mut self.world_map {
            if tile.position() == self.position {
                tile.set(item.clone());
                *tile.nb_items_mut() += 1;
            }
        }
        if let Some(dest) = self.destination.clone() {
            for tile in &self.world_map {
                if tile.position() == dest.position() {
                    self.destination = Some(tile.clone());
                }
            }
        }
    }

    /// Create a message with program informations
    /// 
    /// # Arguments
    /// 
    /// - `msg_type` (`MessageType`) - Type of the message.
    /// - `content` (`Option<String>`) - content of the messsage.
    /// 
    /// # Returns
    /// 
    /// - `Message` - Formated message with correct infos.
    /// 
    /// # Examples
    /// 
    /// ```
    /// use crate::...;
    /// 
    /// let _ = new_message();
    /// ```
    pub fn new_message(&self, msg_type: MessageType, content: Option<String>) -> Message {
        Message::new(
            self.client_num() as u32,
            self.message_id(),
            msg_type,
            content,
        )
    }
}
