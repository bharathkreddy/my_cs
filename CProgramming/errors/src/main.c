#include <stdio.h>
#include <stdlib.h>
#include <string.h>
const char* isEven(int number){
    return (number %2 == 0) ? "EVEN" : "ODD";
}
int main(void){
    char *buffer = NULL;
    size_t buffersize = 0;
    ssize_t nread;
    int n1=0, n2=0, n3=0, n4=0;

    // open file
    FILE *fp = fopen("data/numbers.txt", "r");
    if(fp == NULL){
        fprintf(stderr, "Error opening the fil\n");
        return EXIT_FAILURE;
    }

    // reading lines
    while((nread = getline(&buffer, &buffersize, fp)) != -1){
        printf("%s", buffer);
        if(sscanf(buffer, "%d %d %d %d\n", &n1, &n2, &n3, &n4) == 4){
            printf("%d is %s\n", n1, isEven(n1));
            printf("%d is %s\n", n2, isEven(n2));
            printf("%d is %s\n", n3, isEven(n3));
            printf("%d is %s\n", n4, isEven(n4));

        }else{
            printf("There are no 4 integers in the line.");
        } 
    }

    fclose(fp);
    free(buffer);
    return EXIT_SUCCESS;
}
