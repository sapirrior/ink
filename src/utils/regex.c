#include "utils.h"
#include "../app/state.h"
#include <regex.h>
#include <string.h>

void utils_do_search(AppState *app, const char *pattern, int dir) {
    if (!pattern || pattern[0] == '\0') return;
    strncpy(app->last_pattern, pattern, sizeof(app->last_pattern) - 1);
    app->last_search_dir = dir;

    regex_t regex;
    if (regcomp(&regex, pattern, REG_EXTENDED | REG_NOSUB) != 0) return;

    size_t current_raw = 0;
    for (size_t i = 0; i < app->doc.line_count; i++) {
        if (app->layout.raw_to_display[i] <= (size_t)app->scroll_y) {
            current_raw = i;
        } else {
            break;
        }
    }

    int found = -1;
    if (dir == 1) {
        for (size_t i = current_raw + 1; i < app->doc.line_count; i++) {
            if (regexec(&regex, app->doc.raw_lines[i], 0, NULL, 0) == 0) {
                found = (int)i;
                break;
            }
        }
    } else {
        if (current_raw > 0) {
            for (int i = (int)current_raw - 1; i >= 0; i--) {
                if (regexec(&regex, app->doc.raw_lines[i], 0, NULL, 0) == 0) {
                    found = i;
                    break;
                }
            }
        }
    }

    if (found != -1) {
        app->scroll_y = (int)app->layout.raw_to_display[found];
    }

    regfree(&regex);
}
