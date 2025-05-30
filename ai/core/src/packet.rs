use core::fmt;
use lib_tcp::tcp_client::AsyncTcpClient;
use crate::{Result};
use async_trait::async_trait;

#[derive(Debug, Clone)]
pub enum Packet {
    TeamName(String),
    Forward,
    Right,
    Left,
    Look,
    Inventory,
    Broadcast(String),
    ConnectNbr(u32),
    Fork,
    Eject,
    // Death,
    Take(String),
    Set(String),
    Incantation,
}

impl fmt::Display for Packet {
    fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {
        let out = match self {
            Packet::TeamName(name) => format!("TEAM-{}", name),
            Packet::Forward => "Forward".to_string(),
            Packet::Right => "Right".to_string(),
            Packet::Left => "Left".to_string(),
            Packet::Look => "Look".to_string(),
            Packet::Inventory => "Inventory".to_string(),
            Packet::Fork => "Fork".to_string(),
            Packet::Eject => "Eject".to_string(),
            Packet::Incantation => "Incantation".to_string(),
            Packet::Broadcast(msg) => format!("Broadcast {}", msg),
            Packet::ConnectNbr(n) => format!("Connect_nbr {}", n),
            Packet::Take(item) => format!("Take {}", item),
            Packet::Set(item) => format!("Set {}", item),
        };
        write!(f, "{}", out)
    }
}

impl Packet {
    pub fn to_bytes(&self) -> Vec<u8> {
        let mut bytes = self.to_string().into_bytes();
        bytes.push(b'n');
        bytes
    }
}

#[async_trait]
pub trait PacketSender {
    async fn send_packet(&mut self, packet: Packet) -> Result<()>;

    async fn send_batch_packets(&mut self, packets: Vec<Packet>) -> Result<()>;

    async fn send_team_name(&mut self, name: &str) -> Result<()>;
    async fn move_forward(&mut self) -> Result<()>;
    async fn turn_right(&mut self) -> Result<()>;
    async fn turn_left(&mut self) -> Result<()>;
    async fn look_around(&mut self) -> Result<()>;
    async fn check_inventory(&mut self) -> Result<()>;
    async fn broadcast_message(&mut self, message: &str) -> Result<()>;
    async fn take_item(&mut self, item: &str) -> Result<()>;
}

#[async_trait]
impl PacketSender for AsyncTcpClient {
    async fn send_packet(&mut self, packet: Packet) -> Result<()> {
        let data = packet.to_string();
        self.send(&format!("{}\n", data)).await?;
        println!("Sent packet: {:?}", packet);
        Ok(())
    }

    async fn send_batch_packets(&mut self, packets: Vec<Packet>) -> Result<()> {
        for packet in packets {
            self.send_packet(packet).await?;
        }
        Ok(())
    }

    async fn send_team_name(&mut self, name: &str) -> Result<()> {
        self.send_packet(Packet::TeamName(name.to_string())).await
    }

    async fn move_forward(&mut self) -> Result<()> {
        self.send_packet(Packet::Forward).await
    }

    async fn turn_right(&mut self) -> Result<()> {
        self.send_packet(Packet::Right).await
    }

    async fn turn_left(&mut self) -> Result<()> {
        self.send_packet(Packet::Left).await
    }

    async fn look_around(&mut self) -> Result<()> {
        self.send_packet(Packet::Look).await
    }

    async fn check_inventory(&mut self) -> Result<()> {
        self.send_packet(Packet::Inventory).await
    }

    async fn broadcast_message(&mut self, message: &str) -> Result<()> {
        self.send_packet(Packet::Broadcast(message.to_string())).await
    }

    async fn take_item(&mut self, item: &str) -> Result<()> {
        self.send_packet(Packet::Take(item.to_string())).await
    }
}