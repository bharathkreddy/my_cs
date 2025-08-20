#include <stdio.h>
#include <string.h> 


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
    printf("%d", strnlen(arr,50));
}

