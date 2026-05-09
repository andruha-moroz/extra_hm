#include <stdio.h>
#include <stdlib.h>

#include "../include/cleanup_out_fail.h"

int cleanup_out_fail(Line *fwd, Line *rev, Line *lines, size_t n) {
    perror("fopen output");
    free(fwd);
    free(rev);
    for (size_t i = 0; i < n; i++) {
        free(lines[i].ptr);
    }
    free(lines);
    return 1;
}
