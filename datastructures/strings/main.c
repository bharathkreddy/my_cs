#include <stdio.h>
#include "strings.h"

int main(void)
{
    int res = -1;

    char a[] = "hello world from Bharath";
    res = findLength(a);
    printf("String created: %s\n", a);
    printf("Length: %d\n", res);
    res = countWords(a);
    printf("WordCount: %d\n", res);
    reverseString(a);
    printf("Reversed String: %s\n", a);
    
    char b[] = "bharath";
    findDuplicates(b);
}
