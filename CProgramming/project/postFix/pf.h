#ifndef PF_H
#define PF_H

#include <stdio.h>

struct Stack{
    struct Node *top;
};

struct Node{
    char data;
    struct Node *next;
};

void push(struct Stack *s, int element);
char pop(struct Stack *s);
void freeStack(struct Stack *s);
char *pfix(char * infix);
int isOperand(char c);
int isOperator(char c);
int precedence(char op);

#endif
