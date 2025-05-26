mod init;

use init::{init};

use std::env;

fn print_usage()
{
    println!("USAGE: ./zappy_ai -p port -n name -h machine");
}

fn main()
{
    let args : Vec<String> = env::args().collect();

    if (args.len()) != 4{
        print_usage();
        return;
    }
    init();
    tcp::connect();
    println!("Hello, world!");
}
