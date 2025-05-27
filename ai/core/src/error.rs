#[derive(Debug)]
pub enum CoreError
{
    InvalidArgs(String),
    Io(std::io::Error),
}

impl std::error::Error for CoreError {}

impl std::fmt::Display for CoreError
{
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result
    {
        match self
        {
            CoreError::InvalidArgs(msg) => write!(f, "{}", msg),
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
