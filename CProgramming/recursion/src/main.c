#include <stdio.h>

int recAdd(int num){
    if(num ==1 ) return 1;

    return (num + recAdd(num-1));
}

int main(void){
    int num = 5;
    printf("recAdd(%d): %d\n", num, recAdd(5));
}
