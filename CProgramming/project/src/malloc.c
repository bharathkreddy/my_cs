#include <stdio.h>
#include <stdlib.h> 

int main(){
    int numChars = 0;
    printf("Enter the no of chars: ");
    scanf("%d", &numChars);
    
    char *myArr = malloc((numChars+1) * sizeof(*myArr));
    if(! *myArr)
        return 0;

    printf("Enter your string: ");
    scanf("%s", myArr);
    // myArr[numChars+1] = '\0';

    printf("Here is your array: %s", myArr);

    free(myArr);
    myArr = NULL;

}
