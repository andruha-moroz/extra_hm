#pragma once

#include "Line.h"

/**
 * @brief Case-insensitive lexicographical comparator.
 * @param element_1 First element.
 * @param element_2 Second element.
 * @return <0, 0, >0 for qsort.
 */
int cmp_forward(const void *element_1, const void *element_2);

/**
 * @brief Case-insensitive reverse-end comparator.
 * @param element_1 First element.
 * @param element_2 Second element.
 * @return <0, 0, >0 for qsort.
 */
int cmp_reverse(const void *element_1, const void *element_2);
