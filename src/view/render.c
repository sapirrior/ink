#include "view.h"
#include "../app/state.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <unistd.h>
#include <regex.h>

void rb_init(RenderBuf *rb) {
    rb->cap = 16384;
    rb->data = malloc(rb->cap);
    rb->len = 0;
    if (rb->data) rb->data[0] = '\0';
}

void rb_append(RenderBuf *rb, const char *s, size_t len) {
    if (rb->len + len >= rb->cap) {
        size_t new_cap = rb->cap * 2 + len;
        char *new_data = realloc(rb->data, new_cap);
        if (!new_data) return;
        rb->data = new_data;
        rb->cap = new_cap;
    }
    memcpy(rb->data + rb->len, s, len);
    rb->len += len;
    rb->data[rb->len] = '\0';
}

void rb_printf(RenderBuf *rb, const char *fmt, ...) {
    char buf[1024];
    va_list ap;
    va_start(ap, fmt);
    int n = vsnprintf(buf, sizeof(buf), fmt, ap);
    va_end(ap);
    if (n > 0) rb_append(rb, buf, (size_t)n);
}

void rb_flush(RenderBuf *rb) {
    if (rb->len > 0) {
        write(STDOUT_FILENO, rb->data, rb->len);
        rb->len = 0;
        rb->data[0] = '\0';
    }
}

void rb_free(RenderBuf *rb) {
    free(rb->data);
    rb->data = NULL;
    rb->len = 0;
    rb->cap = 0;
}

void view_render_screen(AppState *app) {
    RenderBuf rb;
    rb_init(&rb);

    rb_append(&rb, "\x1b[H", 3);

    int margin = (app->ts.cols * 8) / 100;
    int view_height = app->ts.rows - 1;

    regex_t regex;
    bool has_regex = false;
    if (app->last_pattern[0] != '\0' && regcomp(&regex, app->last_pattern, REG_EXTENDED) == 0) {
        has_regex = true;
    }

    for (int i = 0; i < view_height; i++) {
        int line_idx = app->scroll_y + i;
        rb_printf(&rb, "\x1b[%d;1H\x1b[2K", i + 1);

        if (line_idx < (int)app->layout.count) {
            for (int j = 0; j < margin; j++) rb_append(&rb, " ", 1);
            
            const char *line = app->layout.display_lines[line_idx];
            if (has_regex) {
                regmatch_t pmatch;
                const char *ptr = line;
                while (regexec(&regex, ptr, 1, &pmatch, 0) == 0) {
                    // Text before match
                    rb_append(&rb, ptr, (size_t)pmatch.rm_so);
                    // Match (inverted)
                    rb_append(&rb, "\x1b[7m", 4);
                    rb_append(&rb, ptr + pmatch.rm_so, (size_t)(pmatch.rm_eo - pmatch.rm_so));
                    rb_append(&rb, "\x1b[m", 3);
                    ptr += pmatch.rm_eo;
                    if (pmatch.rm_so == pmatch.rm_eo) ptr++; // Avoid infinite loop on empty matches
                    if (*ptr == '\0') break;
                }
                rb_append(&rb, ptr, strlen(ptr));
            } else {
                rb_append(&rb, line, strlen(line));
            }
        }
    }

    if (has_regex) regfree(&regex);

    rb_printf(&rb, "\x1b[%d;1H\x1b[2K", app->ts.rows);

    if (app->search_failed) {
        rb_append(&rb, "\x1b[7mPattern not found (press any key)\x1b[m", 38);
    } else {
        int current_last_line = app->scroll_y + view_height;
        if (current_last_line >= (int)app->layout.count) {
            rb_append(&rb, "\x1b[7m(END)\x1b[m", 13);
        } else {
            rb_append(&rb, ":", 1);
        }
    }

    rb_flush(&rb);
    rb_free(&rb);
}
