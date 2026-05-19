pub struct Layout {
    pub display_lines: Vec<String>,
    pub display_to_raw: Vec<usize>, // 1-indexed raw line number, 0 for continuation
    pub raw_to_display: Vec<usize>, // maps raw line index to starting display line index
}

impl Layout {
    pub fn new() -> Self {
        Self {
            display_lines: Vec::new(),
            display_to_raw: Vec::new(),
            raw_to_display: Vec::new(),
        }
    }

    pub fn add_line(&mut self, text: &str, raw_num: usize) {
        self.display_lines.push(text.to_string());
        self.display_to_raw.push(raw_num);
    }

    pub fn count(&self) -> usize {
        self.display_lines.len()
    }
}
