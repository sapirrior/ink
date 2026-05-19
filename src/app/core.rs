use crate::document::Document;
use crate::layout::Layout;
use std::sync::Arc;
use std::sync::atomic::{AtomicBool, Ordering};
use std::sync::mpsc::{self, Receiver};

pub struct App {
    pub doc: Document,
    pub layout: Layout,
    pub scroll_y: usize,
    pub filenames: Vec<String>,
    pub current_file_index: usize,
    pub last_pattern: String,
    pub last_search_dir: i32, // 1 for forward, -1 for backward
    pub search_failed: bool,
    pub search_wrapped: bool,
    pub show_help: bool,
    pub show_line_numbers: bool,
    pub running: bool,
    pub follow_mode: bool,
    pub is_loading: bool,
    pub terminal_cols: u16,
    pub terminal_rows: u16,
    pub error_message: Option<String>,
    pub line_receiver: Option<Receiver<String>>,
    pub stop_io: Arc<AtomicBool>,
}

impl App {
    pub fn new(filenames: Vec<String>) -> Self {
        Self {
            doc: Document::new(),
            layout: Layout::new(),
            scroll_y: 0,
            filenames,
            current_file_index: 0,
            last_pattern: String::new(),
            last_search_dir: 1,
            search_failed: false,
            search_wrapped: false,
            show_help: false,
            show_line_numbers: false,
            running: true,
            follow_mode: false,
            is_loading: false,
            terminal_cols: 0,
            terminal_rows: 0,
            error_message: None,
            line_receiver: None,
            stop_io: Arc::new(AtomicBool::new(false)),
        }
    }

    pub fn init(&mut self) {
        if !self.filenames.is_empty() {
            let filename = self.filenames[self.current_file_index].clone();
            self.start_loading_file(filename);
        } else {
            use std::io::IsTerminal;
            if !std::io::stdin().is_terminal() {
                self.start_loading_reader(std::io::stdin());
            }
        }
    }

    fn start_loading_file(&mut self, filename: String) {
        use std::fs::File;
        match File::open(&filename) {
            Ok(file) => self.start_loading_reader(file),
            Err(e) => self.error_message = Some(format!("Error opening {}: {}", filename, e)),
        }
    }

    fn start_loading_reader<R: std::io::Read + Send + 'static>(&mut self, reader: R) {
        self.stop_io.store(true, Ordering::SeqCst);
        self.stop_io = Arc::new(AtomicBool::new(false));
        let (tx, rx) = mpsc::channel();
        self.line_receiver = Some(rx);
        self.is_loading = true;
        Document::spawn_reader(reader, tx, Arc::clone(&self.stop_io));
    }

    pub fn switch_file(&mut self, index: usize) {
        if let Some(filename) = self.filenames.get(index).cloned() {
            self.current_file_index = index;
            self.doc.clear();
            self.scroll_y = 0;
            self.start_loading_file(filename);
            self.layout.compute(&self.doc, self.terminal_cols);
        }
    }
}
