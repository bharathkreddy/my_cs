#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Site{
    char *url;
};

struct Node{
    struct Site site;
    struct Node *prevNode;
};

struct Stack{
    int nodeCount;
    struct Node *current;
};

struct BackStack{
    int nodeCount;
    struct Node *current;
};

void freeStack(struct Stack *stack, struct BackStack *backstack){
    struct Node *temp = stack->current;
    while(temp != NULL){
        free(temp->site.url);
        struct Node *prev = temp->prevNode;
        free(temp);
        temp = prev;
    }
    temp = backstack->current;
    while(temp != NULL){
        free(temp->site.url);
        struct Node *prev = temp->prevNode;
        free(temp);
        temp = prev;
    }
    free(backstack);
    free(stack);
}

void addsite(struct Stack *stack, struct BackStack *backstack, char *buff){
    
    struct Node *node = malloc(sizeof(struct Node));
    if(!node){
        printf("Erorr allocating memory.\n");
        freeStack(stack, backstack);
        exit(1);
    }

    node->site.url = malloc(strlen(buff)+1);
    if(!node->site.url){
        printf("error allocating memory.\n");
        freeStack(stack, backstack);
        exit(1);
    }

    strcpy(node->site.url, buff);
    node->prevNode = stack->current;
    stack->current = node;
    stack->nodeCount++;
}

void displayStack(struct Stack *stack, struct BackStack *backstack){
    printf("\n=====HISTORY=====\n");
    struct Node *temp = stack->current;
    int i = stack->nodeCount;
    while(temp != NULL){
        printf("%d: %s\n",i, temp->site.url);
        temp = temp->prevNode;
        --i;
    }
    printf("\n=====backstack====\n");
    temp = backstack->current;
    i = backstack->nodeCount;
    while(temp != NULL){
        printf("%d: %s\n", i, temp->site.url);
        temp = temp->prevNode;
        --i;
    }
    printf("\n\n");
}

void goBack(struct Stack *stack, struct BackStack *backstack){
    if (stack->current == NULL || stack->current->prevNode == NULL){
        printf("Cannot go back further.\n");
        return;
    }
    struct Node *temp = stack->current;
    stack->current = temp->prevNode;
    stack->nodeCount--;
    temp->prevNode = backstack->current;
    backstack->current = temp;
    backstack->nodeCount++;
    printf("Current URL: %s\n", stack->current->site.url);
}

void goForward(struct Stack *stack, struct BackStack *backstack){
    if (backstack->current == NULL){
        printf("Cannot go forward further.\n");
        return;
    }
    struct Node *temp = backstack->current;
    backstack->current = temp->prevNode;
    backstack->nodeCount--;
    temp->prevNode = stack->current;
    stack->current = temp;
    stack->nodeCount++;
    printf("Current URL: %s\n", stack->current->site.url);
}

int main(void){
    char buff[100] = {0};   
    int userChoice = -1;
    
    //initialize the history stack
    struct Stack *stack = malloc(sizeof(struct Stack));
    stack->current = NULL;
    stack->nodeCount = 0;

    struct BackStack *backstack = malloc(sizeof(struct BackStack));
    backstack->nodeCount = 0;
    backstack->current = NULL;

    while(1){

        printf("====Browser Menu===\n");
        printf("0. Exit program.\n");
        printf("1. visit a site.\n");
        printf("2. Go back n steps.\n");
        printf("3. Go forward n steps.\n");
        printf("4. Display history.\n");

        scanf("%d", &userChoice);
        while(getchar() != '\n'); // empty left over new line from input.
        if(userChoice ==0) break;
        
        switch(userChoice) {
            case 1:
                printf("Enter a url: ");
                // Read input from the user
                fgets(buff, sizeof(buff), stdin);
                buff[strcspn(buff, "\n")] = '\0'; // Removes '\n'
                addsite(stack, backstack, buff);
                break;
            case 2:
                goBack(stack, backstack);
                break;
            case 3:
                goForward(stack, backstack);
                break;
            case 4:
                displayStack(stack, backstack);
                break;
           default:
                printf("Incorrect choice. Please select again.\n");
                break;
        }

    }
    freeStack(stack, backstack);
    return 0;
}
