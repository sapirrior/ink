#ifndef INK_UTILS_H
#define INK_UTILS_H

#include <stddef.h>

// Forward declaration
typedef struct AppState AppState;

void ink_die(const char *fmt, ...);

// Search utility
void utils_do_search(AppState *app, const char *pattern, int dir);

#endif
