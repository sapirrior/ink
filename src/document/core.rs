pub struct Document {
    pub raw_lines: Vec<String>,
}

impl Document {
    pub fn new() -> Self {
        Self {
            raw_lines: Vec::new(),
        }
    }

    pub fn clear(&mut self) {
        self.raw_lines.clear();
    }

    pub fn line_count(&self) -> usize {
        self.raw_lines.len()
    }
}
