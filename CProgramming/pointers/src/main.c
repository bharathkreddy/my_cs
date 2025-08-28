#include <stdio.h>

void foo(int *pa, int *pb){

    printf("p: addr: %p, val: %p, pts: %d\n", (void *)&pa, (void*)pa, *pa);
    printf("p: addr: %p, val: %p, pts: %d\n", (void *)&pb, (void*)pb, *pb);

    *pa = 99;
    int b = 42;
    pb = &b;

    printf("p: addr: %p, val: %p, pts: %d\n", (void *)&pa, (void*)pa, *pa);
    printf("p: addr: %p, val: %p, pts: %d\n", (void *)&pb, (void*)pb, *pb);
}

int main(void){

    int a = 10;
    int b = 20;
    int c = 30;


    printf("Add of a: %p, Value of a: %d\n", (void*)&a, a);
    printf("Add of b: %p, Value of b: %d\n", (void*)&b, b);
    printf("Add of c: %p, Value of c: %d\n", (void*)&c, c);

    int *p = NULL;
    printf("p initiallized to NULL.\n");
    printf("Add of p: %p, Value of p: %p\n", (void*)&p, (void*)p);
  
    printf("p points to a\n");
    p = &a;
    printf("Add of p: %p, Value of p: %p, references: %d\n", (void*)&p, (void*)p, *p);

    printf("p points to b\n");
    p = &b;
    printf("Add of p: %p, Value of p: %p, references: %d\n", (void*)&p, (void*)p, *p);
    
    printf("p changed to 1\n");
    *p = 1;
    printf("Add of p: %p, Value of p: %p, references: %d\n", (void*)&p, (void*)p, *p);

    printf("Add of b: %p, Value of b: %d\n", (void*)&b, b);
  
    printf("changing value of b\n");
    b = 99;
    printf("Add of p: %p, Value of p: %p, references: %d\n", (void*)&p, (void*)p, *p);
    printf("Add of b: %p, Value of b: %d\n\n", (void*)&b, b);



    b = 10;
    a = 99;
    int *pa = &a;
    int *pb = &b;
    
    int **pp = NULL;
    pp = &pa;
    
    printf("a add: %p, val: %d\n", (void *)&a, a);
    printf("b add: %p, val: %d\n", (void *)&b, b);
    printf("pa: add: %p, val: %p, pts_to: %d\n", (void *)&pa, (void *)pa, *pa);
    printf("pb: add: %p, val: %p, pts_to: %d\n", (void *)&pb, (void *)pb, *pb);
    printf("pp: add: %p, val: %p, pts_to: %d\n\n", (void *)&pp, (void *)pp, **pp);

    **pp = 12;
    printf("a add: %p, val: %d\n", (void *)&a, a);
    printf("b add: %p, val: %d\n", (void *)&b, b);
    printf("pa: add: %p, val: %p, pts_to: %d\n", (void *)&pa, (void *)pa, *pa);
    printf("pb: add: %p, val: %p, pts_to: %d\n", (void *)&pb, (void *)pb, *pb);
    printf("pp: add: %p, val: %p, pts_to: %d\n\n", (void *)&pp, (void *)pp, **pp);

   
    a = 10;
    b = 20;
    pa = &a;
    pb = &b;

    printf("p: addr: %p, val: %p, pts: %d\n", (void *)&pa, (void*)pa, *pa);
    printf("p: addr: %p, val: %p, pts: %d\n", (void *)&pb, (void*)pb, *pb);
    foo(pa, pb);
    printf("p: addr: %p, val: %p, pts: %d\n", (void *)&pa, (void*)pa, *pa);
    printf("p: addr: %p, val: %p, pts: %d\n", (void *)&pb, (void*)pb, *pb);


    return 0;
}
