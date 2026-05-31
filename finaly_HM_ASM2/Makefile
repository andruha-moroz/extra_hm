CC = gcc
ASM = nasm

TARGET = integral
BUILD_DIR = build

CFLAGS = -m32 -std=c11 -Wall -Wextra -Werror -O2
CPPFLAGS = -Iinclude -Iinclude/Common -Iinclude/ComputationalModule -Iinclude/IO -Iinclude/RuntimeASMFLAGS = -f elf32
LDFLAGS = -m32
LDLIBS = -lm

C_SOURCES = \
	src/main.c \
	src/ComputationModule/comp.c \
	src/IO/io.c \
	src/Runtime/rt.c

ASM_SOURCES = \
	src/ComputationModule/functions.asm

C_OBJECTS = $(patsubst src/%.c,$(BUILD_DIR)/%.o,$(C_SOURCES))
ASM_OBJECTS = $(patsubst src/%.asm,$(BUILD_DIR)/%.o,$(ASM_SOURCES))

OBJECTS = $(C_OBJECTS) $(ASM_OBJECTS)

.PHONY: all clean test

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) $(LDLIBS) -o $(TARGET)

$(BUILD_DIR)/%.o: src/%.c
	mkdir -p $(dir $@)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/%.o: src/%.asm
	mkdir -p $(dir $@)
	$(ASM) $(ASMFLAGS) $< -o $@

ttest: all
	./integral --test-root 1:2:0.0:3.0:0.0001:2.0
	./integral --test-root 3:2:1.0:2.0:0.0001:1.4142135624
	./integral --test-root 3:1:0.5:1.5:0.0001:1.0
	./integral --test-integral 1:0.0:1.0:0.0001:0.5
	./integral --test-integral 2:0.0:1.0:0.0001:2.0
	./integral --test-integral 3:0.0:1.0:0.0001:0.3333333333

clean:
	rm -rf $(BUILD_DIR) $(TARGET)
