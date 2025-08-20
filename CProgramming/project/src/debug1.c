#include <stdio.h>


int main(void){
    int number = 0;
    int *p = NULL;

    number = 10;
    p = &number;

    printf("Value of number: %i\n", number);
    printf("Addr of number: %p\n\n", &number);
    
    printf("Value at p: %d\n", *p);
    printf("Addr of p: %p\n", &p);
    printf("Value of p: %p\n", p);
    printf("Size of p: %lu bytes\n", sizeof(p));

    *p = 5;


    return 0;

}
