#include <stdio.h>
#include <string.h> 
#include <stdlib.h> 
int main(){
    int maxchars;
    printf("max chars: ");
    scanf("%d", &maxchars);
    char *mystr = malloc(maxchars * sizeof(char));
    
    printf("input a string: ");
    scanf("%s", mystr);
    int slen = strlen(mystr);
    int iterations = strlen(mystr) - 1;
    for(int i=0; i<iterations; i++){
        for(int j=0,k=1; k < slen;  ++j,++k){
           if (mystr[j]> mystr[k]){
               char a = mystr[j];
               mystr[j] = mystr[k];
               mystr[k] = a;
           }
        //   printf("slen: %d\n", slen);
        //   printf("i: %d\n", i);
        //   printf("j: %d\n",j);   
        //   printf("k: %d\n",k);   
        //   printf("mystr: %s\n", mystr);
        }
        //printf("Inner loop ends\n\n");
        --slen;
    }
    free(mystr);
    return 0;
}
