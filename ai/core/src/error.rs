#[derive(Debug)]
pub enum CoreError
{
    InvalidArgs,
    Io(std::io::Error),
    Tcp(lib_tcp::TcpError),
}

impl std::error::Error for CoreError {}

impl std::fmt::Display for CoreError
{
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result
    {
        match self
        {
            CoreError::InvalidArgs => write!(f, ""),
            CoreError::Io(e) => write!(f, "Io error: {}", e),
            CoreError::Tcp(e) => write!(f, "Tcp error: {}", e),
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

impl From<lib_tcp::TcpError> for CoreError
{
    fn from(err: lib_tcp::TcpError) -> Self
    {
        CoreError::Tcp(err)
    }
}

