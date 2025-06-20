use std::error;
use std::fmt;
use std::io;
use tokio::sync::mpsc::error::SendError;

use crate::packet::Packet;
use crate::server_response::ServerResponse;

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
    FormatError(std::fmt::Error),
    InvalidResponse(String),
    SendChannelErrorPacket(SendError<Packet>),
    SendChannelErrorSR(SendError<ServerResponse>),
    ConnectionClosed(String),
    Process(String),
}

impl error::Error for CoreError {}

impl fmt::Display for CoreError {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> fmt::Result {
        match self {
            CoreError::Io(e) => write!(f, "Io error: {}", e),
            CoreError::Tcp(e) => write!(f, "Tcp error: {}", e),
            CoreError::FormatError(e) => write!(f, "Format error: {}", e),
            CoreError::InvalidResponse(e) => write!(f, "Invalid Response: {}", e),
            CoreError::ConnectionClosed(e) => write!(f, "ConnectionClosed: {}", e),
            CoreError::SendChannelErrorPacket(e) => write!(f, "Send channel Error: {}", e),
            CoreError::SendChannelErrorSR(e) => write!(f, "Send channel Error: {}", e),
            CoreError::Process(e) => write!(f, "Process Error: {}", e),
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

impl From<std::fmt::Error> for CoreError {
    fn from(err: std::fmt::Error) -> Self {
        CoreError::FormatError(err)
    }
}

impl From<SendError<Packet>> for CoreError {
    fn from(err: SendError<Packet>) -> Self {
        CoreError::SendChannelErrorPacket(err)
    }
}

impl From<SendError<ServerResponse>> for CoreError {
    fn from(err: SendError<ServerResponse>) -> Self {
        CoreError::SendChannelErrorSR(err)
    }
}
