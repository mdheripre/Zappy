use crate::item::Item;

/// Inventory struct to hold the resources collected by an AI player.
///
/// # Fields
///
/// - `food` - Amount of food collected.
/// - `linemate` - Amount of linemate collected.
/// - `deraumere` - Amount of deraumere collected.
/// - `sibur` - Amount of sibur collected.
/// - `mendiane` - Amount of mendiane collected.
/// - `phiras` - Amount of phiras collected.
/// - `thystame` - Amount of thystame collected.
///
#[derive(Clone, Debug)]
pub struct Inventory {
    pub food: usize,
    pub linemate: usize,
    pub deraumere: usize,
    pub sibur: usize,
    pub mendiane: usize,
    pub phiras: usize,
    pub thystame: usize,
}

impl Inventory {
    pub fn new() -> Self {
        Inventory {
            food: 0,
            linemate: 0,
            deraumere: 0,
            sibur: 0,
            mendiane: 0,
            phiras: 0,
            thystame: 0,
        }
    }

    /// Add an item to the inventory.
    /// # Arguments
    /// - `item` - The item to add to the inventory.
    pub fn add_item(&mut self, item: &Item) {
        match item {
            Item::Food => self.food += 1,
            Item::Linemate => self.linemate += 1,
            Item::Deraumere => self.deraumere += 1,
            Item::Sibur => self.sibur += 1,
            Item::Mendiane => self.mendiane += 1,
            Item::Phiras => self.phiras += 1,
            Item::Thystame => self.thystame += 1,
        }
    }

    /// Remove an item from the inventory.
    /// # Arguments
    /// - `item` - The item to remove from the inventory.
    /// # Returns
    /// - `Result<(), String>` - Ok if the item was removed, Err if the item was not found or not enough items to remove.
    pub fn remove_item(&mut self, item: &Item) -> Result<(), String> {
        match item {
            Item::Food if self.food > 0 => {
                self.food -= 1;
                Ok(())
            }
            Item::Linemate if self.linemate > 0 => {
                self.linemate -= 1;
                Ok(())
            }
            Item::Deraumere if self.deraumere > 0 => {
                self.deraumere -= 1;
                Ok(())
            }
            Item::Sibur if self.sibur > 0 => {
                self.sibur -= 1;
                Ok(())
            }
            Item::Mendiane if self.mendiane > 0 => {
                self.mendiane -= 1;
                Ok(())
            }
            Item::Phiras if self.phiras > 0 => {
                self.phiras -= 1;
                Ok(())
            }
            Item::Thystame if self.thystame > 0 => {
                self.thystame -= 1;
                Ok(())
            }
            _ => Err(format!("Cannot remove item: {:?}", item)),
        }
    }

    /// Get the count of a specific item in the inventory.
    /// # Arguments
    /// - `item` - The item to get the count for.
    /// # Returns
    /// - `usize` - The count of the item in the inventory.
    pub fn get_count(&self, item: &Item) -> usize {
        match item {
            Item::Food => self.food,
            Item::Linemate => self.linemate,
            Item::Deraumere => self.deraumere,
            Item::Sibur => self.sibur,
            Item::Mendiane => self.mendiane,
            Item::Phiras => self.phiras,
            Item::Thystame => self.thystame,
        }
    }

    pub fn as_broadcast(&self) -> String {
        let mut str: String = String::new();
        str.push_str(&self.linemate.to_string());
        str.push(':');
        str.push_str(&self.deraumere.to_string());
        str.push(':');
        str.push_str(&self.sibur.to_string());
        str.push(':');
        str.push_str(&self.mendiane.to_string());
        str.push(':');
        str.push_str(&self.phiras.to_string());
        str.push(':');
        str.push_str(&self.thystame.to_string());
        str
    }
    
    pub fn is_ready(&self) -> bool {
        if self.linemate < 9 {
            return false;
        }
        if self.deraumere < 8 {
            return false;
        }
        if self.sibur < 10 {
            return false;
        }
        if self.mendiane < 5 {
            return false;
        }
        if self.phiras < 6 {
            return false;
        }
        if self.thystame < 1 {
            return false;
        }
        true
    }
}
