CC = gcc
CFLAGS = -fsanitize=address -Wall -g
LDFLAGS = -fsanitize=address
SRC_DIR = src
BUILD_DIR = build

SOURCES = $(wildcard $(SRC_DIR)/*.c)
EXES = $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%, $(SOURCES))

all: $(EXES)

# Each .c builds .o and links to executable of same name
$(BUILD_DIR)/%: $(SRC_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(LDFLAGS) $< -o $@

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

clean:
	rm -rf $(BUILD_DIR)

.PHONY: all clean

