mod error;
mod init;
mod prelude;
mod utils;

use crate::prelude::*;
use init::init_client;
use clap::Parser;

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
    println!("{:?}", infos);
    init_client(&infos)?;
    Ok(())
}
