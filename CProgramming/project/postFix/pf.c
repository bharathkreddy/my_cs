#include <stdio.h>
#include <stdlib.h>

#include "pf.h"

void push(struct Stack *s, int element)
{
    struct Node *current = (struct Node *)malloc(sizeof(struct Node));
    if(!current){
        printf("Memory allocation error.\n");
        return;
    }
    current->data = element;
    current->next = s->top;
    s->top = current;
}

char pop(struct Stack *s)
{
    if(!s->top) return '\0'; // underflow
    struct Node *current = s->top;
    s->top = current->next;
    char result = current->data;
    free(current);
    return result;
}

void freeStack(struct Stack *s)
{
    struct Node *current = s->top;
    while(s->top)
    {
        s->top = current->next;
        free(current);
        current = s->top;
    }
    free(s);
}

int isOperand(char c)
{
    if(c != '+' && c != '-' && c != '*' && c != '/'&& c != '(' && c != ')') {
        return 1;
    } else {
        return 0;
    }
}

int isOperator(char c)
{
    if(c == '+' || c == '-' || c == '*' || c == '/'){
        return 1;
    } else {
        return 0;
    }
}

int precedence(char op){
    switch (op) {
        case '+':
        case '-': return 1;
        case '*':
        case '/': return 2;
        case '^': return 3;
    }
    return 0;
}

char *pfix(char *infix)
{
    char *postfix = malloc(1024 * sizeof(char));
    if(!postfix){
        printf("Memory allocation error.\n");
        return NULL;
    }

    // init stack
    struct Stack *s = (struct Stack *)malloc(sizeof(struct Stack));
    if(!s){
        printf("Memory allocation error.\n");
        return NULL;
    }
    s->top = NULL;

    // move infix to stack
    int j = 0;
    for(int i = 0; infix[i] != '\0'; ++i){
        if(isOperand(infix[i])){
            postfix[j++] = infix[i];
        } else if (infix[i] == '(') {
            push(s, infix[i]);
        } else if (infix[i] == ')') {
            while(s->top && s->top->data != '(') {
                postfix[j++] = pop(s);
            }
            pop(s);
        } else if (isOperator(infix[i])) {
            while (s->top && (precedence(s->top->data) >= precedence(infix[i]))){
                postfix[j++] = pop(s);
            }
            push(s, infix[i]);
        }
    }

    while(s->top != NULL){
        postfix[j++] = pop(s);
    }

    postfix[j] = '\0';

    freeStack(s);

    return postfix;
}
