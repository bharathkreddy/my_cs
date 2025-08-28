#include <stdio.h>

#define DEBUG
#define I 4

int main(void){

    int sum = 0;

    for(int j = 0; j < I; ++j){
        sum += j+1;
        #ifdef DEBUG
            printf("SUM RUNNING: %d, J: %d\n", sum, j);
        #endif
    }
    printf("SUM: %d\n", sum);
    return 0;
}
