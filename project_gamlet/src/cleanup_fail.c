#include <stdlib.h>

#include "../include/cleanup_fail.h"

int cleanup_fail(FILE *in, Line *lines, size_t n) {
    fclose(in);
    for (size_t i = 0; i < n; i++) {
        free(lines[i].ptr);
    }
    free(lines);
    return 1;
}
