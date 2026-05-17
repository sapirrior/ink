#include "commands.h"
#include "../input/input.h"

void command_dispatch(AppState *app, int key) {
    switch (key) {
        case KEY_UP:              cmd_nav_up(app); break;
        case KEY_DOWN:            cmd_nav_down(app); break;
        case KEY_PAGE_UP:         cmd_nav_page_up(app); break;
        case KEY_PAGE_DOWN:       cmd_nav_page_down(app); break;
        case KEY_HALF_UP:         cmd_nav_half_up(app); break;
        case KEY_HALF_DOWN:       cmd_nav_half_down(app); break;
        case KEY_HOME:            cmd_nav_home(app); break;
        case KEY_END:             cmd_nav_end(app); break;
        case KEY_SEARCH_FORWARD:  cmd_search_forward(app); break;
        case KEY_SEARCH_BACKWARD: cmd_search_backward(app); break;
        case KEY_SEARCH_NEXT:     cmd_search_next(app); break;
        case KEY_SEARCH_PREV:     cmd_search_prev(app); break;
        case KEY_QUIT:            cmd_sys_quit(app); break;
    }
}
