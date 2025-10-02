#include <stdio.h>
#include <stdlib.h>
#include "ll.h"

struct Node* createll(int *arr, int len)
{
    if(len == 0) { return NULL; }
    struct Node *head = (struct Node*) malloc(sizeof(struct Node));
    head->data = arr[0];
    head->next = NULL;

    struct Node *current = head;

    for(int i = 1; i < len; ++i){
        struct Node *newNode = (struct Node*)malloc(sizeof(struct Node));
        newNode->data = arr[i];
        newNode->next = NULL;
        
        current->next = newNode;
        current = newNode;
    }
    return head;
}

void displayll(struct Node *head)
{
    struct Node *temp = head;
    while(temp != NULL){
        printf("data:%d | &data: %p |  next-> %p\n", temp->data, (void *) &temp->data, (void *)temp->next);
        temp = temp->next;
    }
    printf("NULL\n");
}

void freell(struct Node *head)
{
    struct Node *temp;
    while(head != NULL){
        temp = head;
        head = head->next;
        free(temp);
    }
}

void recursive_displayll(struct Node *head)
{
    if(head != NULL){
        printf("%d ",head->data);
        recursive_displayll(head->next);
    } else {
        printf("\n");
    }
}

void recursive_reverse_displayll(struct Node *head)
{
    if(head != NULL){
        recursive_reverse_displayll(head->next);
        printf("%d ",head->data);
    } else {
        printf("\n");
    }
}

int countNodes(struct Node *head)
{
    int count = 0;
    struct Node *temp = head;
    while(temp != NULL){
        temp = temp->next;
        count++;
    }
    return count;
}

int sumNodes(struct Node *head){
    struct Node *temp = head;
    int sum = 0;
    while(temp != NULL){
        sum += temp->data;
        temp = temp->next;
    }
    return sum;
}

void insertll(struct Node **head, int key, int index)
{
    struct Node *p = *head;
    struct Node *q = NULL;
    struct Node *newNode = (struct Node*)malloc(sizeof(struct Node));
    if(!newNode){
        printf("Memory allocation failed.\n");
        return;
    }
    newNode->data = key;
    if(index == 0){
        *head = newNode;
        newNode->next = p;
    } else {
        for(int i=0; i < index && p != NULL; ++i){
            q = p;
            p = p->next;            
        }
        q->next = newNode;
        newNode->next = p;
    }
}

void deleteNode(struct Node **head, int key)
{
    struct Node *p = *head;
    // case 1 delete head node
    if(p->data == key){
        *head = p->next;
        free(p);
        return;
    }

    // case 2 nonhead node deletion
    while(p->next != NULL && p->next->data != key ){
        p = p->next;
    }

    if(p->next == NULL){
        printf("Key:%d not found.\n", key);
        return;
    }

    struct Node *toDelete = p->next;
    p->next = toDelete->next;
    free(toDelete);
}

void reversell(struct Node **head)
{
    struct Node *p = *head;
    struct Node *q = NULL;
    struct Node *r = NULL;

    while(p != NULL) {
        r = q;
        q = p;
        p = p->next;
        q->next = r; 
    }
    *head = q;
}

void concatenatell(struct Node **head1, struct Node *head2)
{
    struct Node *p = *head1;
    while(p->next != NULL){
        p = p->next;
    }
    p->next = head2;
}

void mergell(struct Node **head1, struct Node *head2)
{
   struct Node *first = NULL;
   struct Node *last = NULL;
    
   if((*head1)->data < head2->data)
   {
       first = *head1;
       last = *head1;
       *head1 = (*head1)->next;
       last->next = NULL;
   }
   else
   {
        first = head2;
        last = head2;
        head2 = head2->next;
        last->next = NULL;
   }

   while(*head1 != NULL && head2 != NULL)
   {
       if((*head1)->data < head2->data)
       {
           last->next = *head1;
           last = *head1;
           *head1 = (*head1)->next;
           last->next = NULL;
       }
       else
       {
           last->next = head2;
           last = head2;
           head2 = head2->next;
           last->next = NULL;
       }
   }
   if(*head1 != NULL)
   {
       last->next = *head1;
   }
   else
   {
       last->next = head2;
   }

   *head1 = first;
}

struct Node_dl * create_dl(int arr[], int len)
{
    struct Node_dl *head_dl = (struct Node_dl *)malloc(sizeof(struct Node_dl));
    head_dl->prev = NULL;
    head_dl->data = arr[0];
    head_dl->next = NULL;
    
    struct Node_dl *l = head_dl;

    for(int i = 1; i < len; ++i){
        struct Node_dl *temp = (struct Node_dl*)malloc(sizeof(struct Node_dl));
        temp->data = arr[i];
        temp->next = NULL;
        
        l->next = temp;
        temp->prev = l;
        
        l = temp;
    }
    return head_dl;
}

void display_dl(struct Node_dl *head_dl)
{
    struct Node_dl *temp = head_dl;
    while(temp != NULL)
    {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n\n");
}

void free_dl(struct Node_dl **head_dl)
{
    struct Node_dl *curr = *head_dl;
    while (curr != NULL){
        struct Node_dl *next = curr->next;
        free(curr);
        curr = next;
    }
    *head_dl = NULL;
}

void insert_dl(struct Node_dl **head, int newData, int index)
{
    struct Node_dl *temp = (struct Node_dl *) malloc(sizeof(struct Node_dl));
    temp->data = newData;
    temp->prev = NULL;
    temp->next = NULL;
    
    struct Node_dl *p = head;
    if(index == 0)
    {
        temp->next = head->next;
        head = temp;
        temp->next->prev = temp;
    }
    else
    {
        
    }
}
