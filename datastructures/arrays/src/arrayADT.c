#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arrayADT.h"

void findPairToSum(struct Array *a, int k)
{
    int i = 0;
    int j = a->curr_length - 1;

    while(i < j) {
        if(a->arr[i] + a->arr[j] == k){
            printf("Pair: %d + %d = %d\n", a->arr[i], a->arr[j], k);
            i++;
            j--;
        } else if (a->arr[i] + a->arr[j] > k) {
            j--;
        } else {
            i++;
        }
        printf("==END===\n");
    }
}

void initializeArray(struct Array *a, int length)
{
    a->curr_length = 0;
    a->full_length = length;
    a->arr = (int *) malloc(a->full_length * sizeof(int));
    printf("Array of length %d Initialized.\n", a->full_length);
}

int add(struct Array *a, int n)
{
    if(a->curr_length > a->full_length-1) { return -1;}
    a->arr[a->curr_length] = n;
    a->curr_length++;
    return 0;
}

void displayArray(struct Array *a)
{
    if(a->curr_length == 0){printf("\nno elements.\n"); return;}
    printf("\nDisplaying elements of the array.\n");
    for(int i = 0; i < a->curr_length; ++i){
        printf("%d-", a->arr[i]);
    }
    printf("\n");
    printf("Curr_len: %d, full_len: %d\n\n", a->curr_length, a->full_length);
}

void cleanProgram(struct Array *a)
{
    free(a->arr);
    printf("\nExiting the program.\n");
}

void insertElement(struct Array *a, int el, int index)
{
    if(index > 10 || index > a->curr_length){
        printf("Index out of bounds.\n");
        return;
    }
    if(a->curr_length > a->full_length){
        printf("Array full, cant insert more.\n");
        return;
    }
    for(int i = a->curr_length; i > index; --i){
        a->arr[i] = a->arr[i-1];
    }
    a->arr[index] = el;
    a->curr_length++;
    printf("\nElement %d inserted at index %d\n", el, index);
}

void deleteIndex(struct Array *a, int index)
{
    if(index > a->curr_length -1){
        printf("Array has only %d elements\n", a->curr_length);
        return;
    }
    for(int i = index; i < a->curr_length; ++i){
        a->arr[i] = a->arr[i+1];
    }
    a->curr_length--;
    printf("Element at index %d removed\n", index);
}

int binarySearch(struct Array *a, int element)
{
    int l = 0;
    int h = a->full_length - 1;
    while(l<=h){
        int m = l+ (h-l)/2;
        if (a->arr[m] == element){
            return m;
        } else if (a->arr[m] > element){
            h = m-1;
        } else {
            l = m+1;
        }
    }
    return -1;
}

int sum(struct Array *a)
{
    int res = 0;
    for(int i = 0; i < a->full_length; ++i){
        res = res + a->arr[i];
    }
    return res;
}

void swap(struct Array *a, int i, int j)
{
    int temp = a->arr[i];
    a->arr[i] = a->arr[j];
    a->arr[j] = temp;
}

void reverse(struct Array *a)
{
    int i = 0;
    int j = a->curr_length-1;
    while(j>i){
        swap(a, i, j);
        i++;
        j--;
    }
    printf("Array reversed.");
    displayArray(a);
}

void shift(struct Array *a, int shift)
{
    if(shift == 0) return;
    if(shift >= a->full_length || -shift >= a->full_length){
        memset(a->arr, 0, sizeof(int) * a->full_length);
        return;
    }

    if(shift > 0){ // rightshift
        memmove(a->arr + shift, a->arr, a->curr_length * sizeof(int));
        memset(a->arr, 0, shift * sizeof(int));
    } else {   //leftshift
        shift = -shift;
        memmove(a->arr, a->arr + shift, (a->curr_length - shift) * sizeof(int));
        memset(a->arr + (a->curr_length - shift), 0, shift * sizeof(int));
    }
}
