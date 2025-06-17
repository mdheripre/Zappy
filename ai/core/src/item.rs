use crate::{CoreError, Result};
use std::fmt;

/// All existing items in the game
///
/// # Variants
/// - `Food` - Unit main ressource.
/// - `Linemate` - Ressource for incantations.
/// - `Deraumere` - Ressource for incantations.
/// - `Sibur` - Ressource for incantations.
/// - `Mendiane` - Ressource for incantations.
/// - `Phiras` - Ressource for incantations.
/// - `Thystame` - Ressource for incantations.
///
/// # Examples
/// ```
/// use crate::...;
///
/// let item = Item::Food;
/// match item {
///     Item::Food => handle_unit,
///     Item::Linemate => handle_unit,
///     Item::Deraumere => handle_unit,
///     Item::Sibur => handle_unit,
///     Item::Mendiane => handle_unit,
///     Item::Phiras => handle_unit,
///     Item::Thystame => handle_unit,
/// }
/// ```
#[derive(Debug, Clone, PartialEq, Eq, Hash)]
pub enum Item {
    Food,
    Linemate,
    Deraumere,
    Sibur,
    Mendiane,
    Phiras,
    Thystame,
}

impl fmt::Display for Item {
    fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {
        let s = match self {
            Item::Food => "food",
            Item::Linemate => "linemate",
            Item::Deraumere => "deraumere",
            Item::Sibur => "sibur",
            Item::Mendiane => "mendiane",
            Item::Phiras => "Phiras",
            Item::Thystame => "thystame"
        };
        write!(f, "{}", s)
    }
}
