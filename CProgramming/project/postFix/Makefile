CC = gcc
CFLAGS = -Wall -Wextra -pedantic -Wstrict-prototypes 

# Default Target
all: main

main: main.o bm.o
	$(CC) $(CFLAGS) main.o bm.o -o main

main.o: main.c
	$(CC) $(CFLAGS) -c main.c -o main.o

bm.o: bm.c
	$(CC) $(CFLAGS) -c bm.c -o bm.o

# Test target
test: test.o bm.o
	$(CC) $(CFLAGS) test.o bm.o -o tests

test.o: test.c bm.h
	$(CC) $(CFLAGS) -c test.c -o test.o

clean:
	rm -rf main main.o bm.o test.o

asan: main.o bm.o
	$(CC) $(CFLAGS) -fsanitize=address -g main.o bm.o -o main
