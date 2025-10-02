#include <stdio.h>
#include "stack.h"

int main(void)
{
    struct Stack *s = initStack();

    printf("Stack empty: %s\n", isEmpty(s)? "true": "false");

    push(s, 1);
    push(s, 3);
    push(s, 5);
    push(s, 7);
    push(s, 9);

    printf("Stack full: %s\n", isFull(s)? "true": "false");

    displayStack(s);
    
    printf("\nPeek element @index 9: %d\n", peek(s, 9));
    printf("\nPeek element @index 3: %d\n", peek(s, 3));

    printf("\nPoped: %d\n", pop(s));
    displayStack(s);
    
    printf("\nStack Top: %d\n", stackTop(s));

    freeStack(&s);

    // stack linked list
    printf("\n====Stack using Linked List=====\n");
    struct StackLL *stack = initStackLL();
    pushLL(stack, 3);
    pushLL(stack, 5);
    pushLL(stack, 8);
    pushLL(stack, 9);

    printf("Stack Empty: %s\n", (isEmptyLL(stack)) ? "True":"False");
    
    displayStackLL(stack);

    printf("Pop: %d\n", popLL(stack));
    printf("Pop: %d\n", popLL(stack));

    printf("Top element: %d\n", peekLL(stack));
    displayStackLL(stack);

    freeStackLL(stack);
    return 0;
}
