use crate::ai::AiCommand;

/// Represents the direction of the AI in the game.
/// # Variants
/// - `North` - Facing north.
/// - `East` - Facing east.
/// - `South` - Facing south.
/// - `West` - Facing west.
///
#[derive(Debug, Clone)]
pub enum Direction {
    North,
    East,
    South,
    West,
}

impl Direction {
    /// Turn the direction to the right
    /// # Returns
    /// - `Direction` - The new direction after turning right.
    pub fn right(&self) -> Self {
        match self {
            Direction::North => Direction::East,
            Direction::East => Direction::South,
            Direction::South => Direction::West,
            Direction::West => Direction::North,
        }
    }

    /// Turn the direction to the left
    /// # Returns
    /// - `Direction` - The new direction after turning left.
    pub fn left(&self) -> Self {
        match self {
            Direction::North => Direction::West,
            Direction::East => Direction::North,
            Direction::South => Direction::East,
            Direction::West => Direction::South,
        }
    }

    /// Checks if the given position is along the direction
    /// # Arguments
    /// - `pos` - The position to check, represented as a tuple (x, y).
    /// # Returns
    /// - `bool` - `true` if the position is along the direction, `false` otherwise.
    pub fn is_along(&self, pos: (i32, i32)) -> bool {
        match self {
            Direction::North => pos.1 < 0,
            Direction::East => pos.0 > 0,
            Direction::South => pos.1 > 0,
            Direction::West => pos.0 < 0,
        }
    }

    // Get the best turn to orient to the given position
    /// # Arguments
    /// - `pos` - The position to orient towards, represented as a tuple (x, y).
    /// # Returns
    /// - `AiCommand` - The best command to turn towards the position.
    pub fn get_best_turn_to(&self, pos: (i32, i32)) -> AiCommand {
        match self {
            Direction::North => {
                if pos.0 < 0 {
                    return AiCommand::Left;
                }
                AiCommand::Right
            }
            Direction::East => {
                if pos.1 < 0 {
                    return AiCommand::Left;
                }
                AiCommand::Right
            }
            Direction::South => {
                if pos.0 < 0 {
                    return AiCommand::Right;
                }
                AiCommand::Left
            }
            Direction::West => {
                if pos.1 < 0 {
                    return AiCommand::Right;
                }
                AiCommand::Right
            }
        }
    }

    pub fn get_direction_from_nb(direction: u32, look_direction: Direction) -> Direction {
        if direction == 1 || direction == 2 || direction == 8 {
            return look_direction;
        }
        if direction == 3 {
            return look_direction.left();
        }
        if direction == 7 {
            return look_direction.right();
        }
        look_direction.right().right()
    }

    pub fn add_to_pos(pos: (i32, i32), direction: Direction) -> (i32, i32) {
        match direction {
            Direction::North => (pos.0, pos.1 - 1),
            Direction::East => (pos.0 + 1, pos.1),
            Direction::South => (pos.0, pos.1 + 1),
            Direction::West => (pos.0 - 1, pos.1),
        }
    }
}
