#pragma once

#include <stddef.h>

#include "Line.h"

/**
 * @brief Free buffers on output-open failure.
 * @param fwd Forward-sorted lines.
 * @param rev Reverse-sorted lines.
 * @param lines Original lines.
 * @param n Number of initialized lines.
 * @return Always 1.
 */
int cleanup_out_fail(Line *fwd, Line *rev, Line *lines, size_t n);
