#include "terminal.h"
#include <unistd.h>
#include <string.h>

void terminal_enter_alt_buffer(void) {
    const char *s = "\x1b[?1049h";
    write(STDOUT_FILENO, s, strlen(s));
}

void terminal_exit_alt_buffer(void) {
    const char *s = "\x1b[?1049l";
    write(STDOUT_FILENO, s, strlen(s));
}

void terminal_hide_cursor(void) {
    const char *s = "\x1b[?25l";
    write(STDOUT_FILENO, s, strlen(s));
}

void terminal_show_cursor(void) {
    const char *s = "\x1b[?25h";
    write(STDOUT_FILENO, s, strlen(s));
}

void terminal_clear(void) {
    const char *s = "\x1b[2J\x1b[H";
    write(STDOUT_FILENO, s, strlen(s));
}
