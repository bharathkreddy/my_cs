#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Song{
    char *songName;
    int duration;
    char *artist;
};

struct Node{
    struct Song song;
    struct Node *nextNode;
};

struct Playlist{
    struct Node *head;
    struct Node *current;
    int nodeCount;
};

struct Node* createNode(void){
    
    struct Node *node = malloc(sizeof(struct Node));
    if(node == NULL){
        perror("Memory allocation error.\n");
        exit(1);
    }
    char sname[100];
    char sartist[100];

    printf("Enter Song name: ");
    fgets(sname, sizeof(sname), stdin);
    sname[strcspn(sname, "\n")] = '\0'; //cleanup new line after input

    printf("Enter artist name: ");
    fgets(sartist, sizeof(sartist), stdin);
    sartist[strcspn(sartist, "\n")] = '\0';
    
    printf("Enter Song duration: ");
    scanf("%d", &node->song.duration);
    while(getchar() != '\n');  // Clear input buffer
    
    node->song.songName = malloc(strlen(sname)+1);
    if(node->song.songName == NULL){
        perror("Memory allocation error.\n");
        exit(1);
    }
    strcpy(node->song.songName, sname);
    
    node->song.artist = malloc(strlen(sartist)+1);
    if(node->song.artist == NULL){
        perror("Memory allocation error.\n");
        exit(1);
    }
    strcpy(node->song.artist, sartist);

    node->nextNode = NULL;

    return node;  // return pointer to created node
}

void addSong(struct Playlist *pl, int songPosition){
    
    struct Node *node1 = createNode();

    // empty list -> new head and current
    if(pl->head == NULL) {
        printf("Empty playlist, adding song to first position.\n");
        pl->head = node1;
        pl->current = node1;
    } else if (songPosition == 0){   // insert at postion 0, head becomes node1
        printf("Adding to start of playlist.\n");
        node1->nextNode = pl->head;  // New node points to old head
        pl->head = node1;  // New node becomes the head.
        pl->current = node1;  
    } else if (songPosition == -1 || songPosition > pl->nodeCount) {
        struct Node *temp = pl->head;
        while(temp->nextNode != NULL){
            temp = temp->nextNode;
        }
        temp->nextNode = node1; 
        pl->current = node1;        
    } else {
        struct Node *temp = pl->head;
        for(int i=0; i<songPosition-1; ++i){
            temp = temp->nextNode;
        }
        node1->nextNode = temp->nextNode;
        temp->nextNode = node1;
        pl->current = node1;
    }
    
    pl->nodeCount++; //increase the nodecount.
}

void displayPlaylist(struct Playlist *pl){
    if(pl->head == NULL){
        printf("Nothing to display.\n");
        return;
    }
    int songNumber = 1;
    struct Node *temp = pl->head;
    while(temp != NULL){
        printf("Song %d - (%d mins) - %s, by %s.\n", songNumber, temp->song.duration, temp->song.songName, temp->song.artist);
   songNumber++;
   temp = temp->nextNode;
    }
}

void cleanup(struct Playlist *pl){
    if(pl->head == NULL){
        printf("nothing to cleanup.\n");
        return;
    } else {
        struct Node *temp = pl->head;
        while(temp != NULL){
            free(temp->song.songName);
            free(temp->song.artist);
            pl->head = temp->nextNode;
            free(temp);
            temp = pl->head;
        }
        pl->head = NULL; //redundant as next of last is null, but good defensive programming.
        pl->current = NULL;
        printf("cleanup complete\n");
    }
}

int main(void){
    //initialize playlist
    struct Playlist pl;
    pl.current = NULL;
    pl.head = NULL;
    pl.nodeCount = 0;
    
    int userChoice = -1;
    int songPosition = -1;
    
    while(1){
        printf("====PLAYLIST====\n");
        printf("Menu: \n");
        printf("0. Exit the program.\n");
        printf("1. Add a song.\n");
        printf("2. Display playlist.\n");


        scanf("%d", &userChoice);
        while(getchar() != '\n'); // clear buffer before creating node.
        if(userChoice == 0){
            printf("Exiting the program.\n");
            cleanup(&pl);
            exit(0);
        }

        switch(userChoice){
            case 1:
                printf("At what position do you want to add the song?");
                scanf("%d", &songPosition);
                while(getchar() != '\n'); // clear buffer before creating node.
                addSong(&pl, songPosition);
                break;
            case 2:
                displayPlaylist(&pl);
                break;
            case 3:
               // displayPlaylist(&pl);
                break;
            default:
                printf("Incorrect Choice. Choose again.\n");
        }
    }

    return 0;
}
