#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/Line.h"
#include "../include/cleanup_fail.h"
#include "../include/cleanup_out_fail.h"
#include "../include/cmp_forward.h"
#include "../include/dup_str.h"
#include "../include/soft_assert.h"

/**
 * @brief Free line strings and line buffer.
 * @param lines Lines buffer.
 * @param count Number of initialized lines.
 */
static void free_lines(Line *lines, size_t count) {
    for (size_t i = 0; i < count; i++) {
        free(lines[i].ptr);
    }
    free(lines);
}

/**
 * @brief Program entry point.
 * @return 0 on success, non-zero on failure.
 */
int main(void) {
    const char *in_name = "hamlet.txt";
    const char *out_name = "result.txt";

    FILE *in = fopen(in_name, "r");
    soft_assert(in, "File not open", 1);

    size_t capacity = 128;
    size_t count = 0;
    Line *lines = (Line *)calloc(capacity, sizeof(Line));
    soft_assert(lines, "calloc lines failed", (fclose(in), 1));

    char buf[4096];
    while (fgets(buf, sizeof(buf), in)) {
        buf[strcspn(buf, "\r\n")] = '\0';
        if (buf[0] == '\0') {
            continue;
        }

        if (count == capacity) {
            size_t new_capacity = capacity * 2;
            Line *tmp = (Line *)realloc(lines, new_capacity * sizeof(Line));
            soft_assert(tmp, "realloc failed", cleanup_fail(in, lines, count));

            memset(tmp + capacity, 0, (new_capacity - capacity) * sizeof(Line));
            lines = tmp;
            capacity = new_capacity;
        }

        lines[count].ptr = dup_str(buf);
        soft_assert(lines[count].ptr, "dup_str failed", cleanup_fail(in, lines, count));
        count++;
    }
    fclose(in);

    size_t alloc_count = (count == 0) ? 1 : count;

    Line *fwd = (Line *)calloc(alloc_count, sizeof(Line));
    if (!fwd) {
        fprintf(stderr, "Error: calloc fwd failed\n");
        free_lines(lines, count);
        return 1;
    }

    Line *rev = (Line *)calloc(alloc_count, sizeof(Line));
    if (!rev) {
        fprintf(stderr, "Error: calloc rev failed\n");
        free(fwd);
        free_lines(lines, count);
        return 1;
    }

    memcpy(fwd, lines, count * sizeof(Line));
    memcpy(rev, lines, count * sizeof(Line));

    qsort(fwd, count, sizeof(Line), cmp_forward);
    qsort(rev, count, sizeof(Line), cmp_reverse);

    FILE *out = fopen(out_name, "w");
    soft_assert(out, "File not open", cleanup_out_fail(fwd, rev, lines, count));

    fprintf(out, "=== FORWARD ===\n");
    for (size_t i = 0; i < count; i++) {
        fprintf(out, "%s\n", fwd[i].ptr);
    }

    fprintf(out, "\n=== REVERSE ===\n");
    for (size_t i = 0; i < count; i++) {
        fprintf(out, "%s\n", rev[i].ptr);
    }

    fclose(out);

    free(fwd);
    free(rev);
    free_lines(lines, count);

    return 0;
}
