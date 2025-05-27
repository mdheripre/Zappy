use std::error;
use std::io;
use std::fmt;

#[derive(Debug)]
pub enum CoreError
{
    InvalidArgs,
    Io(std::io::Error),
    Tcp(lib_tcp::TcpError),
}

impl error::Error for CoreError {}

impl fmt::Display for CoreError
{
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> fmt::Result
    {
        match self
        {
            CoreError::InvalidArgs => write!(f, ""),
            CoreError::Io(e) => write!(f, "Io error: {}", e),
            CoreError::Tcp(e) => write!(f, "Tcp error: {}", e),
        }
    }
}

impl From<io::Error> for CoreError
{
    fn from(err: io::Error) -> Self
    {
        CoreError::Io(err)
    }
}

impl From<lib_tcp::TcpError> for CoreError
{
    fn from(err: lib_tcp::TcpError) -> Self
    {
        CoreError::Tcp(err)
    }
}

