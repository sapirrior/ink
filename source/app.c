#include "ink.h"

AppState *g_app = NULL;

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

void app_init(AppState *app, const char *filename) {
    app->filename = filename;
    doc_init(&app->doc);
    doc_load_file(&app->doc, filename);
    
    app->scroll_y = 0;
    app->resize_pending = 0;
    app->last_pattern[0] = '\0';
    app->last_search_dir = 1;
    app->running = true;

    terminal_setup(&app->ts);
    layout_init(&app->layout);
    layout_compute(&app->layout, &app->doc, app->ts.cols);
    
    g_app = app;
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

void app_cleanup(AppState *app) {
    terminal_restore(&app->ts);
    doc_free(&app->doc);
    layout_free(&app->layout);
    g_app = NULL;
}
