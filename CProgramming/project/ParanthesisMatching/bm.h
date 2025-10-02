#ifndef BM_H
#define BM_H

#include <stdio.h>

struct Stack{
    struct Node *top;
};

struct Node{
    char data;
    struct Node *next;
};

void displayStack(struct Stack *stack);
void push(struct Stack *stack, char element);
void cleanStack(struct Stack *stack);
int isBalanced(char *buff);
char pop(struct Stack *stack);
int isMatching(char open, char close);
int isEmpty(struct Stack *stack);

#endif
