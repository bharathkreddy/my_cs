#include "math_utils.h"

static int staticAdd(int a){
    return a+1+PI;
}

int add (int a, int b){
    return staticAdd(a) + b;
}

int subtract(int a, int b){
    return b - a;
}


