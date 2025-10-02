#ifndef STACK_H
#define STACK_H

#include <stdio.h>
#include <stdbool.h>

// data: 1.elements, 2. Top pointer
struct Stack
{
    int size;
    int top;
    int *s;
};

//init
struct Stack* initStack(void);
void displayStack(struct Stack *s);
void freeStack(struct Stack **s);

// Operations:
// 1. push(x)
void push(struct Stack *s, int element);

// 2. pop()
int pop(struct Stack *s);

// 3. Peek(index)
int peek(struct Stack *s, int index);

// 4. stackTop()
int stackTop(struct Stack *s);

// 5. isEmpty()
bool isEmpty(struct Stack *s);

// 6. isFull()
bool isFull(struct Stack *s);

//======linked list implementation=======//

struct Node {
    int data;
    struct Node *next;
};

struct StackLL {
    struct Node *top;
};

struct StackLL* initStackLL(void);
int isEmptyLL(struct StackLL *stack);
void pushLL(struct StackLL *stack, int value);
int popLL(struct StackLL *stack);
int peekLL(struct StackLL *stack);
void displayStackLL(struct StackLL *stack);
void freeStackLL(struct StackLL *stack);

#endif
