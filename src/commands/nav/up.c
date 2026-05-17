#include "nav.h"
#include "../../app/state.h"

void cmd_nav_up(AppState *app) {
    if (app->scroll_y > 0) app->scroll_y--;
}
