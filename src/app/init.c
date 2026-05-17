#include "app.h"
#include <string.h>

AppState *g_app = NULL;

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

void app_cleanup(AppState *app) {
    terminal_restore(&app->ts);
    doc_free(&app->doc);
    layout_free(&app->layout);
    g_app = NULL;
}
