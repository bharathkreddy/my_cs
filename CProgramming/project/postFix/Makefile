CC = gcc
CFLAGS = -Wall -Wextra -pedantic -Wstrict-prototypes 

# Default Target
all: main

main: main.o pf.o
	$(CC) $(CFLAGS) main.o pf.o -o main

main.o: main.c
	$(CC) $(CFLAGS) -c main.c -o main.o

pf.o: pf.c
	$(CC) $(CFLAGS) -c pf.c -o pf.o

# Test target
test: test.o pf.o
	$(CC) $(CFLAGS) test.o pf.o -o tests

test.o: test.c pf.h
	$(CC) $(CFLAGS) -c test.c -o test.o

clean:
	rm -rf main main.o pf.o test.o

asan: main.o pf.o
	$(CC) $(CFLAGS) -fsanitize=address -g main.o pf.o -o main
