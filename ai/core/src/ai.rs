use crate::{CoreError, Result};

#[derive(Debug, Clone)]
pub enum GameCommand {
    TeamName(String),
    Forward,
    Right,
    Left,
    Look,
    Inventory,
    Broadcast(String),
    ConnectNbr(u32),
    Fork,
    Eject,
    Take(String),
    Set(String),
    Incantation,
}
