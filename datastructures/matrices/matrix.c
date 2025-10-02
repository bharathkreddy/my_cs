#include <stdio.h>
#include <stdlib.h>

#include "matrix.h"

int* init_diagonal_matrix(int n)
{
    int *a = (int *) malloc(n * sizeof(int));
    return a;
}

void set_diagonal_matrix(int *a, int i, int x)
{
    a[i-1] = x;
}

void display_diagonal_matrix(int *a, int n)
{
    for(int i = 0; i < n; ++i){
        for(int j = 0; j < n; ++j){
            if(i == j){
                printf(" %d ",a[i]);
            } else {
                printf(" %d ", 0);
            }
        }
        printf("\n");
    }
}

int * init_lower_triangular_matrix(int n)
{
    int *a = (int *) malloc((n*(n+1)/2) * sizeof(int));
    if(!a){
        printf("Error allocating memory.\n");
        exit(1);
    }
    return a;
}

void set_lower_triangular_matrix(int *a, int i, int j, int x)
{
    // |a11|a21,a22|a31,a32,a33|a41,a42,a43,a44|....
    // first row - 1 element
    // second row - 2 elements
    // third row - 3 elemnts
    // so to add a43, we need to move 3 rows then 3 elements and 
    // subtract 1 as arrays are 0 indexed and matrix is 1 indexed.

    int index = (i * (i-1) / 2) + j - 1;
    a[index] = x;
}

void display_lower_triangular_matrix(int *a, int n)
{
    for(int i=1; i <= n; i++){
        for(int j = 1; j <= n; j++){
            if (i >= j){
                int index = (i * (i-1) / 2) + j - 1;
                printf(" %d ", a[index]);
            } else {
                printf(" %d ", 0);
            }
        }
        printf("\n");
    }
}

void create_sparse(struct Sparse *s)
{
    printf("Enter dimensions of the Sparse Array (rows,colums): ");
    scanf("%d%d", &s->m, &s->n);
    printf("Enter number of non-zero elements: ");
    scanf("%d", &s->num);

    s->e = (struct Element *) malloc(s->num * sizeof(struct Element));
    printf("Enter elements (row,column,number)\n");
    for(int i = 0; i < s->num; ++i){
        scanf("%d%d%d", &s->e[i].i, &s->e[i].j, &s->e[i].x);
    }
}

void display_sparse(struct Sparse s)
{
    int k = 0;
    for(int i = 1; i <= s.m; ++i){
        for(int j = 1; j <= s.n; ++j){
            if(i==s.e[k].i && j==s.e[k].j){
                printf("%d ", s.e[k].x);
                k++;
            } else {
                printf("0 ");
            }
        }
        printf("\n");
    }
}
