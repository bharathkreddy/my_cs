#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int A[5];
    printf("===int A[5]====\n");
    for(int i = 0; i < 5; ++i){
        printf("value at A[%d] is %d and its address is %p\n", i, A[i], (void *)&A[i]);
    }

    int B[5] = {1, 2, 3, 4, 5};
    printf("\n===int B[5]====\n");
    for(int i = 0; i < 5; ++i){
        printf("value at B[%d] is %d and its address is %p\n", i, B[i], (void *)&B[i]);
    }

    int C[5] = {2, 4, 6};
    printf("\n===int C[5]====\n");
    for(int i = 0; i < 5; ++i){
        printf("value at C[%d] is %d and its address is %p\n", i, C[i], (void *)&C[i]);
    }

    int D[5] = {0};
    printf("\n===int D[5]====\n");
    for(int i = 0; i < 5; ++i){
        printf("value at D[%d] is %d and its address is %p\n", i, D[i], (void *)&D[i]);
    }

    int E[] = {1, 2, 3, 4, 5};
    printf("\n===int E[5]====\n");
    for(int i = 0; i < 5; ++i){
        printf("value at E[%d] is %d and its address is %p\n", i, E[i], (void *)&E[i]);
    }

    /* resizing memory in heap; same principle for stack */

    int *p;
    int *q;

    p = (int *) malloc(5 * sizeof(int));
    p[0] = 1;
    p[1] = 2;
    p[2] = 3;
    p[3] = 4;
    p[4] = 5;

    for(int i = 0; i < 5; i++)
        printf("%d~", p[i]);

    /* provision a new array or larger size */
    q = (int *) malloc(10 * sizeof(int));
    for(int i = 0; i < 5; i++)
        q[i] = p[i];

    free(p);
    p = q;
    q = NULL;

    p[5] = 6;
    p[6] = 7; 

    for(int i = 0; i < 10; i++)
        printf("%d~", p[i]);

    /* this is exactly what realloc function does */

    /* 2D array, with main array of pointers on stack and rest on heap */

    int *b[3];
    b[0] = (int*) malloc(4 * sizeof(int));
    b[1] = (int*) malloc(4 * sizeof(int));
    b[2] = (int*) malloc(4 * sizeof(int));

    printf("\n====2D Array====\n");
    for(int i = 0; i < 3; i++)
    {
        for(int j = 0; j < 4; j++)
            printf("%d\t", b[i][j]);
        printf("\n");
    }

    printf("\n====Addr of the Array====\n");
    for(int i = 0; i < 3; i++)
    {
        for(int j = 0; j < 4; j++)
            printf("%p\t", (void *)&b[i][j]);
        printf("\n");
    }
    free(b[0]);
    free(b[1]);
    free(b[2]);

    /* 2D array with everything in heap */
    int **c;
    c = (int **) malloc(3 * sizeof(int *));
    c[0] = (int *) malloc(4 * sizeof(int));
    c[1] = (int *) malloc(4 * sizeof(int));
    c[2] = (int *) malloc(4 * sizeof(int));

    printf("\n====2D Array====\n");
    for(int i = 0; i < 3; i++)
    {
        for(int j = 0; j < 4; j++)
            printf("%d\t", c[i][j]);
        printf("\n");
    }

    printf("\n====Addr of the Array====\n");
    for(int i = 0; i < 3; i++)
    {
        for(int j = 0; j < 4; j++)
            printf("%p\t", (void *)&c[i][j]);
        printf("\n");
    }
    free(c[0]);
    free(c[1]);
    free(c[2]);
    free(c);

    return 0;
}
