#include "app.h"
#include "../view/view.h"
#include "../input/input.h"
#include "../commands/commands.h"
#include <signal.h>
#include <stdlib.h>

static void handle_sigint(int sig) {
    (void)sig;
    if (g_app) {
        app_cleanup(g_app);
    }
    exit(0);
}

static void handle_sigwinch(int sig) {
    (void)sig;
    if (g_app) {
        g_app->resize_pending = 1;
    }
}

void app_run(AppState *app) {
    signal(SIGINT, handle_sigint);
    signal(SIGWINCH, handle_sigwinch);

    while (app->running) {
        if (app->resize_pending) {
            terminal_get_size(&app->ts);
            layout_compute(&app->layout, &app->doc, app->ts.cols);
            app->resize_pending = 0;
        }

        view_render_screen(app);

        int key = input_read_key();
        if (key != KEY_NONE) {
            command_dispatch(app, key);
        }
    }
}
