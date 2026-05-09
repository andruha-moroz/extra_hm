#include <stdlib.h>

#include "../include/free_lines.h"

void free_lines(Line *lines, size_t count) {
    for (size_t i = 0; i < count; i++) {
        free(lines[i].ptr);
    }
    free(lines);
}
