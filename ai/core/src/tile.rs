use crate::item::Item;
use crate::{CoreError, Result};
/// Content of a Tile
///
/// # Fields
///
/// - `nb_items` (`i32`) - items on the tile.
/// - `nb_players` (`i32`) - players on the tile.
/// - `items` (`Vec<Item>`) - actual items on the tile.
///
/// # Examples
///
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
    pub nb_items: i32,
    pub nb_players: i32,
    pub items: Vec<Item>,
}
