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




   1. function pointers
   2. advanced pointers
   3. variable arguments to functions
   4. dynamic linking
   5. signals, forking, and inter-process communication
   6. threading and concurrency
   7. sockets
   8. setjmp and longjmp for restoring state
   9. memory management and fragmentation
   10. making programs more portable
   11. Interfacing with kernel modules (drivers and ioctls)
   12. compiler and linker files
   13. gdb and lldb advanced usecases. 
   14. profiling and tracing tools (gprof, dtrace, strace)
   15. memory debugging like valgrind
   16. typedef
   17. void* 's
   18. static libraries and shared objects
   19. macros
   20. unions
