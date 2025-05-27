mod error;
mod utils;
mod prelude;
mod init;

use init::{init};
use std::env;
use crate::prelude::*;

fn print_usage()
{
    println!("USAGE: ./zappy_ai -p port -n name -h machine");
}

fn main() -> Result<()>
{
    let args : Vec<String> = env::args().collect();

    if args.len() == 2 && &args[1] == "--help" {
        print_usage();
        return Ok(());
    }
    if args.len() != 4 {
        return Err(CoreError::InvalidArgs);
    }
    init();
    lib_tcp::connect();
    println!("Hello, world!");
    Ok(())
}
