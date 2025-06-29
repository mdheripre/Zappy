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
    food: usize,
    linemate: usize,
    deraumere: usize,
    sibur: usize,
    mendiane: usize,
    phiras: usize,
    thystame: usize,
}

impl Inventory {
    pub fn new() -> Self {
        Inventory {
            food: 10,
            linemate: 0,
            deraumere: 0,
            sibur: 0,
            mendiane: 0,
            phiras: 0,
            thystame: 0,
        }
    }

    pub fn food(&self) -> usize {
        self.food
    }

    pub fn food_mut(&mut self) -> &mut usize {
        &mut self.food
    }

    pub fn linemate(&self) -> usize {
        self.linemate
    }

    pub fn linemate_mut(&mut self) -> &mut usize {
        &mut self.linemate
    }

    pub fn deraumere(&self) -> usize {
        self.deraumere
    }

    pub fn deraumere_mut(&mut self) -> &mut usize {
        &mut self.deraumere
    }

    pub fn sibur(&self) -> usize {
        self.sibur
    }

    pub fn sibur_mut(&mut self) -> &mut usize {
        &mut self.sibur
    }

    pub fn mendiane(&self) -> usize {
        self.mendiane
    }

    pub fn mendiane_mut(&mut self) -> &mut usize {
        &mut self.mendiane
    }

    pub fn phiras(&self) -> usize {
        self.phiras
    }

    pub fn phiras_mut(&mut self) -> &mut usize {
        &mut self.phiras
    }

    pub fn thystame(&self) -> usize {
        self.thystame
    }

    pub fn thystame_mut(&mut self) -> &mut usize {
        &mut self.thystame
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

    pub fn get_any_item(&self) -> Option<Item> {
        match () {
            _ if self.linemate > 0 => Some(Item::Linemate),
            _ if self.deraumere > 0 => Some(Item::Deraumere),
            _ if self.sibur > 0 => Some(Item::Sibur),
            _ if self.mendiane > 0 => Some(Item::Mendiane),
            _ if self.phiras > 0 => Some(Item::Phiras),
            _ if self.thystame > 0 => Some(Item::Thystame),
            _ => None,
        }
    }

    pub fn compare(&self, other: &Inventory) -> bool {
        self.linemate() >= other.linemate()
            && self.deraumere() >= other.deraumere()
            && self.sibur() >= other.sibur()
            && self.phiras() >= other.phiras()
            && self.thystame() >= other.thystame()
    }

    pub fn is_empty(&self) -> bool {
        self.linemate() == 0
            && self.deraumere() == 0
            && self.sibur() == 0
            && self.phiras() == 0
            && self.thystame() == 0
    }
}
