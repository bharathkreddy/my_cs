#include <stdio.h>
#include <stdarg.h>

int addMultiple(int argcnt, ...){
    int counter, total =0 ;

    //declare a variable of type va_list
    va_list argptr;

    //initialize that variable
    va_start(argptr, argcnt);

    for(counter=0; counter<argcnt; counter++){

        //get next args
        total += va_arg (argptr, int);
    }

    // end use of argptr
    va_end(argptr);
    return total;
}

int main (void){
    printf("Total: %d\n", addMultiple(4, 1,3,5, 10));
    return 0;
}
