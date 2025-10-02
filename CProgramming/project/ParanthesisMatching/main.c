#include <stdio.h>
#include "bm.h"


int main(void)
{
    char buff[128];
    
    printf("Enter the expression you want to evaluate.\n");
    fgets(buff, sizeof(buff), stdin);
    
    printf("Expression: %s, is %s balanced\n", buff, (isBalanced(buff))? "Indeed" : "not");

    return 0;
}
