#include <stdio.h>

int main() {

    int x = 42;
    int *p = &x;

    printf("value of x: %d\n", x);
    printf("address of x: %d\n", &x);
    printf("value of p: %d\n", p);
    printf("address of p: %d\n", &p);
    printf("value at address in p: %d\n", *p);

    return 0;
}
