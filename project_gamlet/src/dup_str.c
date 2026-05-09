#include <stdlib.h>
#include <string.h>

#include "../include/dup_str.h"

char *dup_str(const char *src) {
    size_t len = strlen(src) + 1;
    char *dst = (char *)calloc(len, 1);
    if (!dst) {
        return NULL;
    }
    memcpy(dst, src, len);
    return dst;
}
