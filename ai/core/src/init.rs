use crate::packet::PacketSender;
use crate::ServerInfos;
use crate::{CoreError, Result};
use lib_tcp::tcp_client::AsyncTcpClient;

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
    let client_num_str = client.recv_until(b'\n').await?;
    let position_str = client.recv_until(b'\n').await?;

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

pub async fn init_client(infos: &ServerInfos) -> Result<()> {
    let mut client = AsyncTcpClient::new(&infos.ip, infos.port).await?;

    let client_infos = handshake(&mut client, infos).await?;
    println!(
        "clients infos: {} {} {}",
        client_infos.client_num, client_infos.x, client_infos.y
    );
    Ok(())
}
