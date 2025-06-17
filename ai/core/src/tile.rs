use crate::item::Item;
use crate::{CoreError, Result};
use std::collections::HashMap;
use crate::ai_core::AiState;

/// Content of a Tile
///
/// # Fields
/// - `nb_items` (`i32`) - items on the tile.
/// - `nb_players` (`i32`) - players on the tile.
/// - `items` (`HashMap<Item, usize>`) - actual items on the tile.
///
/// # Examples
/// ```
/// use crate::...;
///
/// let s = Tile {
///     nb_items: value,
///     nb_players: value,
///     items: value,
/// };
/// ```
#[derive(Debug, Clone)]
pub struct Tile {
    position: (i32, i32),
    pub nb_items: i32,
    pub nb_players: i32,
    items: HashMap<Item, usize>,
    look_time: i32,
}

impl Tile {
    pub fn new(time: i32) -> Self {
        Tile {
            position: (0, 0),
            nb_items: 0,
            nb_players: 0,
            items: HashMap::new(),
            look_time: time,
        }
    }

    pub fn new_from_response(string: String, tile_number: i32, ai_state: AiState) -> Self {
        let mut tile = Tile::new(ai_state.time);
        let mut y = ((tile_number as f64).sqrt().floor() as i32);
        let mut x = (tile_number - y * (y + 1));
        match ai_state.direction {
            crate::ai_direction::Direction::North => {
                tile.set_position((ai_state.position.0 + x, ai_state.position.1 - y));
            }
            crate::ai_direction::Direction::East => {
                tile.set_position((ai_state.position.0 + y, ai_state.position.1 + x));
            },
            crate::ai_direction::Direction::South => {
                tile.set_position((ai_state.position.1 - x, ai_state.position.1 + y));
            },
            crate::ai_direction::Direction::West => {
                tile.set_position((ai_state.position.1 - y, ai_state.position.1 - x));
            },
        }
        for item in string.split(' ') {
            if item == "player" {
                tile.nb_players += 1;
                continue;
            } else if let Ok(item_enum) = item.parse::<Item>() {
                tile.nb_items += 1;
                tile.set(item_enum);
            }
        }
        tile
    }

    pub fn position(&self) -> (i32, i32) {
        self.position
    }

    pub fn set_position(&mut self, pos: (i32, i32)) {
        self.position = pos;
    }

    pub fn clear_items(&mut self) {
        self.items.clear();
        self.nb_items = 0;
    }

    pub fn get_items(&self) -> &HashMap<Item, usize> {
        &self.items
    }

    pub fn get_look_time(&self) -> i32 {
        self.look_time
    }
    
    pub fn set_look_time(&mut self, time: i32) {
        self.look_time = time;
    }
    
    pub fn set(&mut self, item: Item) {
        *self.items.entry(item).or_insert(0) += 1;
    }

    pub fn take(&mut self, item: Item) {
        if let Some(count) = self.items.get_mut(&item) {
            if *count > 1 {
                *count -= 1;
            } else {
                self.items.remove(&item);
            }
        }
    }
    
    pub fn distance(&self, pos: (i32, i32)) -> f64 {
        let dx = (self.position.0 - pos.0).abs();
        let dy = (self.position.1 - pos.1).abs();
        (dx + dy) as f64
    }
    
    pub fn distance_as_pair(&self, pos: (i32, i32)) -> (i32, i32) {
        (self.position.0 - pos.0, self.position.1 - pos.1)
    }
}
