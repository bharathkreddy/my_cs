/* tyler series e^x = 1 + x/1 + x^2/2! + x^3/3! + ... upto n terms. */           
//            ty(2,3)
//        n=3, p=4→8, f=2→6
//        r=5.0, returns 6.333
//             |
//             v
//          ty(2,2)
//        n=2, p=2→4, f=1→2
//        r=3.0, returns 5.0
//             |
//             v
//          ty(2,1)
//        n=1, p=1→2, f=1→1
//        r=1.0, returns 3.0
//             |
//             v
//          ty(2,0)
//        n=0, returns 1.0
//       
#include<stdio.h>

double ty(int x, int n)
{
    static double p = 1;
    static double f = 1;
    double r;
    if(n == 0){
        return 1;
    } else {
        r = ty(x, n-1);
        p = p*x;
        f = f*n;
        return r + p/f;
    }
}

int main(void)
{
    int n;
    int x;
    printf("Enter n: ");
    scanf("%d", &n);
    printf("Enter x: ");
    scanf("%d", &x);
     
    printf("result: %f\n", ty(x, n)); 
}
