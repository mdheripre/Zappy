use crate::{AsyncW, Result};
use std::ops::{Deref, DerefMut};
use tokio::net::TcpStream;

pub struct AsyncTcpClient {
    stream: AsyncW<TcpStream>,
}

impl AsyncTcpClient {
    pub async fn new(ip: &str, port: u16) -> Result<Self> {
        let stream = AsyncW::connect(ip, port).await?;
        Ok(Self { stream })
    }

    pub async fn send_and_recv(&mut self, msg: &str) -> Result<String> {
        self.stream.send(msg).await?;
        let response = self.stream.recv().await?;
        Ok(response)
    }

    pub async fn send_batch(&mut self, msgs: &[&str]) -> Result<Vec<String>> {
        let mut responses = Vec::new();

        for msg in msgs {
            self.stream.send(msg).await?;
            let response = self.stream.recv().await?;
            responses.push(response);
        }
        Ok(responses)
    }
}

impl Deref for AsyncTcpClient {
    type Target = AsyncW<TcpStream>;

    fn deref(&self) -> &Self::Target {
        &self.stream
    }
}

impl DerefMut for AsyncTcpClient {
    fn deref_mut(&mut self) -> &mut Self::Target {
        &mut self.stream
    }
}
