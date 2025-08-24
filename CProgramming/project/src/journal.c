#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct Entry{
    int entry_id;
    time_t entry_time;
    int content_length;
    char *content;
};

struct EntryIndex{
    int entry_id;
    long file_position; // Byte position of entry in file.
    time_t entry_time;
    int content_length;
};


struct Journal{
    char filename[256];
    FILE *file_pointer;
    int total_entries;
    int index_capacity;
    struct EntryIndex *index;
    int is_modified;
    int next_entry_id;
};


void displayChoices(int *pUserSelection){
    printf("\n==== Journal Menu ====\n");
    printf("1: Add new entry\n");
    printf("2: Read entry by ID\n");
    printf("3: Display all entries\n");
    printf("0: Quit\n");
    printf("Select option: ");
    scanf("%d", pUserSelection);
}

void initializeJournal(struct Journal *journal){
    printf("Name of journal data file: ");
    scanf("%s", journal->filename);
    journal->total_entries = 0;
    journal->index_capacity = 10;
    journal->index = malloc(journal->index_capacity * sizeof(struct EntryIndex));
    journal->next_entry_id = 1;
    journal->is_modified = 0;
    journal->file_pointer = fopen(journal->filename, "rb+");
    if(!journal->file_pointer){
        printf("Datafile doesnt exist, creating one now.\n");
        journal->file_pointer = fopen(journal->filename, "wb+");
        if(!journal->file_pointer){
            perror("Error creating the file.");
            free(journal->index);
            exit(1);
        }
        fwrite(&journal->total_entries, sizeof(int), 1, journal->file_pointer);
        fflush(journal->file_pointer);
    } else {
        // read from the existing file.
        fread(&journal->total_entries, sizeof(int), 1, journal->file_pointer);
        int pos = sizeof(int);
        for(int i=0; i<journal->total_entries; ++i){
          struct EntryIndex idx;
          fseek(journal->file_pointer, pos, SEEK_SET);
          fread(&idx.entry_id, sizeof(int), 1, journal->file_pointer);
          fread(&idx.entry_time, sizeof(time_t), 1, journal->file_pointer);
          fread(&idx.content_length, sizeof(int), 1, journal->file_pointer);
          idx.file_position = pos;
          journal->index[i] = idx;
          pos = sizeof(int) + sizeof(time_t) + sizeof(int) + idx.content_length;
        } 
    journal->next_entry_id = journal->total_entries > 0 ? journal->index[journal->total_entries-1].entry_id +1 : 1;
    }
}

void add_entry(struct Journal *journal){
  char buffer[1024], line[100];
  printf("Enter Text. Press '.' on a new line to exit.\n");
  while(1){
    fgets(line, sizeof(line), stdin);
    if(strcmp(line, ".\n")==0) break;
    strncat(buffer, line, strlen(line));
  }
  fseek(journal->file_pointer, 0, SEEK_END);
  int pos = ftell(journal->file_pointer);
  fwrite(&journal->next_entry_id, sizeof(int), 1, journal->file_pointer); 
  journal->next_entry_id++;
  fwrite(&pos, sizeof(int), 1, journal->file_pointer);
  time_t nowTime = time(NULL);
  fwrite(&nowTime, sizeof(time_t), 1 , journal->file_pointer);
  int bufferSize = strlen(buffer);
  fwrite(&bufferSize, sizeof(int), 1, journal->file_pointer);
  fwrite(buffer, sizeof(char), bufferSize, journal->file_pointer);
  fflush(journal->file_pointer);
  journal->total_entries++;
  
  // update index
  struct EntryIndex eid;
  eid.entry_id = journal->next_entry_id - 1;
  eid.file_position = pos;
  eid.entry_time = nowTime;
  eid.content_length = sizeof(buffer);
  journal->index[journal->total_entries] = idx; 

  // update header of file
  fseek(journal->file_pointer, 0, SEEK_SET);
  fwrite(&journal->total_entries, sizeof(int), 1, journal->file_pointer);
  fflush(journal->file_pointer);

  printf("Entry added as id: %d\n", eid.entry_id);

}


void read_entry(struct Journal *journal){
    int journalID;
    printf("Id of journal: ");
    scanf("%d", &journalID);
    int found  = -1;
    for(int i =0; i<journal->total_entries; ++i){
        if(journal->index[i].entry_id == journalID){
            found = i;
            break;
        }
    }
    if(found==-1){
        printf("no entry found.\n");
    } else {
        fseek(journal->file_pointer, journal->index[found].file_position + sizeof(int)+sizeof(time_t)+sizeof(int), SEEK_SET);
        char *printEntry = malloc(sizeof(journal->index[found].content_length));
        fread(printEntry, sizeof(journal->index[found].content_length), 1, journal->file_pointer);
        print("%s", printEntry);
    }
}

void read_all_entries(struct Journal *journal){
      
}

int main(){
    struct Journal journal;
    initializeJournal(&journal);
    
    int userSelection = -1;
    while(1){
        displayChoices(&userSelection);
        if(userSelection == 0) break;
        else if (userSelection == 1) add_entry(&journal);
        else if (userSelection == 2) read_entry(&journal);
        else if (userSelection == 3) read_all_entries(&journal);
        else printf("Wong choice made. Try again.\n");
    }

    // cleanup
    fclose(journal.file_pointer);
    free(journal.index);
    printf("Journal Closed.");

    return 0;
}
