#include <stdio.h>

union student{
    char letterGrade;
    int roundedGrade;
    float exactGrade;
};

int main(void){
    union student s1;
    union student s2;

    s1.letterGrade = 'A';

    printf("s1: %zu\n", sizeof(s1));
    printf("s1:%c\n", s1.letterGrade);
    
    s1.roundedGrade = 3;
    printf("S1: %d, size: %zu\n", s1.roundedGrade, sizeof(s1));
    printf("s1:%c\n", s1.letterGrade);

    s2.exactGrade = 3.14;
    printf("s2: %f, size:%zu\n", s2.exactGrade, sizeof(s2));

    return 0;
}
