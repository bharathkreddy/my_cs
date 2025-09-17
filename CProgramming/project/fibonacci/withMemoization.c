/* finonacci series with memoization */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int *z;

int 
rfib(int n)
{
    if(n <= 1){
        z[n] = n;
        return n;
    }

    if(z[n-2] == -1)
        z[n-2] = rfib(n-2);

    if(z[n-1] == -1)
        z[n-1] = rfib(n-1);

    return z[n-2] + z[n-1]; 
}

int 
main(void)
{
    int result = 0;
    int n;
    
    printf("Enter n:");
    scanf("%d", &n);

    z = (int *) malloc((n+1) * sizeof(int));
    if(!z) {printf("Error allocating memory."); exit(EXIT_FAILURE);}
    memset(z, -1, (n+1) * sizeof(int));

    result = rfib(n);

    printf("The %dth, fibonacci numbers is: %d", n, result);

    return 0;
}
