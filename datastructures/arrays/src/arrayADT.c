#include <stdio.h>
#include <stdlib.h>

struct Array
{
    int *arr;
    int curr_length;
    int full_length;
};

void initializeArray(struct Array *a);

/* adding or appending to end of array *
 * Time complexity: O(1) */
void add(struct Array *a, int n);
/* O(n) */
void displayArray(struct Array *a);
void cleanProgram(struct Array *a);
/* O(n) */
void insertElement(struct Array *a, int el, int index);

int main(void)
{
    /* initialize */
    struct Array a;
    initializeArray(&a);
    
    int n; 
    int choice;
    int el;

    while(1){
        printf("\n====ARRAY ADT====\n");
        printf("Choose from menu below\n");
        printf("1. Add a number to the array.\n");
        printf("2. Display the array\n");
        printf("3. Insert at index\n");
        printf("9. Exit the program.\n");
        printf("Your Choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter a number to add to the array: ");
                scanf("%d", &n);
                add(&a, n);
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
            case 9:
                cleanProgram(&a);
                exit(EXIT_SUCCESS);
                break;
        }
    }
    return 0;
}

void initializeArray(struct Array *a)
{
    a->curr_length = 0;
    printf("Enter the full lenght of the array: ");
    scanf("%d", &a->full_length);
    a->arr = (int *) malloc(a->full_length * sizeof(int));
    printf("Array a Initialized.\n");
}

void add(struct Array *a, int n)
{
    a->arr[a->curr_length] = n;
    a->curr_length++;
    printf("\nElement %d added at index %d", n, a->curr_length -1);
}

void displayArray(struct Array *a)
{
    if(a->curr_length == 0){printf("no elements.\n"); return;}
    printf("\nDisplaying elements of the array.\n");
    for(int i = 0; i < a->curr_length; ++i){
        printf("%d-", a->arr[i]);
    }
    printf("\n");
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
    for(int i = a->curr_length; i > index; --i){
        a->arr[i] = a->arr[i-1];
    }
    a->arr[index] = el;
    a->curr_length++;
    printf("\nElement %d inserted at index %d\n", el, index);
}
