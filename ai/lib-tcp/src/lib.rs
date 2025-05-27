pub mod error;
pub use crate::error::{Result, TcpError};
use std::io::{Read, Write};
use std::net::TcpStream;

pub struct W<T>(T);

impl W<TcpStream>
{
    pub fn connect(ip: &str, port: u16) -> Result<Self> {
        let addr = format!("{}:{}", ip, port);
        let stream = TcpStream::connect(&addr)?;
        Ok(W(stream))
    }

    pub fn send(&mut self, packet: &str) -> Result<()>
    {
        self.0.write_all(packet.as_bytes())?;
        Ok(())
    }

    pub fn recv(&mut self) -> Result<String>
    {
        let mut buffer = [0; 1024];
        let n = self.0.read(&mut buffer)?;
        Ok(String::from_utf8_lossy(&buffer[..n]).to_string())
    }
}

pub fn connect(ip: &str, port: u16) -> Result<TcpStream>
{
    let addr = format!("{}:{}", ip, port);
    let stream = TcpStream::connect(&addr)?;
    Ok(stream)
}

pub fn recv(stream: &mut TcpStream) -> Result<String>
{
    let mut buffer = [0; 1024];
    let n = stream.read(&mut buffer)?;
    let data = String::from_utf8_lossy(&buffer[..n]).to_string();
    Ok(data)
}

pub fn send(stream: &mut TcpStream, msg: &str) -> Result<()>
{
    stream.write_all(msg.as_bytes())?;
    Ok(())
}
