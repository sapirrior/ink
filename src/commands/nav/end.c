#include "nav.h"
#include "../../app/state.h"

void cmd_nav_end(AppState *app) {
    int view_height = app->ts.rows - 1;
    app->scroll_y = (int)app->layout.count - view_height;
    if (app->scroll_y < 0) app->scroll_y = 0;
}
