CC := gcc
CFLAGS := -Wall -Wpedantic -Wextra -Wno-unused-parameter

NAME := chip8em
SOURCE_DIR := src
HEADER_DIR := include
BUILD_DIR := build

HEADERS := $(wildcard $(HEADER_DIR)/*.h)
SOURCES := $(wildcard $(SOURCE_DIR)/*.c)
# Substitute src/*.c -> build/obj/*.o
# notdir removes the src part
OBJECTS := $(addprefix $(BUILD_DIR)/, $(notdir $(SOURCES:.c=.o)))

default: $(NAME)

# $^ is all prerequisites
# $@ is target name
$(NAME): $(OBJECTS)
	@ $(CC) $(CFLAGS) $^ -o $@

# $< is leftmost prerequisite
$(BUILD_DIR)/%.o: $(SOURCE_DIR)/%.c $(HEADERS)
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) -c -o $@ $< -Iinclude

clean:
	@ rm -rf $(BUILD_DIR)
	@ rm $(NAME)

# phony targets are those targets which are the name of an action to carry out
.PHONY: default clean
