CC = gcc
CFLAGS = -std=c11 -Wall -Wextra -Wpedantic -Iinclude
SRC = src/main.c src/dup_str.c src/cmp_forward.c src/cleanup_fail.c src/cleanup_out_fail.c src/free_lines.c
TARGET = project_gamlet

.PHONY: all clean run

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)
