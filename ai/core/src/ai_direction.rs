use crate::ai::AiCommand;

#[derive(Debug, Clone)]
pub enum Direction {
    North,
    East,
    South,
    West,
}

impl Direction {
    pub fn right(&self) -> Self {
        match self {
            Direction::North => Direction::East,
            Direction::East => Direction::South,
            Direction::South => Direction::West,
            Direction::West => Direction::North,
        }
    }
    
    pub fn left(&self) -> Self {
        match self {
            Direction::North => Direction::West,
            Direction::East => Direction::North,
            Direction::South => Direction::East,
            Direction::West => Direction::South,
        }
    }
    
    pub fn is_along(&self, pos: (i32, i32)) -> bool {
        match self {
            Direction::North => pos.1 < 0,
            Direction::East => pos.0 > 0,
            Direction::South => pos.1 > 0,
            Direction::West => pos.0 < 0,
        }
    }
    
    // Get the best turn to orient to the given position
    pub fn get_best_turn_to(&self, pos: (i32, i32)) -> AiCommand {
        match self {
            Direction::North => {
                if pos.0 < 0 {
                    return AiCommand::Left
                }
                AiCommand::Right
            },
            Direction::East => {
                if pos.1 < 0 {
                    return AiCommand::Left
                }
                AiCommand::Right
            },
            Direction::South => {
                if pos.0 < 0 {
                    return AiCommand::Right
                }
                AiCommand::Left
            },
            Direction::West => {
                if pos.1 < 0 {
                    return AiCommand::Right
                }
                AiCommand::Right
            },
        }
    }
}
