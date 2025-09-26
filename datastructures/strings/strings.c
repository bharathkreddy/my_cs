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

void findDuplicates(char a[])
{
    long int x = 0; // this is how we check for bytes on or off
    long int h = 0;

    for(int i = 0; a[i] != '\0'; ++i){
        // first we will check if char is already present in h or not
        x = 1; 
        x = x << (a[i]-97);
        if((x & h) > 0){
            printf("Duplicate: %c\n", a[i]);
        } else {
            h = x | h;
        }
    }
}
