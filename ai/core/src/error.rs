use std::error;
use std::fmt;
use std::io;
use tokio::sync::mpsc::error::SendError;

use crate::packet::Packet;

/// Error enum
///
/// # Variants
///
/// - `Io(std::io::Error)` - Basic Io error (e.g read / write).
/// - `Tcp(lib_tcp::TcpError)` - Error from lib-tcp.
/// - `InvalidResponse(String)` - invalid response from the server.
/// - `SendChannelError(SendError<Packet>)` - Error in a send channel.
/// - `ConnectionClosed(String)` - Server closed connexion.
///
/// # Examples
///
/// ```
/// use crate::...;
///
/// let error = CoreError::Io;
/// match error {
///     CoreError::Io(v0) => handle_tuple,
///     CoreError::Tcp(v0) => handle_tuple,
///     CoreError::InvalidResponse(v0) => handle_tuple,
///     CoreError::SendChannelError(v0) => handle_tuple,
///     CoreError::ConnectionClosed(v0) => handle_tuple,
/// }
/// ```
#[derive(Debug)]
pub enum CoreError {
    Io(std::io::Error),
    Tcp(lib_tcp::TcpError),
    InvalidResponse(String),
    SendChannelError(SendError<Packet>),
    ConnectionClosed(String),
}

impl error::Error for CoreError {}

impl fmt::Display for CoreError {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> fmt::Result {
        match self {
            CoreError::Io(e) => write!(f, "Io error: {}", e),
            CoreError::Tcp(e) => write!(f, "Tcp error: {}", e),
            CoreError::InvalidResponse(e) => write!(f, "Invalid Response: {}", e),
            CoreError::ConnectionClosed(e) => write!(f, "ConnectionClosed: {}", e),
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
