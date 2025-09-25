#include <stdio.h>
#include "strings.h"

int findLength(char a[])
{
    int len = 0;
    while(a[len] != '\0'){
        len++;
    }
    return len;
}

int countWords(char a[])
{
    int i = 0;
    int wordCount = 0;
    while(a[i] != '\0'){
        if(a[i] == ' ' && a[i+1] != ' ' && a[i+1] != '\0') {
            wordCount++;
        }
        i++;
    }
    return wordCount++;
}

void reverseString(char a[])
{
    int i, j;
    for(j=0; a[j] != '\0'; j++){
      // do nothing;  
    }
    j--; //brings j to last char before null pointer

    for(i=0; i < j; i++,j--){
        char t = a[i];
        a[i] = a[j];
        a[j] = t;
    }
}

