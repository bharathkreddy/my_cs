CC := gcc
STD := -std=c11
WARNINGS := -Wall -Wextra -pedantic -Wstrict-prototypes
MODE ?= debug

ifeq ($(MODE),debug)
  CFLAGS := $(STD) $(WARNINGS) -g -O0 -fsanitize=address
else ifeq ($(MODE),release)
  CFLAGS := $(STD) $(WARNINGS) -O2 -DNDEBUG
endif

# Source files in src/
SRC := $(wildcard src/*.c)

# Object files in build/
OBJ := $(patsubst src/%.c,build/%.o,$(SRC))

# Executables in main folder
EXE := $(patsubst src/%.c,%,$(SRC))

# Dependency files in build/
DEP := $(patsubst src/%.c,build/%.d,$(SRC))

# Main target
all: $(EXE)

# Create build directory
build/:
	@mkdir -p $@

# Compile .c to .o
build/%.o: src/%.c | build/
	@echo "📝 Compiling $< -> $@"
	@$(CC) $(CFLAGS) -M -MT $@ $< > $(patsubst %.o,%.d,$@)
	@$(CC) $(CFLAGS) -c $< -o $@

# Link .o to executable
%: build/%.o | build/
	@echo "🔗 Linking $< -> $@"
	@$(CC) $(CFLAGS) -fsanitize=address $< -o $@

# Include dependency files
-include $(DEP)

# Clean
.PHONY: clean
clean:
	@echo "🧹 Cleaning build folder and executables"
	@rm -rf build/ $(EXE) $(DEP)

.PHONY: all
