#include <stdio.h>

struct Node
{
    int data;
    struct Node *next;
};

struct Node_dl
{
    struct Node_dl *prev;
    int data;
    struct Node_dl *next;
};

struct Node* createll(int *arr, int len);
void displayll(struct Node *head);
void recursive_displayll(struct Node *head);
void recursive_reverse_displayll(struct Node *head);
int countNodes(struct Node *head);
int sumNodes(struct Node *head);
void insertll(struct Node **head, int key, int index);
void deleteNode(struct Node **head, int key);
void freell(struct Node *head);
void reversell(struct Node **head);
void concatenatell(struct Node **head1, struct Node *head2);
void mergell(struct Node **head1, struct Node *head2);
struct Node_dl * create_dl(int arr[], int len);
void display_dl(struct Node_dl *head_dl);
void free_dl(struct Node_dl **head_dl);
void insert_dl(struct Node_dl **head, int newData, int index);
void delete_dl(int data);
