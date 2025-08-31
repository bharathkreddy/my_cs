#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum Department{
    xray,
    consultation,
    test,
};

struct Patient{
    char *name;
    int age;
    char gender;
};

struct Node{
    struct Patient patient;
    struct Node *nextNode;
};

struct Queue{
    struct Node *head;
    struct Node *tail;
    int count;
};

void addPatient(struct Queue *q){
    // allocate memory and initialize
    struct Node *node = malloc(sizeof(struct Node));
    if(!node){
        printf("Memory Allocation failed.\n");
        return;
    }

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
    scanf("%c", &node->patient.gender);
    while(getchar() != '\n');

    node->nextNode = NULL;
    q->tail = node;
    if(q->head == NULL) q->head = node;
    q->count++;
}


void displayPatients(struct Queue *q){
    
}

int main(void){
    
    //initialize the queue.
    struct Queue *xrayQ = malloc(sizeof(struct Queue));
    xrayQ->head = NULL;
    xrayQ->tail = NULL;
    xrayQ->count = 0;
    struct Queue *consultQ = malloc(sizeof(struct Queue));
    consultQ->head = NULL;
    consultQ->tail = NULL;
    consultQ->count = 0;
    struct Queue *testQ = malloc(sizeof(struct Queue));
    testQ->head = NULL;
    testQ->tail = NULL;
    testQ->count = 0;

    // variable declaration
    int userChoice = -1;
    int userDept = -1;
    
    while(1){

        // User Menu
        printf("\n=====HOSPITAL MENU=====\n");
        printf("0. Exit the program.\n");
        printf("1. Add a patient.\n");
        printf("2. Display all patients.\n");
        
        scanf("%d", &userChoice);
        while(getchar() != '\n');
        if(userChoice == 0 ) break;
        switch(userChoice){
            case 1:
                printf("Which department?\n");
                printf("1. Xray\n");
                printf("2. Consultation\n");
                printf("3. Tests\n");
                scanf("%d", &userDept);
                while(getchar() != '\n')
                if(userDept == 1) {addPatient(xrayQ);}
                else if (userDept == 2) {addPatient(consultQ);}
                else if (userDept == 3) {addPatient(testQ);}
                else {printf("Incorrect choice, taking back to main menu.\n");}
                break;
            case 2:
                //displayPatients();
                break;
            default:
                printf("Bad choice. Please choose again.\n");
                break;
        }
    }
    return 0;
}
