#include "sys.h"
#include "../../app/state.h"

void cmd_sys_quit(AppState *app) {
    app->running = false;
}
