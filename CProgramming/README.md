1. [Makefile](./makecompilation/readme.md):
2. | <br>Data type                    | format | Size (bits) | Suffix for Constants     | Example Constant       |
   | -------------------------------- | ------ | ----------- | ------------------------ | ---------------------- |
   | `char`                           | `%c`   | 8           | none                     | `'A'`                  |
   | `signed char`                    | `%c`   | 8           | none                     | `'B'`                  |
   | `unsigned char`                  | `%c`   | 8           | none                     |                        |
   | `short int`                      | `%hd`  | 16          | none                     |                        |
   | `unsigned short int`             | `%hu`  | 16          | none                     |                        |
   | `int`                            | `%d`   | 32          | none                     | `12345`                |
   | `unsigned int`                   | `%u`   | 32          | `u` or `U`               | `12345u`, `12345U`     |
   | `long int`                       | `%ld`  | 32 or 64    | `l` or `L`               | `12345l`, `12345L`     |
   | `unsigned long int`              | `%lu`  | 32 or 64    | `ul`/`UL`/`lu`/`LU`      | `12345ul`, `12345LU`   |
   | `long long int`                  | `%lld` | 64          | `ll` or `LL`             | `12345ll`, `12345LL`   |
   | `unsigned long long int`         | `%llu` | 64          | `ull` or `ULL`           | `12345ull`, `12345ULL` |
   | `float`                          | `%f`   | 32          | `f` or `F`               | `3.14f`, `2.7F`        |
   | `double`                         | `%lf`  | 64          | none                     | `3.14159`              |
   | `long double`                    | `%Lf`  | 128\*       | `l` or `L` (after value) | `3.14159L`             |
   | `_Bool` / `bool` (`<stdbool.h>`) | `%d`   | 8           | none                     | `1`, `0`               |


make
→ Compiles all .c to .o in obj/, links into run/program (default release build with optimizations).

make debug
→ Same build, but adds -g -O0 (good for gdb/lldb debugging, disables optimizations).

make release
→ Adds -O2 optimizations (fast build for production).

make clean
→ Deletes .o files and final binary.


```
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

```


# PROJECTS
1. [Playlist](./project/playlist)
2. [Web Browser Simulation](./project/webbrowser/README.md) 
3. [Hospital Emergency System](./project/hospitalEmergencySystem/README.md)
4. [File System Explorer](./project/fileSystemExplorer/README.md)
5. [Advanced Text Editor](./project/textEdit/README.md)
6. Shell 
4. Multi-threaded HTTP server. + Chat messenger.
5. compiler
6. simple game (snake game)
