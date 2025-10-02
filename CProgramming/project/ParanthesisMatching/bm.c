#include <stdio.h>
#include <stdlib.h>
#include "bm.h"

void push(struct Stack *stack, char element)
{
    struct Node *temp = (struct Node*)malloc(sizeof(struct Node));
    if(!temp){
        printf("memory allocation failure.\n");
        return;
    }
    temp->data = element;
    temp->next = stack->top;
    stack->top = temp;
}

void displayStack(struct Stack *stack)
{
    struct Node *temp = stack->top;
    while(temp){
        printf("%c ", temp->data);
        temp = temp->next;
    }
    printf("END\n\n");
}

void cleanStack(struct Stack *stack)
{
    struct Node *temp = stack->top;
    while(temp){
        stack->top = temp->next;
        free(temp);
        temp = stack->top;
    }
    temp = NULL;   
}

char pop(struct Stack *stack)
{
    if(!stack->top) return '\0';
    struct Node *temp = stack->top;
    char ret = temp->data;
    stack->top = temp->next;
    free(temp);
    return ret;
}

int isMatching(char open, char close) 
{
    return (open == '(' && close == ')') ||
           (open == '{' && close == '}') ||
           (open == '[' && close == ']');
}

int isEmpty(struct Stack *stack)
{
    return stack->top == NULL;
}

int isBalanced(char *buff)
{
    // initialize a stack
    struct Stack *stack = (struct Stack*)malloc(sizeof(struct Stack));
    if(!stack){
        printf("memory allocation failure.\n");
        return -1;
    }
    stack->top = NULL;

    // push expression into the stack
    for(int i = 0; buff[i] != '\0'; ++i){
        if(buff[i] == '(' || buff[i] == '{' || buff[i] == '['){
            push(stack, buff[i]);
        }
        else if(buff[i] == ')' || buff[i] == '}' || buff[i] == ']'){
            if(isEmpty(stack)) {
                cleanStack(stack);
                free(stack);
                return 0;
            }

            char popped = pop(stack);
            if(!isMatching(popped, buff[i])) {
                cleanStack(stack);
                free(stack);
                return 0;
            }
        }
    }

    int balanced = isEmpty(stack);
    cleanStack(stack);
    free(stack);
    return balanced;
}

