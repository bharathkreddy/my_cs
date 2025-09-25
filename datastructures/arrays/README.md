# how to use test harnesses in c.

gcc -Wall -Wextra -pedantic -Wstrict-prototypes -c arrayADT.c -o arrayADT.o
gcc -Wall -Wextra -pedantic -Wstrict-prototypes -c main.c -o main.o
gcc -Wall -Wextra -pedantic -Wstrict-prototypes arrayADT.o main.o -o main

gcc -Wall -Wextra -pedantic -Wstrict-prototypes -c tests.c -o tests.o
gcc -Wall -Wextra -pedantic -Wstrict-prototypes arrayADT.o tests.o -o tests


