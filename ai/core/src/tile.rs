use crate::item::Item;
use crate::{CoreError, Result};

#[derive(Debug, Clone)]
pub struct Tile {
    pub nb_items: i32,
    pub nb_players: i32,
    pub items: Vec<Item>,
}
