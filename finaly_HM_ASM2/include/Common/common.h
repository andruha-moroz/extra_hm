#ifndef COMMON_H
#define COMMON_H
#include <stdio.h>

#define soft_assert(condition, error_message, return_value) \
    do { \
        if ((condition)) { \
            fprintf(stderr, "Error: %s\n", (error_message)); \
            return (return_value); \
        } \
    } while (0)
    
#endif
