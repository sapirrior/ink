#include "inkless.h"
#include <unistd.h>

int main(int argc, char **argv) {
    if (argc < 2 && isatty(STDIN_FILENO)) {
        fprintf(stderr, "Usage: %s <filename> [filename...]\n", argv[0]);
        fprintf(stderr, "   or: <command> | %s\n", argv[0]);
        return 1;
    }

    AppState app;
    app_init(&app, argc - 1, (const char **)(argv + 1));
    app_run(&app);
    app_cleanup(&app);

    return 0;
}
