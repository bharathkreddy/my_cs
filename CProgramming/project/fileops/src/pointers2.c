#include <stdio.h>
#include <stdlib.h>

void copyStr(const char *f, char *t){
    for( ; *f != '\0'; ++f, ++t )
        *t = *f;
}

int strLenP(const char *f){
    const char *p = f; // points to first memory in array
    while(*p){
        printf("%c\n", *p);
        p++;
    }
    return p-f;
}

int main(){
    const char arr[] = "a string";
    char const *pArr = arr;
    char const *pArrEnd = &arr[sizeof(arr)-1];
    printf("arr: %s, of size: %lu\n", arr, sizeof(arr));
    printf("start of arr: %c, its addr:  %p\n", *pArr, pArr);
    printf("end of arr: %c, its addr:  %p\n", *pArrEnd, pArrEnd);

    while(pArr != pArrEnd){
        printf("Pointer points to -> %c, its address: %p\n",*pArr, pArr);
        pArr++;
    }

    const char from[] = "bharath";
    char *to = malloc(sizeof(from));
    to[sizeof(from)-1] = '\0';
    printf("%s\n", to);
    copyStr(from, to);
    printf("%s\n", to);
    free(to);

    int cnt = strLenP(from);
    printf("len of str: %d\n", cnt);
}
