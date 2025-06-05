use crate::{CoreError, Result};

/// All existing items
/// 
/// # Variants
/// 
/// - `Food` - Unit main ressource.
/// - `Linemate` - Ressource for incantations.
/// - `Deraumere` - Ressource for incantations.
/// - `Sibur` - Ressource for incantations.
/// - `Mendiane` - Ressource for incantations.
/// - `Phiras` - Ressource for incantations.
/// - `Thystame` - Ressource for incantations.
/// 
/// # Examples
/// 
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
#[derive(Debug, Clone)]
pub enum Item {
    Food,
    Linemate,
    Deraumere,
    Sibur,
    Mendiane,
    Phiras,
    Thystame,
}
