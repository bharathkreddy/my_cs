#include <stdio.h>
#include <stdlib.h>

#include "matrix.h"

int main(void)
{
    int n = 5;
    int *a = init_diagonal_matrix(n);
    set_diagonal_matrix(a, 1, 9);
    set_diagonal_matrix(a, 2, 3);
    set_diagonal_matrix(a, 3, 7);
    set_diagonal_matrix(a, 4, 5);
    set_diagonal_matrix(a, 5, 1);

    display_diagonal_matrix(a, 5);
    free(a); 

    printf("\n\n");
    
    int *b = init_lower_triangular_matrix(5);
    set_lower_triangular_matrix(b, 1, 1, 3);
    set_lower_triangular_matrix(b, 2, 1, 6);
    set_lower_triangular_matrix(b, 2, 2, 1);
    set_lower_triangular_matrix(b, 3, 1, 5);
    set_lower_triangular_matrix(b, 3, 2, 7);
    set_lower_triangular_matrix(b, 3, 3, 6);
    set_lower_triangular_matrix(b, 4, 1, 2);
    set_lower_triangular_matrix(b, 4, 2, 9);
    set_lower_triangular_matrix(b, 4, 3, 8);
    set_lower_triangular_matrix(b, 4, 4, 7);
    set_lower_triangular_matrix(b, 5, 1, 2);
    set_lower_triangular_matrix(b, 5, 2, 9);
    set_lower_triangular_matrix(b, 5, 3, 5);
    set_lower_triangular_matrix(b, 5, 4, 6);
    set_lower_triangular_matrix(b, 5, 5, 4);
    display_lower_triangular_matrix(b, 5);
    free(b);

    struct Sparse s;
    create_sparse(&s);
    printf("\n\n");
    display_sparse(s);
    free(s.e);

    return 0;
}
