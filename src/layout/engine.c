#include "layout.h"
#include <stdlib.h>
#include <string.h>

static void layout_add_line(Layout *layout, const char *line) {
    if (layout->count >= layout->cap) {
        layout->cap = layout->cap == 0 ? 128 : layout->cap * 2;
        layout->display_lines = realloc(layout->display_lines, sizeof(char *) * layout->cap);
    }
    layout->display_lines[layout->count++] = strdup(line);
}

void layout_compute(Layout *layout, Document *doc, int cols) {
    layout_free(layout);
    layout_init(layout);

    if (doc->line_count > 0) {
        layout->raw_to_display = malloc(sizeof(size_t) * doc->line_count);
    }

    int margin = (cols * 8) / 100;
    int content_width = cols - (2 * margin);
    if (content_width <= 0) content_width = cols;

    for (size_t i = 0; i < doc->line_count; i++) {
        if (layout->raw_to_display) layout->raw_to_display[i] = layout->count;
        char *raw = doc->raw_lines[i];
        size_t len = strlen(raw);

        if (len == 0) {
            layout_add_line(layout, "");
            continue;
        }

        size_t start = 0;
        while (start < len) {
            size_t remaining = len - start;
            if (remaining <= (size_t)content_width) {
                layout_add_line(layout, raw + start);
                break;
            }

            size_t end = start + content_width;
            size_t split = end;
            while (split > start && raw[split] != ' ' && raw[split] != '-') {
                split--;
            }

            if (split == start) {
                char buf[content_width + 1];
                strncpy(buf, raw + start, content_width);
                buf[content_width] = '\0';
                layout_add_line(layout, buf);
                start += content_width;
            } else {
                size_t split_len = split - start;
                if (raw[split] == '-') split_len++; 
                
                char buf[split_len + 1];
                strncpy(buf, raw + start, split_len);
                buf[split_len] = '\0';
                layout_add_line(layout, buf);
                
                start = split;
                if (raw[split] == ' ') start++;
            }
        }
    }
}
