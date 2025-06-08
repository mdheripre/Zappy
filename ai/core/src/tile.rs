use crate::item::Item;
use crate::{CoreError, Result};
use std::collections::HashMap;
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
}

impl Tile {
    pub fn position(&self) -> (i32, i32) {
        self.position
    }

    pub fn get_items(&self) -> &HashMap<Item, usize> {
        &self.items
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
}
