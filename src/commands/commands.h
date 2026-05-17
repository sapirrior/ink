#ifndef INK_COMMANDS_H
#define INK_COMMANDS_H

#include "../app/state.h"

typedef void (*CommandHandler)(AppState *app);

void command_dispatch(AppState *app, int key);

// Sub-module headers will be included here as they are created
#include "nav/nav.h"
#include "search/search_cmd.h"
#include "sys/sys.h"

#endif
