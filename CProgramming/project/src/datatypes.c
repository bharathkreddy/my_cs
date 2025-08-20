#include <stdio.h>
#include <stdlib.h> 
#include <stdbool.h>


int arrlen(char *p) {
    int cnt = 0;
    while (p[cnt]!= '\0'){
        cnt++;
    }
    return cnt;
}

bool arrsame(char *a , char *b){
    if(arrlen(a) != arrlen(b)){
        return false;
    }
    int i=0;
    while(a[i] != '\0'){
        if(a[i]!=b[i]){
            return false;
        }
        i++;
    }
    return true;
}

char *arrcat(char *arr1, char *arr2) {
    int newArrLen = arrlen(arr1) + arrlen(arr2) + 1;
    char *newArr = malloc(newArrLen * sizeof(char));
    if(!newArr){
        printf("Malloc failed!\n");
        return NULL;
    }
    int i = 0;
    for(int j=0 ; arr1[j] != '\0'; ++j, ++i){
        newArr[i] = arr1[j];        
    }
    for(int k=0 ; arr2[k] != '\0'; ++k, ++i){
        newArr[i] = arr2[k];
    }
    newArr[i] = '\0';
    return newArr;
}

int main(){

    char arr1[] = "hello1";
    char arr2[] = "HELLO2";
    char arr3[] = "hello1";

   // int ln = 0;
   // ln = arrlen(arr1);
   // printf("size of arr1: %d\n", ln);
   // printf("arr1 & arr3 equal:%s\n", arrsame(arr1, arr3)? "true" : "false");
   // printf("arr1 & arr2 equal:%s\n", arrsame(arr1, arr2)? "true" : "false");
   char *concatenated = arrcat(arr1, arr2);
    
   if(concatenated){
       printf("%s\n", concatenated);
       free(concatenated);
   }

    return 0;
}
