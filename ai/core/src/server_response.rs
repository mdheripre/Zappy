use regex::Regex;

/// Possible responses from the server.
///
/// # Variants
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
    Inventory(i32),
    Message(i32, String),
    ClientNum(i32),
    Incantation(i32),
    Unknown(String),
}

impl ServerResponse {
    pub fn from_string(response: &str) -> Self {
        let response = response.trim();
        match response {
            "ok" => ServerResponse::Ok,
            "ko" => ServerResponse::Ko,
            "dead" => ServerResponse::Dead,
            s if s.starts_with("[") && s.ends_with("]") && !s.chars().any(|c| c.is_numeric()) => {
                Self::parse_look_response(s)
            }
            s if s.starts_with("[") && s.ends_with("]") && s.chars().any(|c| c.is_numeric()) => {
                Self::parse_inventory_response(s)
            }
            s if s.starts_with("CLIENT-") => Self::parse_clientnum_response(s),
            s if s.starts_with("message ") => Self::parse_message_response(s),
            s if s.starts_with("current level:") => Self::parse_incantation_response(s),
            _ => ServerResponse::Unknown(response.to_string()),
        }
    }

    fn parse_look_response(s: &str) -> Self {
        let items = s[1..s.len() - 1]
            .split(',')
            .map(|s| s.trim().to_string())
            .collect();
        ServerResponse::Look(items)
    }

    fn parse_inventory_response(s: &str) -> Self {
        match Regex::new(r"food (\d+)")
            .ok()
            .and_then(|re| re.captures(s))
            .and_then(|cap| cap.get(1))
            .and_then(|mat| mat.as_str().parse().ok())
        {
            Some(food_value) => ServerResponse::Inventory(food_value),
            None => ServerResponse::Inventory(0),
        }
    }

    fn parse_clientnum_response(s: &str) -> Self {
        match s[7..].parse::<i32>() {
            Ok(num) => ServerResponse::ClientNum(num),
            Err(_) => ServerResponse::Unknown(s.to_string()),
        }
    }

    fn parse_message_response(s: &str) -> Self {
        let regex = match Regex::new(r"^message\s+(\w+)\s*,\s*(.+)$") {
            Ok(re) => re,
            Err(_) => return ServerResponse::Unknown(s.to_string()),
        };

        let caps = match regex.captures(s) {
            Some(caps) => caps,
            None => return ServerResponse::Unknown(s.to_string()),
        };

        let (dir, msg) = match (caps.get(1), caps.get(2)) {
            (Some(dir), Some(msg)) => (dir, msg),
            _ => return ServerResponse::Unknown(s.to_string()),
        };

        match dir.as_str().parse::<i32>() {
            Ok(num) => ServerResponse::Message(num, msg.as_str().to_string()),
            Err(_) => ServerResponse::Unknown(s.to_string()),
        }
    }

    fn parse_incantation_response(s: &str) -> Self {
        let regex = match Regex::new(r"^current level:\s+(\d+)$") {
            Ok(re) => re,
            Err(_) => return ServerResponse::Unknown(s.to_string()),
        };

        let caps = match regex.captures(s) {
            Some(caps) => caps,
            None => return ServerResponse::Unknown(s.to_string()),
        };

        let level_str = match caps.get(1) {
            Some(level) => level,
            None => return ServerResponse::Unknown(s.to_string()),
        };

        match level_str.as_str().parse::<i32>() {
            Ok(level) => ServerResponse::Incantation(level),
            Err(_) => ServerResponse::Unknown(s.to_string()),
        }
    }
}
