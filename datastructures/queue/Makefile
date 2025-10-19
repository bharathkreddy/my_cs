main: main.o queue.o
	gcc -Wall -Wextra -pedantic -Wstrict-prototypes main.o queue.o -o main

main.o: main.c
	gcc -Wall -Wextra -pedantic -Wstrict-prototypes -c main.c -o main.o

queue.o: queue.c
	gcc -Wall -Wextra -pedantic -Wstrict-prototypes -c queue.c -o queue.o

clean:
	rm -rf main main.o queue.o

asan: main.o queue.o
	gcc -Wall -Wextra -pedantic -Wstrict-prototypes -fsanitize=address -g main.o queue.o -o main
