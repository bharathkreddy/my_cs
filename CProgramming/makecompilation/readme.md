[make file tutorial](https://makefiletutorial.com/)

gcc -Wall -g -O0 -o hello hello.c

Flag:Purpos:Example
-Wall	Show all common warnings	gcc -Wall main.c
-o	Set output file name	gcc -o myprog main.c
-O0	No optimization (default)	gcc -O0 main.c
-O2	Optimize more (recommended for release build)	gcc -O2 main.c
-g	Add debug symbols (for debugging)	gcc -g main.c
