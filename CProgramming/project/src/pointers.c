#include <stdio.h>
#include <string.h> 

void mySwap(int *a, int *b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

int *findMax(int *arr, int size){
    int *pMax = arr;
    for(int i=1; i<size; ++i){
        pMax = arr[i]>*pMax ? &arr[i] : pMax;
    }
    return pMax;
}

void printBytes(void *arr, size_t size){
    char *p = (char *)arr;
    for (size_t i=0; i<size; ++i)
        printf("%02X - ",p[i]);
    printf("\n");
}

int main(void){

    int number = 10;
    int *pNumber = &number;
    if(!pNumber){
        printf("pointer not allocated properly");
        return 1;
    }
    printf("Number's value: %d, addr: %p\n",number, &number);
    printf("Pointers's value: %p, addr: %p, points_at:%d\n",pNumber, &pNumber, *pNumber);

    printf("Changing value of *pNum to 100.\n");
    *pNumber = 100;

    printf("Number's value: %d, addr: %p\n",number, &number);
    printf("Pointers's value: %p, addr: %p, points_at:%d\n\n",pNumber, &pNumber, *pNumber);

   // illegal change of pointer being assigned an int and not address :  pNumber = 100;
    
    int arr[] = {1,2,3,4,5};
    int *pArr = arr;
    printf("Arrays's value: %p, addr: %p\n", arr, &arr);
    printf("Pointers's value: %p, addr: %p, points_at:%d\n",pArr, &pArr, *pArr);
    printf("iterating throught the array using pointer.\n");
    
    printf("size of array: %lu, size of 1st element: %lu, Len of arr: %lu\n", sizeof(arr),sizeof(arr[0]), sizeof(arr)/sizeof(arr[0]));

    for(int i=0; i<(sizeof(arr)/sizeof(arr[0])); ++i,pArr++){
        printf("Pointer points to: %d\n\n", *pArr);
    }
    
    // code to swap 2 variables using pointer
    int a = 10, b=20;
    printf("Before swap a: %d, b: %d\n", a, b);
    mySwap(&a, &b);
    printf("After swap a: %d, b: %d\n", a, b);
    
    int arr1[] = {1, 3, 5, 12, 6};
    int *pMax = findMax(arr1, 5);
    printf("Max of array, is: %d\n", *pMax);


    const int *p = &a; // now p cant change the value of a
    // *p = 20;  error: read-only variable is not assignable
    printf("value of a: %d, *p: %d\n", a, *p);
    // now p references something else
    p = &b;   // p can reference something else but change change it.
    printf("value of b: %d, *p: %d\n", b, *p);

    int * const p1 = &a;
    printf("value of a: %d, *p: %d\n", a, *p1);
    *p1 = 100;
    printf("value of a: %d, *p: %d\n", a, *p1);
    //p1 = &b; p can change value but cant reference anything else now.

    const int * const p2 = &a;
    printf("value of a: %d, *p: %d\n", a, *p2);
    // p2 = &b; not allowed
    // *p2 = 10; also not allowed.

    int x = 0x12345678;
    printBytes(&x, sizeof(x)); 

    int x1 = 5, y1 = 10;
    int *pointer1 = &x1, *pointer2 = &y1;
    int **pp = &pointer1;

    *pp = &y1;  // Now p1 points to y1
    *pointer1 = 42;  // Changes y1, not x1

    printf("x1 = %d, y1 = %d\n", x1, y1); // x1 = 5, y1 = 42
    printf("p1 points to value %d\n", *pointer1); // p1 -> y1
    printf("p2 points to value %d\n", *pointer2); // p2 -> y1
    printf("pp points to address %p\n", (void*)pp);
}
