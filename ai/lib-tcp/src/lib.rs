pub mod error;

pub use crate::error::{Result, TcpError};
use std::io::{Read, Write};
use std::net::TcpStream;

pub fn connect(ip: &str, port: u16) -> Result<TcpStream>
{
    let addr = format!("{}:{}", ip, port);
    let stream = TcpStream::connect(&addr)?;
    Ok(stream)
}

pub fn recv(mut stream: TcpStream) -> Result<String>
{
    let mut buffer = [0; 1024];
    let n = stream.read(&mut buffer)?;
    let data = String::from_utf8_lossy(&buffer[..n]).to_string();
    Ok(data)
}

pub fn send(mut stream: TcpStream, msg: &str) -> Result<()>
{
    stream.write_all(msg.as_bytes())?;
    Ok(())
}
