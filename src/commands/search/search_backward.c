#include "search_cmd.h"
#include "../../app/state.h"
#include "../../view/view.h"
#include "../../utils/utils.h"
#include <string.h>

void cmd_search_backward(AppState *app) {
    char pattern[256];
    view_read_prompt(app, '?', pattern, sizeof(pattern));
    if (pattern[0] != '\0') {
        strncpy(app->last_pattern, pattern, sizeof(app->last_pattern) - 1);
        app->last_search_dir = -1;
        utils_do_search(app, app->last_pattern, -1);
    }
}
