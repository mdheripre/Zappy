use core::fmt;

#[derive(Debug, Clone)]
pub enum MessageType {
    Gather,
    Dead,
    Need,
    Hello,
    Welcome,
    Item,
}

impl fmt::Display for MessageType {
    fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {
        let out = match self {
            MessageType::Gather => "GATHER".to_string(),
            MessageType::Dead => "DEAD".to_string(),
            MessageType::Need => "NEED".to_string(),
            MessageType::Hello => "HELLO".to_string(),
            MessageType::Welcome => "WELCOME".to_string(),
            MessageType::Item => "ITEM".to_string(),
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
    
    pub fn content(&self) -> &Option<String> { &self.content }
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
    received: Vec<(i32, Message)>,
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

    pub fn receive_message(&mut self, dir: i32, msg: &String) -> Result<(), String> {
        let parsed_msg = self.parse_message(&msg)?;

        self.is_valid_message(&parsed_msg)?;
        self.received.insert(0, (dir, parsed_msg));
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
            "HELLO" => Ok(MessageType::Hello),
            "WELCOME" => Ok(MessageType::Welcome),
            "ITEM" => Ok(MessageType::Item),
            _ => Err(format!("Invalid msg type: {}", type_str)),
        }
    }

    fn is_valid_message(&self, msg: &Message) -> Result<(), String> {
        let duplicate_received = self.received.iter().any(|existing| {
            existing.1.program_id() == msg.program_id() && existing.1.msg_id() == msg.msg_id()
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

    pub fn get_received_messages(&self) -> &[(i32, Message)] {
        &self.received
    }
    
    pub fn pop_received(&mut self) -> Option<(i32, Message)> {
        self.received.pop()
    }
    
    pub fn clear(&mut self) {
        self.received.clear();
    }
}
