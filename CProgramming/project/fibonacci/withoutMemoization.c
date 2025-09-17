#include <stdio.h>

int 
rfib(int n)
{
    if(n == 0)
        return 0;
    if(n == 1)
        return 1;
    return rfib(n-2) + rfib(n-1);
}

int 
main(void)
{
    int result = 0;
    int n;
    printf("Enter n:");
    scanf("%d", &n);

    result = rfib(n);

    printf("Sum of first %d, fibonacci numbers is: %d", n, result);

    return 0;
}
