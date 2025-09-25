#include <stdio.h>
#include <stdlib.h>
#include "arrayADT.h"

#define ASSERT_EQ(expected, actual, msg) \
    do { \
        if ((expected) == (actual)) { \
            printf("[PASS] %s\n", msg); \
        } else {  \
            printf("[FAIL] %s (expected %d got %d)\n", msg, (expected), (actual));  \
        }  \
    } while(0);

#define ASSERT_ARR_EQ(expected, actual, length, msg) \
    do{  \
        int _ok = 1;  \
        for(int _i = 0; _i < length; ++_i) {  \
            if((expected)[_i] != (actual)[_i]){  \
                _ok = 0;  \
                break;  \
            }  \
        }  \
        if(_ok) {  \
            printf("[PASS] %s\n", msg);  \
        } else {  \
            printf("[FAIL] %s (array mismatch)\n", msg);  \
        }  \
    } while(0);

void test_add_and_display(void)
{
    struct Array a;
    initializeArray(&a, 9);
    add(&a, 3);
    add(&a, 13);
    add(&a, 5);
    add(&a, 9);
    add(&a, 7);
    add(&a, 1);
    add(&a, 11);
    add(&a, 15);
    add(&a, 21);

    int expected[] = {3, 13, 5, 9, 7, 1, 11, 15, 21};

    ASSERT_ARR_EQ(expected, a.arr, a.curr_length, "Add elements to array");

    cleanProgram(&a);
}

void test_insert(void)
{
    struct Array a;
    initializeArray(&a, 4);
    add(&a, 3);
    add(&a, 13);
    add(&a, 5);
    insertElement(&a, 9, 1);
    int expected[] = {3, 9, 13, 5};
    ASSERT_ARR_EQ(expected, a.arr, a.curr_length, "insert elements at index");
}

void test_delete(void)
{
    struct Array a;
    initializeArray(&a, 5);

    add(&a, 10);
    add(&a, 20);
    add(&a, 30);
    deleteIndex(&a, 1);

    int expected[] = {10, 30};
    ASSERT_ARR_EQ(expected, a.arr, a.curr_length, "Delete element at index");

    cleanProgram(&a);
}

void test_binarySearch(void)
{
    struct Array a;
    initializeArray(&a, 5);

    add(&a, 10);
    add(&a, 20);
    add(&a, 30);
    add(&a, 40);
    add(&a, 50);

    ASSERT_EQ(2, binarySearch(&a, 30), "Binary search finds element");
    ASSERT_EQ(-1, binarySearch(&a, 99), "Binary search returns -1 if not found");

    cleanProgram(&a);
}
void test_sum(void)
{
    struct Array a;
    initializeArray(&a, 3);

    add(&a, 5);
    add(&a, 10);
    add(&a, 15);

    ASSERT_EQ(30, sum(&a), "Sum of array elements");

    cleanProgram(&a);
}
void test_reverse(void)
{
    struct Array a;
    initializeArray(&a, 4);

    add(&a, 1);
    add(&a, 2);
    add(&a, 3);
    add(&a, 4);
    reverse(&a);

    int expected[] = {4, 3, 2, 1};
    ASSERT_ARR_EQ(expected, a.arr, a.curr_length, "Reverse array");

    cleanProgram(&a);
}

void findPair(void)
{
    struct Array a;
    initializeArray(&a, 10);

    add(&a, 1);
    add(&a, 3);
    add(&a, 4);
    add(&a, 5);
    add(&a, 6);
    add(&a, 8);
    add(&a, 9);
    add(&a, 10);
    add(&a, 12);
    add(&a, 14);

    findPairToSum(&a, 10);

    cleanProgram(&a);
}

int main(void)
{
    printf("====Running ArrayADT tests====\n");
    
    test_add_and_display();
    test_insert();
    test_delete();
    test_binarySearch();
    test_sum();
    test_reverse();
    findPair();

    printf("===Tests completed===\n");
    return 0;
}



