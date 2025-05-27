use std::fmt::{self};

#[derive(Debug)]
pub enum CoreError
{
    InvalidArgs,
    Io(std::io::Error),
}

impl std::error::Error for CoreError {}

impl fmt::Display for CoreError
{
    fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result
    {
        match self
        {
            CoreError::InvalidArgs => write!(f, "USAGE: ./zappy_ai -p port -n name -h machine"),
            CoreError::Io(e) => write!(f, "Io error: {}", e),
        }
    }
}

impl From<std::io::Error> for CoreError
{
    fn from(err: std::io::Error) -> Self
    {
        CoreError::Io(err)
    }
}

pub type Result<T> = core::result::Result<T, CoreError>;
