#include "terminal.h"
#include <unistd.h>
#include <sys/ioctl.h>
#include <stdlib.h>
#include <stdio.h>

void terminal_setup(TerminalState *ts) {
    if (tcgetattr(STDIN_FILENO, &ts->orig_termios) == -1) {
        perror("tcgetattr");
        exit(1);
    }

    struct termios raw = ts->orig_termios;
    raw.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);
    raw.c_oflag &= ~(OPOST);
    raw.c_cflag |= (CS8);
    raw.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG);
    raw.c_cc[VMIN] = 0;
    raw.c_cc[VTIME] = 1;

    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw) == -1) {
        perror("tcsetattr");
        exit(1);
    }

    terminal_enter_alt_buffer();
    terminal_hide_cursor();
    terminal_get_size(ts);
}

void terminal_restore(TerminalState *ts) {
    terminal_exit_alt_buffer();
    terminal_show_cursor();
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &ts->orig_termios);
}

void terminal_get_size(TerminalState *ts) {
    struct winsize ws;
    if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws) == -1 || ws.ws_col == 0) {
        ts->rows = 24;
        ts->cols = 80;
    } else {
        ts->rows = ws.ws_row;
        ts->cols = ws.ws_col;
    }
}
