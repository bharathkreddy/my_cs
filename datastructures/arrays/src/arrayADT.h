#ifndef ARR_ADT_H
#define ARR_ADT_H

struct Array
{
    int *arr;
    int curr_length;
    int full_length;
};

void initializeArray(struct Array *a, int length);

/* adding or appending to end of array *
 * Time complexity: O(1) */
int add(struct Array *a, int n);
/* O(n) */
void displayArray(struct Array *a);
void cleanProgram(struct Array *a);
/* O(n) */
void insertElement(struct Array *a, int el, int index);
/* O(n) */
void deleteIndex(struct Array *a, int index);
int binarySearch(struct Array *a, int element);
int sum(struct Array *a);
void swap(struct Array *a, int i, int j);
void reverse(struct Array *a);
void shift(struct Array *a, int shift);
void findPairToSum(struct Array *a, int k);

#endif
