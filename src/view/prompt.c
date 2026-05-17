#include "view.h"
#include "../app/state.h"
#include "../input/input.h"
#include <stdio.h>
#include <string.h>

void view_read_prompt(AppState *app, char prompt_char, char *buf, size_t size) {
    size_t len = 0;
    buf[0] = '\0';

    while (1) {
        RenderBuf rb;
        rb_init(&rb);
        rb_printf(&rb, "\x1b[%d;1H\x1b[2K%c%s", app->ts.rows, prompt_char, buf);
        rb_flush(&rb);
        rb_free(&rb);

        int c = input_read_key();
        if (c == '\r' || c == '\n') break;
        if (c == '\x1b') { len = 0; buf[0] = '\0'; break; }
        if (c == 127 || c == 8) { // Backspace
            if (len > 0) buf[--len] = '\0';
        } else if (c >= 32 && c < 127 && len < size - 1) {
            buf[len++] = (char)c;
            buf[len] = '\0';
        }
    }
}
