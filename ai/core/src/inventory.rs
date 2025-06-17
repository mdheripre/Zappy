use crate::item::Item;

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
}