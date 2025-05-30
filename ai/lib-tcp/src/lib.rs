pub mod error;
pub mod tcp_client;
pub use crate::error::{Result, TcpError};

use std::net::SocketAddr;
use tokio::io::{AsyncReadExt, AsyncWriteExt};
use tokio::net::TcpStream;

pub struct AsyncW<T>(T);

impl AsyncW<TcpStream> {
    pub async fn connect(ip: &str, port: u16) -> Result<Self> {
        let addr: SocketAddr = format!("{}:{}", ip, port)
            .parse()
            .map_err(|_| TcpError::InvalidAddress)?;
        let stream = TcpStream::connect(&addr).await?;
        Ok(AsyncW(stream))
    }

    pub async fn send(&mut self, packet: &str) -> Result<()> {
        self.0.write_all(packet.as_bytes()).await?;
        self.0.flush().await?;
        Ok(())
    }

    pub async fn recv(&mut self) -> Result<String> {
        let mut buffer = vec![0; 1024];
        let n = self.0.read(&mut buffer).await?;

        if n == 0 {
            return Err(TcpError::ConnectionClosed);
        }
        buffer.truncate(n);
        Ok(String::from_utf8_lossy(&buffer[..n]).to_string())
    }

    pub async fn recv_with_size(&mut self, size: usize) -> Result<String> {
        let mut buffer = vec![0; size];
        let n = self.0.read(&mut buffer).await?;

        if n == 0 {
            return Err(TcpError::ConnectionClosed);
        }
        buffer.truncate(n);
        Ok(String::from_utf8_lossy(&buffer).to_string())
    }

    pub async fn recv_exact(&mut self, size: usize) -> Result<Vec<u8>> {
        let mut buffer = vec![0; size];
        self.0.read_exact(&mut buffer).await?;
        Ok(buffer)
    }

    pub async fn recv_until(&mut self, delimiter: u8) -> Result<String> {
        let mut buffer = Vec::new();
        let mut byte = [0];

        loop {
            println!("Waiting for a byte...");
            let n = self.0.read(&mut byte).await?;
            println!("Read {} bytes", n);
            if n == 0 {
                return Err(TcpError::ConnectionClosed);
            }
            buffer.push(byte[0]);
            if byte[0] == delimiter {
                break;
            }
        }
        Ok(String::from_utf8_lossy(&buffer).to_string())
    }
    pub fn get_ref(&self) -> &TcpStream {
        &self.0
    }

    pub fn get_mut(&mut self) -> &mut TcpStream {
        &mut self.0
    }

    pub fn into_inner(self) -> TcpStream {
        self.0
    }
}

#[cfg(test)]
mod test {
    use super::*;

    #[tokio::test]
    async fn test_wrapper_approach() -> Result<()> {
        Ok(())
    }

    #[tokio::test]
    async fn test_standalone_functions() -> Result<()> {
        Ok(())
    }
}
