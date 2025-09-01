#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum Urgency{
    low,
    medium,
    high,
};

struct Patient{
    char *name;
    int age;
    char gender;
    enum Urgency urgency;
};

struct Node{
    struct Patient patient;
    struct Node *nextNode;
};

struct Queue{
    struct Node *head;
    struct Node *tail;
    int count;
    char name;
};

void addPatient(struct Queue *q){

    // allocate memory and initialize
    struct Node *node = malloc(sizeof(struct Node));
    if(!node){
        printf("Memory Allocation failed.\n");
        return;
    }

    // creation of node
    char pname[100];
    printf("Patient Name: ");
    fgets(pname, sizeof(pname), stdin);
    pname[strcspn(pname, "\n")] = '\0';
    
    node->patient.name = malloc(strlen(pname)+1);
    if(!node->patient.name){
        printf("Memory allocation failed.\n");
        free(node);
        return;
    }
    strcpy(node->patient.name, pname);
    
    printf("Patient Age: ");
    scanf("%d", &node->patient.age);
    while(getchar() != '\n'); //clear input buffer

    printf("Patient Gender: ");
    scanf(" %c", &node->patient.gender);  // space before %c skips whitespaces/newline.
    while(getchar() != '\n');

    printf("Patient Urgency (0:low, 1:medium, 2:high: )");
    scanf("%d", &node->patient.urgency);
    while(getchar() != '\n');

    // insertion of node
    if(q->name == 'X'){
        //priority insertion
        if(q->head == NULL || node->patient.urgency < q->head->patient.urgency) {
            // Insert at head
            node->nextNode = q->head;
            q->head = node;
            if(q->tail == NULL) q->tail = node;
        } else {
            struct Node *curr = q->head;
            while(curr->nextNode != NULL && curr->nextNode->patient.urgency <= node->patient.urgency) {
                curr = curr->nextNode;
            }
            node->nextNode = curr->nextNode;
            curr->nextNode = node;
            if(node->nextNode == NULL) q->tail = node;
        }
    } else {
        // standard queue insert at tail
        node->nextNode = NULL;
        if(q->tail) q->tail->nextNode = node;
        if(q->head == NULL) q->head = node;
        q->tail = node;
    };
    q->count++;
}


void displayPatients(struct Queue *q){
    struct Node *temp = q->head;
    if(temp == NULL){
        printf("Empty queue!");
        return;
    }
    int cnt = q->count;
    printf("\n===QUEUE %c===\n",q->name);
    while(temp){
        printf("%d. %s, %d, %c, Urgency: %d\n", cnt, temp->patient.name, temp->patient.age, temp->patient.gender, temp->patient.urgency);
        temp = temp->nextNode;
        --cnt;
    };
}

void freeMemory(struct Queue *q){
    struct Node *temp = q->head;
    while(temp){
        free(temp->patient.name);
        struct Node *temp2 = temp->nextNode;
        free(temp);
        temp = temp2;
    };
}

int main(void){
    
    //initialize the queue.
    struct Queue *xrayQ = malloc(sizeof(struct Queue));
    xrayQ->head = NULL;
    xrayQ->tail = NULL;
    xrayQ->count = 0;
    xrayQ->name = 'X';
    struct Queue *consultQ = malloc(sizeof(struct Queue));
    consultQ->head = NULL;
    consultQ->tail = NULL;
    consultQ->count = 0;
    consultQ->name = 'C';
    struct Queue *testQ = malloc(sizeof(struct Queue));
    testQ->head = NULL;
    testQ->tail = NULL;
    testQ->count = 0;
    testQ->name = 'T';

    // variable declaration
    int userChoice = -1;
    int userDept = -1;
    
    while(1){

        // User Menu
        printf("\n=====HOSPITAL MENU=====\n");
        printf("0. Exit the program.\n");
        printf("1. Add a patient.\n");
        printf("2. Display all patients.\n");
        printf("Choice: "); 
        scanf("%d", &userChoice);
        while(getchar() != '\n');
        if(userChoice == 0 ) break;
        switch(userChoice){
            case 1:
                printf("Which department?\n");
                printf("1. Xray\n");
                printf("2. Consultation\n");
                printf("3. Tests\n");
                printf("Choice: ");
                scanf("%d", &userDept);
                while(getchar() != '\n');
                if(userDept == 1) {addPatient(xrayQ);}
                else if (userDept == 2) {addPatient(consultQ);}
                else if (userDept == 3) {addPatient(testQ);}
                else {printf("Incorrect choice, taking back to main menu.\n");}
                break;
            case 2:
                printf("Which department?\n");
                printf("1. Xray\n");
                printf("2. Consultation\n");
                printf("3. Tests\n");
                printf("Choice: ");
                scanf("%d", &userDept);
                while(getchar() != '\n');
                if(userDept == 1) {displayPatients(xrayQ);}
                else if (userDept == 2) {displayPatients(consultQ);}
                else if (userDept == 3) {displayPatients(testQ);}
                else {printf("Incorrect choice, taking back to main menu.\n");}
                break;
            default:
                printf("Bad choice. Please choose again.\n");
                break;
        }
    };

    // cleaning up memory
    freeMemory(xrayQ);
    freeMemory(consultQ);
    freeMemory(testQ);

    return 0;
}
