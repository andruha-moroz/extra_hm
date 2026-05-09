#pragma once

#include <stddef.h>
#include <stdio.h>

#include "Line.h"

/**
 * @brief Free line storage and close input file.
 * @param in Open input file.
 * @param lines Lines buffer.
 * @param n Number of initialized lines.
 * @return Always 1.
 */
int cleanup_fail(FILE *in, Line *lines, size_t n);
