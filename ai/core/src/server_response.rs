use crate::{CoreError, Result};

/// Possible responses from the server.
/// 
/// # Variants
/// 
/// - `Ok` - command succeed.
/// - `Ko` - command failed.
/// - `Dead` - player died.
/// - `Look(Vec<String>)` - look command response with tiles.
/// - `Inventory(Vec<String>)` - inventory content.
/// - `Message(String)` - Broadcast command response with text.
/// - `Welcome` - On client connexion.
/// - `ClientNum(i32)` - Number of client slots remaining for the team.
/// - `MapSize(i32, i32)` - Size of the map.
/// 
/// # Examples
/// 
/// ```
/// use crate::...;
/// 
/// let response = ServerResponse::Ok;
/// match response {
///     ServerResponse::Ok => handle_unit,
///     ServerResponse::Ko => handle_unit,
///     ServerResponse::Dead => handle_unit,
///     ServerResponse::Look(v0) => handle_tuple,
///     ServerResponse::Inventory(v0) => handle_tuple,
///     ServerResponse::Message(v0) => handle_tuple,
///     ServerResponse::Welcome => handle_unit,
///     ServerResponse::ClientNum(v0) => handle_tuple,
///     ServerResponse::MapSize(v0, v1) => handle_tuple,
/// }
/// ```
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
                let items = s[1..s.len() - 1]
                    .split(',')
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
