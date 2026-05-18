use std::fmt;
use std::io;

#[derive(Debug)]
pub enum InklessError {
    Io(io::Error),
    Terminal(String),
}

impl fmt::Display for InklessError {
    fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {
        match self {
            Self::Io(err) => write!(f, "I/O Error: {}", err),
            Self::Terminal(msg) => write!(f, "Terminal Error: {}", msg),
        }
    }
}

impl std::error::Error for InklessError {}

impl From<io::Error> for InklessError {
    fn from(err: io::Error) -> Self {
        Self::Io(err)
    }
}
