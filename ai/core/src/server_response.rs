use crate::{CoreError, Result};

#[derive(Debug, Clone)]
pub enum ServerResponse {
    Ok,
    Ko,
    Dead,
    Look(Vec<String>),
    Inventory(Vec<String>),
    Message(String),
    Welcome,
    ClientNum(i32),
    MapSize(i32, i32),
}

impl ServerResponse {
    pub fn from_string(response: &str) -> Self {
        let response = response.trim();
        match response {
            "ok" => ServerResponse::Ok,
            "ko" => ServerResponse::Ko,
            "dead" => ServerResponse::Dead,
            "WELCOME" => ServerResponse::Welcome,
            s if s.starts_with("[") && s.ends_with("]") => {
                let items = s[1..s.len() - 1].split(',')
                    .map(|s| s.trim().to_string())
                    .collect();
                ServerResponse::Look(items)
            }
            s if s.starts_with("CLIENT-") => {
                if let Ok(num) = s[7..].parse::<i32>() {
                    ServerResponse::ClientNum(num)
                } else {
                    ServerResponse::Message(s.to_string())
                }
            }
            _ => ServerResponse::Message(response.to_string()),
        }
    }
}
