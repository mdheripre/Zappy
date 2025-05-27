use crate::ServerInfos;

pub fn init_client(infos: &ServerInfos) -> lib_tcp::Result<()> 
{
    let stream = lib_tcp::connect(&infos.ip, infos.port)?;

    lib_tcp::send(stream, &infos.name)?;
    Ok(())
}
