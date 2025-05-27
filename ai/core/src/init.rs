use crate::ServerInfos;

pub fn init_client(infos: &ServerInfos) -> lib_tcp::Result<()> 
{
    let mut client = lib_tcp::W::connect(&infos.ip, infos.port)?;

    client.send(&infos.name)?;
    client.recv()?;
    Ok(())
}
