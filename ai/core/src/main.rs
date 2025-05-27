mod error;
mod utils;
mod prelude;
mod init;

use crate::prelude::*;
use std::env;
use init::{init_client};

#[derive(Debug)]
struct ServerInfos
{
    ip: String,
    port: u16,
    name: String,
} 

fn parse_args(args:  Vec<String>) -> Result<ServerInfos>
{
    let mut ip = None;
    let mut port = None;
    let mut name = None;

    if args.len() != 7 {
        return Err(CoreError::InvalidArgs);
    }
    let mut iter = args.into_iter();
    while let Some(arg) = iter.next() {
        match arg.as_str() {
            "-p" => {
                if let Some(val) = iter.next() {
                    port = Some(val.parse().map_err(|_| CoreError::InvalidArgs)?);
                }
            }
            "-h" => {
                if let Some(val) = iter.next() {
                    ip = Some(val.parse().map_err(|_| CoreError::InvalidArgs)?);
                }
            }
            "-n" => {
                if let Some(val) = iter.next() {
                    name = Some(val.parse().map_err(|_| CoreError::InvalidArgs)?);
                }
            }
            _ => continue,
        }
    }

    match (ip, port, name) {
        (Some(ip), Some(port), Some(name)) => Ok(ServerInfos {ip, port, name}),
        _ => Err(CoreError::InvalidArgs),
    }
}

fn print_usage()
{
    println!("USAGE: ./zappy_ai -p port -n name -h machine");
}

fn main() -> Result<()>
{
    let args : Vec<String> = env::args().collect();

    if args.len() == 2 && &args[1] == "-help" {
        print_usage();
        return Ok(());
    }
    let infos = parse_args(args)?;
    println!("{:?}", infos);
    init_client(&infos)?;
    Ok(())
}
