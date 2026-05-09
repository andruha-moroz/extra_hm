# Project Hamlet

A small C project that sorts text lines from a file in two ways:

1. Forward lexicographical order (`FORWARD`).
2. Reverse-end lexicographical order (`REVERSE`, rhyme-like grouping).

## What the Program Does

The program:

1. Reads lines from `hamlet.txt`.
2. Skips empty lines.
3. Creates two copies of the line array.
4. Sorts one copy from left to right.
5. Sorts the second copy from right to left (by line endings).
6. Writes both results to `result.txt`.

## Project Structure

```text
project_gamlet/
  include/
    Line.h
    cmp_forward.h
    dup_str.h
    cleanup_fail.h
    cleanup_out_fail.h
    soft_assert.h
  src/
    main.c
    cmp_forward.c
    dup_str.c
    cleanup_fail.c
    cleanup_out_fail.c
    soft_assert.c
  build.sh
  Makefile
  hamlet.txt
  result.txt
```

## Requirements

- `gcc` (or a C11-compatible `clang`)
- `make`
- Linux/macOS

## Build

```bash
cd /Users/andrey/Desktop/work_1/project_gamlet
make
```

Or via script:

```bash
cd /Users/andrey/Desktop/work_1/project_gamlet
./build.sh
```

## Run

```bash
cd /Users/andrey/Desktop/work_1/project_gamlet
./project_gamlet
```

## Clean

```bash
make clean
```

## Input Format

`hamlet.txt` contains plain text lines.

- Input is read line by line.
- Empty lines are ignored.
- Current line buffer limit: `4095` characters.

## Output Format

`result.txt` contains two sections:

- `FORWARD` — sorted by normal lexicographical order.
- `REVERSE` — sorted by line endings.

## Modules

- `src/main.c` — main flow: read, sort, write.
- `src/cmp_forward.c` — `cmp_forward` and `cmp_reverse` comparators.
- `src/dup_str.c` — dynamic string copy helper.
- `src/cleanup_fail.c` — cleanup on input/allocation errors.
- `src/cleanup_out_fail.c` — cleanup on output file open error.
- `include/soft_assert.h` — lightweight assert macro.

## Doxygen Style

Header files use concise doxygen comments:

- `@brief`
- `@param`
- `@return`

## Common Errors

1. `Error: File not open`
Cause: `hamlet.txt` is missing in the current run directory.

2. `calloc/realloc/dup_str` errors
Cause: memory allocation failure.
