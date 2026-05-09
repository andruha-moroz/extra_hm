#pragma once

#include <stddef.h>

#include "Line.h"

/**
 * @brief Free line strings and line buffer.
 * @param lines Lines buffer.
 * @param count Number of initialized lines.
 */
void free_lines(Line *lines, size_t count);
