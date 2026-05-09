#pragma once

#include <stdio.h>

/**
 * @brief Return from function if condition is false.
 */
#define soft_assert(condition, error_message, return_value) \
    do { \
        if (!(condition)) { \
            fprintf(stderr, "Error: %s\\n", (error_message)); \
            return (return_value); \
        } \
    } while (0)
