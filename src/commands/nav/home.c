#include "nav.h"
#include "../../app/state.h"

void cmd_nav_home(AppState *app) {
    app->scroll_y = 0;
}
