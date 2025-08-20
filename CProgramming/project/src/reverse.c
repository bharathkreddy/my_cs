#include <stdio.h>
#include <string.h> 

int main(){

    char inputString[50];
    printf("enter the str you want to invert > \n");
    scanf("%s", inputString);

    int cnt = strnlen(inputString, 50);

    printf("Count: %d\n\n", cnt);
    char outputString[cnt +1];
    for(int i=0; i<cnt; ++i){
        outputString[i] = inputString[cnt -1 -i];
    }
    outputString[cnt] = '\0';
    printf("%s\n",outputString);
    return 0;
}
