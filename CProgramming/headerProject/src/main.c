#include <stdio.h>
#include "math_utils.h"

static void foo(void){
    static int x = 10;
    int y = 100;
    printf("Inside foo- x: %d, y: %d\n", x, y);
    x++;
    y++;
}

int main(void){

    printf("PI: %d\n", PI);
    int a = 5, b= 7;
    printf("Add %d & %d: %d\n", a, b, add(a, b));
    printf("Sub %d & %d: %d\n", a, b, subtract(a, b));

    Point pt = {1.1, 2.2};
    printf("Point pt(%.2f, %.2f)\n", pt.x, pt.y);
    
    for(int i = 0; i<5; i++) foo();

}
