main: main.o matrix.o
	gcc -Wall -Wextra -pedantic -Wstrict-prototypes main.o matrix.o -o main

main.o: main.c
	gcc -Wall -Wextra -pedantic -Wstrict-prototypes -c main.c -o main.o

matrix.o: matrix.c
	gcc -Wall -Wextra -pedantic -Wstrict-prototypes -c matrix.c -o matrix.o

clean:
	rm -rf main main.o matrix.o

asan: main.o matrix.o
	gcc -Wall -Wextra -pedantic -Wstrict-prototypes -fsanitize=address -g main.o matrix.o -o main
