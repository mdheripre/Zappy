mod ai;
mod ai_core;
mod error;
mod init;
mod item;
mod packet;
mod prelude;
mod server_response;
mod tile;
mod utils;

use crate::{ai_core::AiCore, prelude::*};
use clap::Parser;
use init::init_client;
use tokio::runtime::Runtime;

/// Informations requiered for server connection
/// 
/// # Fields
/// 
/// - `long)] ip` (`String`) - ip address.
/// - `long)] port` (`u16`) - port.
/// - `long)] name` (`String`) - team name.
/// 
/// # Examples
/// 
/// ```
/// use crate::...;
/// 
/// let s = ServerInfos {
///     long)] ip: value,
///     long)] port: value,
///     long)] name: value,
/// };
/// ```
#[derive(Parser, Debug)]
#[command(name = "zappy_ai", disable_help_flag = true)]
struct ServerInfos {
    #[arg(short = 'h', long)]
    ip: String,
    #[arg(short = 'p', long)]
    port: u16,
    #[arg(short = 'n', long)]
    name: String,
}

fn main() -> Result<()> {
    let infos = ServerInfos::parse();
    let rt = Runtime::new()?;

    rt.block_on(async {
        let mut ai_core = AiCore::new(&infos).await?;
        println!("Ai core initialized, starting main loop..");
        ai_core.run().await?;
        println!("Simulation finished.");
        Ok::<(), CoreError>(())
    })?;
    Ok(())
}
