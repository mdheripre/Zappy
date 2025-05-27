use crate::ServerInfos;
use lib_tcp::tcp_client::AsyncTcpClient;

pub async fn init_client(infos: &ServerInfos) -> lib_tcp::Result<()> {
    let mut client = AsyncTcpClient::new(&infos.ip, infos.port).await?;

    client.send(&infos.name).await?;
    Ok(())
}
