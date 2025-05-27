#[derive(Debug)]
pub enum TcpError {
    InvalidAddress,
    ConnectionClosed,
    Io(std::io::Error),
    Utf8(std::string::FromUtf8Error),
}

impl std::error::Error for TcpError {}

impl std::fmt::Display for TcpError {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        match self {
            TcpError::InvalidAddress => write!(f, "Invalid address"),
            TcpError::ConnectionClosed => write!(f, "Connection closed"),
            TcpError::Io(e) => write!(f, "Io error: {}", e),
            TcpError::Utf8(e) => write!(f, "UTF-8 error: {}", e),
        }
    }
}

impl From<std::io::Error> for TcpError {
    fn from(err: std::io::Error) -> Self {
        TcpError::Io(err)
    }
}

impl From<std::string::FromUtf8Error> for TcpError {
    fn from(err: std::string::FromUtf8Error) -> Self {
        TcpError::Utf8(err)
    }
}

pub type Result<T> = core::result::Result<T, TcpError>;
