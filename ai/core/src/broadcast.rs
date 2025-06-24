use core::fmt;

#[derive(Debug, Clone)]
pub enum MessageType {
    Gather,
    Dead,
    Need,
}

impl fmt::Display for MessageType {
    fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {
        let out = match self {
            MessageType::Gather => "GATHER".to_string(),
            MessageType::Dead => "DEAD".to_string(),
            MessageType::Need => "NEED".to_string(),
        };
        write!(f, "{}", out)
    }
}

#[derive(Debug, Clone)]
pub struct Message {
    ids: (u32, u32),
    msg_type: MessageType,
    content: Option<String>,
}

impl Message {
    pub fn new(prog_id: u32, msg_id: u32, msg_type: MessageType, content: Option<String>) -> Self {
        Self {
            ids: (prog_id, msg_id),
            msg_type,
            content,
        }
    }

    pub fn program_id(&self) -> u32 {
        self.ids.0
    }

    pub fn msg_id(&self) -> u32 {
        self.ids.1
    }

    pub fn msg_type(&self) -> &MessageType {
        &self.msg_type
    }
}

impl fmt::Display for Message {
    fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {
        match &self.content {
            Some(content) => write!(
                f,
                "{}:{}:{}:{}",
                self.ids.0, self.ids.1, self.msg_type, content
            ),
            None => write!(f, "{}:{}:{}", self.ids.0, self.ids.1, self.msg_type),
        }
    }
}

#[derive(Debug, Clone)]
pub struct Broadcast {
    received: Vec<Message>,
    sent: Vec<Message>,
    key: u32,
}

impl Broadcast {
    pub fn new(key: u32) -> Self {
        Self {
            received: vec![],
            sent: vec![],
            key,
        }
    }

    pub fn send_message(&mut self, msg: Message) {
        self.sent.push(msg);
    }

    pub fn receive_message(&mut self, msg: &String) -> Result<(), String> {
        let parsed_msg = self.parse_message(&msg)?;

        self.is_valid_message(&parsed_msg)?;
        self.received.push(parsed_msg);
        Ok(())
    }

    fn parse_message(&self, msg: &str) -> Result<Message, String> {
        let parts: Vec<&str> = msg.split(':').collect();

        if parts.len() < 3 {
            return Err("not enough parts".to_string());
        }

        let prog_id = parts[0]
            .parse::<u32>()
            .map_err(|_| format!("Invalid program id: {}", parts[0]))?;

        let msg_id = parts[1]
            .parse::<u32>()
            .map_err(|_| format!("Invalid msg id: {}", parts[1]))?;

        let msg_type = self.parse_message_type(parts[2])?;

        let content = if parts.len() > 3 && !parts[3].is_empty() {
            Some(parts[3..].join(":"))
        } else {
            None
        };

        Ok(Message::new(prog_id, msg_id, msg_type, content))
    }

    fn parse_message_type(&self, type_str: &str) -> Result<MessageType, String> {
        match type_str {
            "GATHER" => Ok(MessageType::Gather),
            "NEED" => Ok(MessageType::Need),
            "DEAD" => Ok(MessageType::Dead),
            _ => Err(format!("Invalid msg type: {}", type_str)),
        }
    }

    fn is_valid_message(&self, msg: &Message) -> Result<(), String> {
        let duplicate_received = self.received.iter().any(|existing| {
            existing.program_id() == msg.program_id() && existing.msg_id() == msg.msg_id()
        });

        if duplicate_received {
            return Err(format!(
                "Duplicated message: {}:{}",
                msg.program_id(),
                msg.msg_id()
            ));
        }
        Ok(())
    }

    pub fn get_sent_messages(&self) -> &[Message] {
        &self.sent
    }

    pub fn get_received_messages(&self) -> &[Message] {
        &self.received
    }
}
