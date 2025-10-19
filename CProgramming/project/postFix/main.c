#include <stdio.h>
#include <string.h>
#include "pf.h"

int main(void)
{
    char infix[128];
    printf("Enter the infix expression: ");
    fgets(infix, sizeof(infix), stdin);

    // remove newline
    size_t len = strlen(infix);
    if (len > 0 && infix[len-1] == '\n') {
        infix[len-1] = '\0';
    }

    char *postfix = pfix(infix);
    printf("Postfix: %s\n", postfix);

    return 0;
}
