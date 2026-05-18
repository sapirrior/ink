#include "ink.h"

int main(int argc, char **argv) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    AppState app;
    app_init(&app, argv[1]);
    app_run(&app);
    app_cleanup(&app);

    return 0;
}
