#include "stack.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

struct Stack* initStack(void) {
    struct Stack* s = (struct Stack*)malloc(sizeof(struct Stack));
    if (!s) return NULL;  // memory allocation error.

    s->size = 5;
    s->top = -1;
    s->s = malloc(s->size * sizeof(int));
    if (!s->s) {
        free(s);  // cleanup
        return NULL;
    }
    printf("\n===Stack created and pointer returned===\n");
    return s;
}

void displayStack(struct Stack* s) {
    printf("\n===Displaying the stack===\n");
    if (s->top == -1) 
    {
        printf("No data to show.\n");
    } 
    else 
    {
        for (int i = 0; i <= s->top; ++i) 
        {
            printf("%d(%p) ", s->s[i], (void*)&s->s[i]);
        }
        printf("\n");
    }
}

void push(struct Stack *s, int element)
{
    if(s->top == s->size - 1){
        printf("Stack overflow! cannot push %d.\n", element);
        return;
    }
    s->top++;
    s->s[s->top] = element;
    printf("Element %d pushed and now top at %d\n", element, s->top);
}

int pop(struct Stack *s)
{
    if(s->top == -1){
        printf("no elements to pop.\n");
        return -1   ;
    }
    int popedElement = s->s[s->top];
    s->top--;
    return popedElement;
}

int peek(struct Stack *s, int index)
{
    if(index > s->top)
    {
        printf("Index out of bounds. Stack top at: %d", s->top);
        return -1;
    }    
    return s->s[index];
}

int stackTop(struct Stack *s)
{
    if(s->top == -1)
    {
        printf("No Elements.\n");
        return -1;
    }
    return s->s[s->top];
}

bool isEmpty(struct Stack *s)
{
    return (s->top == -1) ? true : false;
}

bool isFull(struct Stack *s)
{
    return (s->top == s->size -1) ? true : false;
}

void freeStack(struct Stack** s) {
    if (s && *s) {
        free((*s)->s);
        free(*s);
        *s = NULL;
    }
}

struct StackLL* initStackLL(void)
{
    struct StackLL *stack = (struct StackLL *)malloc(sizeof(struct StackLL));
    if(!stack) return NULL;
    stack->top = NULL;
    return stack;
}

int isEmptyLL(struct StackLL *stack)
{
    return stack->top == NULL;
}

void pushLL(struct StackLL *stack, int value)
{
    struct Node *node = (struct Node *)malloc(sizeof(struct Node));
    if(!node) {
        printf("Memory allocation failed.\n");
        return;
    }
    node->data = value;
    node->next = stack->top;
    stack->top = node;
    printf("Pushed %d\n", value);
}

int popLL(struct StackLL *stack)
{
    if(isEmptyLL(stack)){
        printf("Stack underflow.\n");
        return -1;
    }
    struct Node *temp = stack->top;
    int value = temp->data;
    stack->top = temp->next;
    free(temp);
    return value;
}

int peekLL(struct StackLL *stack)
{
    if(isEmptyLL(stack)){
        printf("Stack underflow.\n");
        return -1;
    }
    return stack->top->data;
}

void displayStackLL(struct StackLL *stack)
{
    if(isEmptyLL(stack)){
        printf("Stack underflow.\n");
    }
    printf("Stack (top -> bottom): ");
    struct Node *current = stack->top;
    while(current){
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

void freeStackLL(struct StackLL *stack)
{
    struct Node *current = stack->top;
    while(current){
        struct Node *next  = current->next;
        free(current);
        current = next;
    }
    free(stack);
}
