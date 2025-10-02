main: main.o ll.o
	gcc -Wall -Wextra -pedantic -Wstrict-prototypes main.o ll.o -o main

main.o: main.c
	gcc -Wall -Wextra -pedantic -Wstrict-prototypes -c main.c -o main.o

ll.o: ll.c
	gcc -Wall -Wextra -pedantic -Wstrict-prototypes -c ll.c -o ll.o

clean:
	rm -rf main main.o ll.o

asan: main.o ll.o
	gcc -Wall -Wextra -pedantic -Wstrict-prototypes -fsanitize=address -g main.o ll.o -o main
