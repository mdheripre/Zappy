fn cypher_string(input: &str, ai_id: u32, key: u32) -> String {
    let id_bytes = ai_id.to_le_bytes();
    let key_bytes = key.to_le_bytes();
    let mut output = String::with_capacity(2 * (id_bytes.len() + key_bytes.len()) + input.len());
    for byte in id_bytes.iter().chain(key_bytes.iter()) {
        output.push_str(&format!("{:02X} ", byte));
    }
    output.push_str(input);
    output
}

fn decipher_string(input: &str) -> Option<(u32, u32, &str)> {
    let parts: Vec<&str> = input.split_whitespace().collect();

    if parts.len() < 8 {
        return None;
    }
    let mut bytes = [0u8; 8];
    for (i, part) in parts.iter().take(8).enumerate() {
        match u8::from_str_radix(part, 16) {
            Ok(b) => bytes[i] = b,
            Err(_) => return None,
        }
    }
    let ai_id = u32::from_le_bytes(bytes[0..4].try_into().unwrap());
    let key = u32::from_le_bytes(bytes[4..8].try_into().unwrap());
    let message_start = parts[..8].iter().map(|s| s.len() + 1).sum();
    let message = &input[message_start..];
    Some((ai_id, key, message))
}

fn get_message(input: &str, id_used: Vec<(u32, u32)>) -> Option<String> {
    let deciphered = decipher_string(input);
    if let Some((ai_id, key, message)) = deciphered {
        if id_used.contains(&(ai_id, key)) {
            return None;
        }
        Some(message.to_string())
    } else {
        None
    }
}
