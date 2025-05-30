mod error;
mod init;
mod packet;
mod prelude;
mod utils;

use crate::prelude::*;
use clap::Parser;
use init::init_client;
use tokio::runtime::Runtime;

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
    rt.block_on(async { init_client(&infos).await })?;
    Ok(())
}
