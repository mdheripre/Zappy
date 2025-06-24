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
    Message(String),
    ClientNum(i32),
}

impl ServerResponse {
    pub fn from_string(response: &str) -> Self {
        let response = response.trim();
        match response {
            "ok" => ServerResponse::Ok,
            "ko" => ServerResponse::Ko,
            "dead" => ServerResponse::Dead,
            s if s.starts_with("[") && s.ends_with("]") && !s.chars().any(|c| c.is_numeric()) => {
                let items = s[1..s.len() - 1]
                    .split(',')
                    .map(|s| s.trim().to_string())
                    .collect();
                ServerResponse::Look(items)
            }
            s if s.starts_with("[") && s.ends_with("]") && s.chars().any(|c| c.is_numeric()) => {
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
