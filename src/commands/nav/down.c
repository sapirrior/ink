#include "nav.h"
#include "../../app/state.h"

void cmd_nav_down(AppState *app) {
    int view_height = app->ts.rows - 1;
    if (app->scroll_y + view_height < (int)app->layout.count) {
        app->scroll_y++;
    }
}
