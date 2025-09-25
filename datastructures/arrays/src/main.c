#include <stdio.h>
#include <stdlib.h>
#include "arrayADT.h"

int main(void)
{
    /* initialize */
    struct Array a;
    int n; 
    int choice;
    int el;
    int res;

    while(1){
        printf("\n====ARRAY ADT====\n");
        printf("Choose from menu below\n");
        printf("0. Initialize the Array.\n");
        printf("1. Add a number to the array.\n");
        printf("2. Display the array\n");
        printf("3. Insert at index\n");
        printf("4. Delete at index.\n");
        printf("5. Search for a number.\n");
        printf("6. find sum.\n");
        printf("7. Reverse the array.\n");
        printf("8. Shift the array.\n");
        printf("9. Exit the program.\n");
        printf("Your Choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 0:
                printf("Enter the length of the array: ");
                scanf("%d", &n);
                initializeArray(&a, n);
                break;   
            case 1:
                printf("Enter a number to add to the array: ");
                scanf("%d", &n);
                res = add(&a, n);
                if(res != 0) {printf("Error adding number.\n");}
                if(res == 0) {printf("Ement %d added at index %d\n", n, a.curr_length -1);}
                break;
            case 2:
                displayArray(&a);
                break;
            case 3:
                printf("Enter the element: ");
                scanf("%d", &el);
                printf("Enter the index at which this element is to be inserted: ");
                scanf("%d", &n);
                insertElement(&a, el, n);
                break;
            case 4:
                printf("Enter index at which the element would be deleted: ");
                scanf("%d", &n);
                deleteIndex(&a, n);
                break;
            case 5:
                printf("Enter the number you want the index for: ");
                scanf("%d", &n);
                res = binarySearch(&a, n);
                if(res == -1){
                    printf("No such element.\n");
                } else {
                    printf("%d, is found at index - %d\n", n, res);
                }
                break;
            case 6:
                res = sum(&a);
                printf("Sum: %d\n", res);
                break;
            case 7:
                reverse(&a);
                break;
            case 8:
                printf("Enter negative values for leftshift and positive for rightshift.\n");
                printf("Shift by: ");
                scanf("%d", &n);
                shift(&a, n);
                break;
            case 9:
                cleanProgram(&a);
                exit(EXIT_SUCCESS);
                break;
        }
    }
    return 0;
}
