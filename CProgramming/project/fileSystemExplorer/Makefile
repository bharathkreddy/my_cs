# make           # build release binary
# make debug     # build debug binary
# make release   # rebuild release with optimizations
# make clean     # clean up build


# --- Compiler and flags ---
CC      := gcc
CFLAGS  := -Wall -Wextra -Werror -pedantic -std=c11
DEBUGFLAGS := -g -O0
RELEASEFLAGS := -O2

# --- Folders ---
SRC_DIR := src
OBJ_DIR := obj
BIN_DIR := run
INC_DIR := include

# --- Files ---
SRCS := $(wildcard $(SRC_DIR)/*.c)
OBJS := $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRCS))
TARGET := $(BIN_DIR)/program

# --- Default build (release) ---
all: $(TARGET)

# --- Build target ---
$(TARGET): $(OBJS) | $(BIN_DIR)
	$(CC) $(CFLAGS) $(OBJS) -o $@

# --- Compile each .c -> .o ---
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -I$(INC_DIR) -c $< -o $@

# --- Debug build ---
debug: CFLAGS += $(DEBUGFLAGS)
debug: clean $(TARGET)

# --- Release build ---
release: CFLAGS += $(RELEASEFLAGS)
release: clean $(TARGET)

# --- Create folders if missing ---
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

# --- Clean up ---
clean:
	rm -rf $(OBJ_DIR)/*.o $(TARGET)

