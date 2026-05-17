#ifndef INK_COMMANDS_SEARCH_H
#define INK_COMMANDS_SEARCH_H

typedef struct AppState AppState;

void cmd_search_forward(AppState *app);
void cmd_search_backward(AppState *app);
void cmd_search_next(AppState *app);
void cmd_search_prev(AppState *app);

#endif
