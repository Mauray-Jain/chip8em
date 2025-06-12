CC := gcc
CFLAGS := -Wall -Wpedantic -Wextra -Wno-unused-parameter

NAME := chip8em
SOURCE_DIR := src
BUILD_DIR := build
MODULES := display sound

SRCS := $(wildcard $(SOURCE_DIR)/*.c $(foreach fd, $(SOURCE_DIR)/$(MODULES), $(fd)/*.c))
HEADERS := $(wildcard $(SOURCE_DIR)/*.h $(foreach fd, $(SOURCE_DIR)/$(MODULES), $(fd)/*.h))
INC_DIRS := $(addprefix -I$(SOURCE_DIR)/, $(MODULES))
# Substitute src/* -> build/*.o
OBJECTS := $(addprefix $(BUILD_DIR)/, $(SRCS:src/%.c=%.o))

default: $(NAME)

# $^ is all prerequisites
# $@ is target name
$(NAME): $(OBJECTS)
	@ $(CC) $(CFLAGS) $^ -o $@

# $< is leftmost prerequisite
$(BUILD_DIR)/%.o: $(SOURCE_DIR)/%.c $(HEADERS)
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) -c -o $@ $< $(INC_DIRS)

clean:
	@ rm -rf $(BUILD_DIR)
	@ rm $(NAME)

# phony targets are those targets which are the name of an action to carry out
.PHONY: default clean
