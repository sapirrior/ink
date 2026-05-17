#ifndef INK_APP_H
#define INK_APP_H

#include "state.h"

void app_init(AppState *app, const char *filename);
void app_run(AppState *app);
void app_cleanup(AppState *app);

// Global pointer for signal handlers
extern AppState *g_app;

#endif
