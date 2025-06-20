mod ai;
mod ai_core;
mod ai_state;
mod ai_direction;
mod ai_role;
mod broadcast;
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
use std::env;
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
    #[arg(short = 'h', long)]
    ip: String,
    #[arg(short = 'p', long)]
    port: u16,
    #[arg(short = 'n', long)]
    name: String,
    is_child: bool,
}

impl ServerInfos {
    fn new() -> Self {
        let args = ServerInfos::parse();
        let is_child = env::var("IS_CHILD").ok().as_deref() == Some("1");
        ServerInfos {
            ip: args.ip,
            port: args.port,
            name: args.name,
            is_child,
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
