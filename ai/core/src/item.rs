use crate::{CoreError, Result};
use std::fmt;
use std::str::FromStr;

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
            Item::Phiras => "phiras",
            Item::Thystame => "thystame",
        };
        write!(f, "{}", s)
    }
}

impl FromStr for Item {
    type Err = CoreError;

    fn from_str(s: &str) -> Result<Self> {
        match s.to_lowercase().as_str() {
            "food" => Ok(Item::Food),
            "linemate" => Ok(Item::Linemate),
            "deraumere" => Ok(Item::Deraumere),
            "sibur" => Ok(Item::Sibur),
            "mendiane" => Ok(Item::Mendiane),
            "phiras" => Ok(Item::Phiras),
            "thystame" => Ok(Item::Thystame),
            _ => Err(CoreError::InvalidResponse(format!("Unknown item: {}", s))),
        }
    }
}

impl Item {
    /// Get the probability of finding the item on a tile.
    /// # Returns
    /// - `f64` - The probability of finding the item.
    pub fn probability(&self) -> f64 {
        match self {
            Item::Food => 0.5,
            Item::Linemate => 0.3,
            Item::Deraumere => 0.15,
            Item::Sibur => 0.1,
            Item::Mendiane => 0.1,
            Item::Phiras => 0.08,
            Item::Thystame => 0.05,
        }
    }

    /// Get the number of items needed by an  AI.
    /// # Returns
    /// - `i32` - The number of items needed.
    pub fn needed(&self) -> i32 {
        match self {
            Item::Food => 25,
            Item::Linemate => 9,
            Item::Deraumere => 8,
            Item::Sibur => 10,
            Item::Mendiane => 5,
            Item::Phiras => 6,
            Item::Thystame => 1,
        }
    }
}
