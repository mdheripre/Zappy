use crate::{AsyncW, Result};
use std::ops::{Deref, DerefMut};
use tokio::net::TcpStream;

/// Async TcpStream wrapper
///
/// # Fields
///
/// - `stream` (`AsyncW<TcpStream>`) - the actuall TcpStream
///
/// # Examples
///
/// ```
/// use crate::...;
///
/// let ip = "127.0.0.1";
/// let port = 8080;
/// let s = AsyncTcpClient::new(ip, port);
/// ```
pub struct AsyncTcpClient {
    stream: AsyncW<TcpStream>,
}

impl AsyncTcpClient {
    /// create and connect a TcpStream
    ///
    /// # Arguments
    ///
    /// - `ip` (`&str`) - ip address.
    /// - `port` (`u16`) - port.
    ///
    /// # Returns
    ///
    /// - `Result<Self>`.
    ///
    /// # Errors
    ///
    /// Tcp error.
    ///
    /// # Examples
    ///
    /// ```no_run
    /// use crate::...;
    ///
    /// async {
    ///   let result = new().await;
    /// };
    /// ```
    pub async fn new(ip: &str, port: u16) -> Result<Self> {
        let stream = AsyncW::connect(ip, port).await?;
        Ok(Self { stream })
    }

    pub async fn send_and_recv(&mut self, msg: &str) -> Result<String> {
        self.stream.send(msg).await?;
        let response = self.stream.recv().await?;
        Ok(response)
    }

    /// send a set of requests
    ///
    /// # Arguments
    ///
    /// - `&mut self` (`undefined`).
    /// - `msgs` (`&[&str]`) - array of requests to send.
    ///
    /// # Returns
    ///
    /// - `Result<Vec<String>>` - array of responses from requests.
    ///
    /// # Errors
    ///
    /// Describe possible errors.
    ///
    /// # Examples
    ///
    /// ```no_run
    /// use crate::...;
    ///
    /// async {
    ///   let result = send_batch().await;
    /// };
    /// ```
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
