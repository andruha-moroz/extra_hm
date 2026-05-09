#include <ctype.h>
#include <string.h>

#include "../include/cmp_forward.h"

int cmp_forward(const void *element_1, const void *element_2) {
    const char *ptr_a = ((const Line *)element_1)->ptr;
    const char *ptr_b = ((const Line *)element_2)->ptr;

    while (*ptr_a && *ptr_b) {
        unsigned char elm_a = (unsigned char)tolower((unsigned char)*ptr_a);
        unsigned char elm_b = (unsigned char)tolower((unsigned char)*ptr_b);
        if (elm_a < elm_b) {
            return -1;
        }
        if (elm_a > elm_b) {
            return 1;
        }
        ptr_a++;
        ptr_b++;
    }

    if (!*ptr_a && !*ptr_b) {
        return 0;
    }
    return *ptr_a ? 1 : -1;
}

int cmp_reverse(const void *element_1, const void *element_2) {
    const char *ptr_a = ((const Line *)element_1)->ptr;
    const char *ptr_b = ((const Line *)element_2)->ptr;

    size_t len_a = strlen(ptr_a);
    size_t len_b = strlen(ptr_b);

    while (len_a > 0 && len_b > 0) {
        unsigned char elm_a = (unsigned char)tolower((unsigned char)ptr_a[len_a - 1]);
        unsigned char elm_b = (unsigned char)tolower((unsigned char)ptr_b[len_b - 1]);
        if (elm_a < elm_b) {
            return -1;
        }
        if (elm_a > elm_b) {
            return 1;
        }
        len_a--;
        len_b--;
    }

    if (len_a == 0 && len_b == 0) {
        return 0;
    }
    return (len_a == 0) ? -1 : 1;
}
