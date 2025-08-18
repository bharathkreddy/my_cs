# Compiler and flags(Warnings all and -g: include debugging info)
CC = gcc
CFLAGS = -fsanitize=address -Wall -g
LDFLAGS = -fsanitize=address          # Add ASan for linking checks array out of bounds.

# Directories
SRC_DIR = src
BUILD_DIR = build

# Source files (wildcard path is a make function that expands to matching files)
SOURCES = $(wildcard $(SRC_DIR)/*.c)

# Object files (replace src/%.c with build/%.o)
OBJECTS = $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SOURCES))

# Executable (assuming one main executable; name it after the project or main file)
EXECUTABLE = $(BUILD_DIR)/datatypes

# Default target
all: $(EXECUTABLE)

# Link objects into executable
$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

# Compile source files into objects
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Clean build artifacts
clean:
	rm -rf $(BUILD_DIR)

# Phony targets (not actual files)
.PHONY: all clean

