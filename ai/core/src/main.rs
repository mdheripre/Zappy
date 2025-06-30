mod ai;
mod ai_core;
mod ai_direction;
mod ai_role;
mod ai_state;
mod broadcast;
mod cypher;
mod error;
mod init;
mod inventory;
mod item;
mod packet;
mod prelude;
mod server_response;
mod tile;
mod utils;

use crate::{ai_core::AiCore, prelude::*};
use clap::Parser;
use tokio::runtime::Runtime;

/// Informations requiered for server connection
///
/// # Fields
/// - `long)] ip` (`String`) - ip address.
/// - `long)] port` (`u16`) - port.
/// - `long)] name` (`String`) - team name.
///
/// # Examples
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
    #[arg(short = 'h')]
    ip: String,
    #[arg(short = 'p')]
    port: u16,
    #[arg(short = 'n')]
    name: String,
}

impl ServerInfos {
    fn new() -> Self {
        let args = ServerInfos::parse();
        ServerInfos {
            ip: args.ip,
            port: args.port,
            name: args.name,
        }
    }
}

fn main() -> Result<()> {
    let infos = ServerInfos::new();
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
