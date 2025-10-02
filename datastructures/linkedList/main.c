#include <stdio.h>
#include "ll.h"

int main(void)
{
    int a[] = {1, 3, 5, 7, 11, 13, 17};
    struct Node *head = createll(a, sizeof(a)/sizeof(int));
    printf("++++Display linked list++++\n");
    displayll(head);

    printf("++++Recursive Display linked list++++\n");
    recursive_displayll(head);
    recursive_reverse_displayll(head);

    printf("Count of Nodes: %d\n", countNodes(head));
    printf("Sum of Nodes: %d\n", sumNodes(head));

    // have to pass pointer to pointer(head) to make changes to linked list, else the function would have a local head which gets modified and main never knows of the local head.
    insertll(&head, 21, 0);
    displayll(head);

    insertll(&head, 31, 4);
    displayll(head);

    insertll(&head, 99, 11);
    displayll(head);
    
    deleteNode(&head, 21);
    deleteNode(&head, 31);
    displayll(head);
    
    reversell(&head);
    displayll(head);

    // concatenate l1 and l2, returns expanded l1 and leaves l2 as is
    int b[] = {2, 4, 6 };
    struct Node *head2 = createll(b, sizeof(b)/sizeof(int));
    printf("++++Display linked list two++++\n");
    displayll(head2);
    concatenatell(&head, head2);
    displayll(head);
     
    // cleanup        
    freell(head);
    head = NULL;
    head2 = NULL;
    // freell uses a local head variable to free heap memory but head in main is a dangling pointer now i.e. points to released memory. so has to be set to NULL.

    int c[] = {1, 3, 5, 7, 11, 13, 17};
    struct Node *head_a = createll(c, sizeof(c)/sizeof(int));
    int d[] = {2, 4, 6};
    struct Node *head_b = createll(d, sizeof(d)/sizeof(int));
    mergell(&head_a, head_b);
    displayll(head_a);

    head_b = NULL;
    freell(head_a);
    head_a = NULL;

    //double ll
    int dl_a[] = {1, 3, 5, 7, 9};
    struct Node_dl *head_dl = create_dl(dl_a, sizeof(dl_a)/sizeof(int));
    printf("Displaying double linkedlist.\n");
    display_dl(head_dl);
    free_dl(&head_dl);
    return 0;
}
