#include "layout.h"
#include <stdlib.h>

void layout_init(Layout *layout) {
    layout->display_lines = NULL;
    layout->raw_to_display = NULL;
    layout->count = 0;
    layout->cap = 0;
}

void layout_free(Layout *layout) {
    if (layout->display_lines) {
        for (size_t i = 0; i < layout->count; i++) {
            free(layout->display_lines[i]);
        }
        free(layout->display_lines);
    }
    if (layout->raw_to_display) free(layout->raw_to_display);
    layout_init(layout);
}
