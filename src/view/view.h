#ifndef INK_VIEW_H
#define INK_VIEW_H

#include <stddef.h>

// Forward declaration
typedef struct AppState AppState;

typedef struct {
    char *data;
    size_t len;
    size_t cap;
} RenderBuf;

void rb_init(RenderBuf *rb);
void rb_append(RenderBuf *rb, const char *s, size_t len);
void rb_printf(RenderBuf *rb, const char *fmt, ...);
void rb_flush(RenderBuf *rb);
void rb_free(RenderBuf *rb);

void view_render_screen(AppState *app);
void view_read_prompt(AppState *app, char prompt_char, char *buf, size_t size);

#endif
