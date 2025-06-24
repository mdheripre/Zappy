use crate::ai::AiCommand;
use crate::ai_direction::Direction;
use crate::ai_role::Role;
use crate::broadcast::Broadcast;
use crate::init::ClientInfos;
use crate::inventory::Inventory;
use crate::item::Item;
use crate::tile::Tile;

/// Zappy game state
///
/// # Fields  
///
/// - `client_num` (`i32`) - number of available slots.
/// - `position` ((`i32`, `i32`)) - position on the map.
/// - `inventory` (`Inventory`) - inventory content.
/// - `world_map` (`Vec<Tile>`) - map empty at start.
/// - `is_running` (`bool`) - checker.
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
///     is_running: value,
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
    is_child: bool,
    client_num: i32,
    position: (i32, i32),
    inventory: Inventory,
    world_map: Vec<Tile>,
    is_running: bool,
    role: Role,
    time: i32,
    direction: Direction,
    last_command: Option<AiCommand>,
    previous_command: Option<AiCommand>,
    destination: Option<Tile>,
    broadcast: Broadcast,
}

impl AiState {
    pub fn new(ci: ClientInfos, is_child: bool) -> Self {
        Self {
            is_child,
            client_num: ci.client_num,
            position: (ci.x, ci.y),
            inventory: Inventory::new(),
            world_map: vec![],
            is_running: true,
            role: match ci.client_num {
                1 => Role::Alpha,
                2..=5 => Role::Beta,
                _ => Role::Gamma,
            },
            time: 0,
            direction: Direction::North,
            last_command: None,
            previous_command: None,
            destination: None,
            broadcast: Broadcast::new(123),
        }
    }

    pub fn is_running(&self) -> bool {
        self.is_running
    }

    pub fn set_running(&mut self, new: bool) {
        self.is_running = new
    }
    pub fn is_child(&self) -> bool {
        self.is_child
    }

    pub fn client_num(&self) -> i32 {
        self.client_num
    }

    pub fn set_client_num(&mut self, new: i32) {
        self.client_num = new
    }

    pub fn position(&self) -> (i32, i32) {
        self.position
    }

    pub fn set_position(&mut self, new: (i32, i32)) {
        self.position = new
    }

    pub fn inventory(&mut self) -> &mut Inventory {
        &mut self.inventory
    }

    pub fn world_map(&mut self) -> &mut Vec<Tile> {
        &mut self.world_map
    }

    pub fn role(&mut self) -> &mut Role {
        &mut self.role
    }

    pub fn time(&mut self) -> i32 {
        self.time
    }

    pub fn direction(&mut self) -> &mut Direction {
        &mut self.direction
    }

    pub fn last_command(&mut self) -> &mut Option<AiCommand> {
        &mut self.last_command
    }

    pub fn previous_command(&mut self) -> &mut Option<AiCommand> {
        &mut self.previous_command
    }

    pub fn destination(&mut self) -> &mut Option<Tile> {
        &mut self.destination
    }

    pub fn broadcast(&mut self) -> &mut Broadcast {
        &mut self.broadcast
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
            for item in tile.get_items() {
                value += (item.0.needed() as f64 - self.inventory.get_count(item.0) as f64)
                    / (item.0.probability() * distance)
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
            let value: f64 = (item.needed() as f64 - self.inventory.get_count(&item) as f64)
                / item.probability();
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
            if !tile.get_items().is_empty() {
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
                tile.nb_items -= 1;
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
                tile.nb_items += 1;
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
}
