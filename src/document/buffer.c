#include "document.h"
#include <stdlib.h>

void doc_init(Document *doc) {
    doc->raw_lines = NULL;
    doc->line_count = 0;
    doc->line_cap = 0;
}

void doc_free(Document *doc) {
    if (doc->raw_lines) {
        for (size_t i = 0; i < doc->line_count; i++) {
            free(doc->raw_lines[i]);
        }
        free(doc->raw_lines);
    }
    doc_init(doc);
}
