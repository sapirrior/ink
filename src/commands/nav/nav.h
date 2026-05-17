#ifndef INK_COMMANDS_NAV_H
#define INK_COMMANDS_NAV_H

typedef struct AppState AppState;

void cmd_nav_up(AppState *app);
void cmd_nav_down(AppState *app);
void cmd_nav_page_up(AppState *app);
void cmd_nav_page_down(AppState *app);
void cmd_nav_half_up(AppState *app);
void cmd_nav_half_down(AppState *app);
void cmd_nav_home(AppState *app);
void cmd_nav_end(AppState *app);

#endif
