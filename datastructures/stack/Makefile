main: main.o stack.o
	gcc -Wall -Wextra -pedantic -Wstrict-prototypes main.o stack.o -o main

main.o: main.c
	gcc -Wall -Wextra -pedantic -Wstrict-prototypes -c main.c -o main.o

stack.o: stack.c
	gcc -Wall -Wextra -pedantic -Wstrict-prototypes -c stack.c -o stack.o

clean:
	rm -rf main main.o stack.o

asan: main.o stack.o
	gcc -Wall -Wextra -pedantic -Wstrict-prototypes -fsanitize=address -g main.o stack.o -o main
