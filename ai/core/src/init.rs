use crate::packet::PacketSender;
use crate::ServerInfos;
use crate::{CoreError, Result};
use lib_tcp::tcp_client::AsyncTcpClient;

/// Infos given by the server on connexion
///
/// # Fields
/// - `client_num` (`i32`) - Number of team slots remaining.
/// - `x` (`i32`) - width size of the map.
/// - `y` (`i32`) - height size of the map.
///
/// # Examples
/// ```
/// use crate::...;
///
/// let s = ClientInfos {
///     client_num: value,
///     x: value,
///     y: value,
/// };
/// ```
#[derive(Debug, Clone)]
pub struct ClientInfos {
    pub client_num: i32,
    pub x: i32,
    pub y: i32,
}

async fn handshake(client: &mut AsyncTcpClient, infos: &ServerInfos) -> Result<ClientInfos> {
    let response = client.recv_until(b'\n').await?;
    if response != "WELCOME\n" {
        return Err(CoreError::InvalidResponse(response));
    }
    println!("Received: WELCOME");
    println!("Sending: team name");
    client.send_team_name(&infos.name).await?;
    let position_str = client.recv_until(b'\n').await?;
    let client_num_str = client.recv_until(b'\n').await?;

    let client_num: i32 = client_num_str
        .trim()
        .parse()
        .map_err(|_| CoreError::InvalidResponse(client_num_str.clone()))?;

    let mut parts = position_str.split_whitespace();

    let x: i32 = parts
        .next()
        .ok_or_else(|| CoreError::InvalidResponse(position_str.clone()))?
        .parse()
        .map_err(|_| CoreError::InvalidResponse(position_str.clone()))?;

    let y: i32 = parts
        .next()
        .ok_or_else(|| CoreError::InvalidResponse(position_str.clone()))?
        .parse()
        .map_err(|_| CoreError::InvalidResponse(position_str.clone()))?;

    let client_infos = ClientInfos { client_num, x, y };
    Ok(client_infos)
}

/// initialize and connect a new client to the server
///
/// # Arguments
/// - `infos` (`&ServerInfos`) - information requiered for connection.
///
/// # Returns
/// - `Result<(AsyncTcpClient, ClientInfos)>` - Infos send by the server.
///
/// # Errors
/// TCP errors.
///
/// # Examples
/// ```no_run
/// use crate::...;
///
/// async {
///   let result = init_client().await;
/// };
/// ```
pub async fn init_client(infos: &ServerInfos) -> Result<(AsyncTcpClient, ClientInfos)> {
    let mut client = AsyncTcpClient::new(&infos.ip, infos.port).await?;

    let client_infos = handshake(&mut client, infos).await?;
    Ok((client, client_infos))
}
