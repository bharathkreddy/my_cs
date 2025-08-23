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


int main(){
    struct Journal journal;
    initializeJournal(&journal);
    
    return 0;
}
