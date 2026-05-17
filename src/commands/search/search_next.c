#include "search_cmd.h"
#include "../../app/state.h"
#include "../../utils/utils.h"

void cmd_search_next(AppState *app) {
    utils_do_search(app, app->last_pattern, app->last_search_dir);
}
