#include "search_cmd.h"
#include "../../app/state.h"
#include "../../view/view.h"
#include "../../utils/utils.h"

void cmd_search_forward(AppState *app) {
    char pattern[256];
    view_read_prompt(app, '/', pattern, sizeof(pattern));
    utils_do_search(app, pattern, 1);
}
