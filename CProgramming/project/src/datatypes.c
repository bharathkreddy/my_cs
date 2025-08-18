#include <stdio.h>
#include <stdlib.h>

int main() {

    float weather[5][12] = {
        {1.1, 1.2, 3, 4, 5.5, 6, 7, 8, 9, 10, 11, 12.5},
        {2, 1, 3, 4, 5, 6, 7, 8, 9, 10 , 11, 12},
        {12,34,32,4,5,6,8,43,5,6,7,8},
        {12,34,32,4,5,6,8,43,5,6,7,8},
        {12,34,32,4,5,6,8,43,5,6,7,20},
    };

    for(int i=0; i<5; ++i){
        float sum = 0.0;
        for(int j=0; j<12; ++j){
            sum += weather[i][j];
        }
        printf("Avg rainfall for year %d: %f\n", i+2015, sum);
    }
    return 0;
}

