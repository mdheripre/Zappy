use std::error;
use std::fmt;
use std::io;
use tokio::sync::mpsc::error::SendError;

use crate::packet::Packet;

#[derive(Debug)]
pub enum CoreError {
    Io(std::io::Error),
    Tcp(lib_tcp::TcpError),
    InvalidResponse(String),
    SendChannelError(SendError<Packet>),
}

impl error::Error for CoreError {}

impl fmt::Display for CoreError {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> fmt::Result {
        match self {
            CoreError::Io(e) => write!(f, "Io error: {}", e),
            CoreError::Tcp(e) => write!(f, "Tcp error: {}", e),
            CoreError::InvalidResponse(e) => write!(f, "Invalid Response: {}", e),
            CoreError::SendChannelError(e) => write!(f, "Send channel Error: {}", e),
        }
    }
}

impl From<io::Error> for CoreError {
    fn from(err: io::Error) -> Self {
        CoreError::Io(err)
    }
}

impl From<lib_tcp::TcpError> for CoreError {
    fn from(err: lib_tcp::TcpError) -> Self {
        CoreError::Tcp(err)
    }
}

impl From<SendError<Packet>> for CoreError {
    fn from(err: SendError<Packet>) -> Self {
        CoreError::SendChannelError(err)
    }
}