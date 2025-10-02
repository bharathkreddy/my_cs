#ifndef MATRIX_H
#define MATRIX_H

#include <stdio.h>

// sparse matrix
//  |1 2 3 4 5
//-------------
// 1|0 0 7 0 0  
// 2|2 0 0 5 0
// 3|9 0 0 0 0
// 4|0 0 0 0 4
//   
//  |0 1 2 3 4 5  <- total non-zero elements
// -------------
// i|4 1 2 2 3 4 <-5th nonzero is in 4th row
// j|5 3 1 4 1 5 <- 5th column
// x|5 7 2 5 9 4 <- and number is 4
// 0th col :i=no of rows in matrix; j=no of cols in matrix; x=non-zero elements. 
//

struct Element{
    int i; // row index of element
    int j; // col index of element
    int x; // number
};

struct Sparse{
    int m; //total rows in matrix
    int n; // total cols in matrix
    int num;  // total non-zero numbers
    struct Element *e;
};


int * init_diagonal_matrix(int n);
void set_diagonal_matrix(int *a, int i, int x);
void display_diagonal_matrix(int *a, int n);
int * init_lower_triangular_matrix(int n);
void set_lower_triangular_matrix(int *a, int i, int j, int x);
void display_lower_triangular_matrix(int *a, int n);
void create_sparse(struct Sparse *s);
void display_sparse(struct Sparse s);

#endif
