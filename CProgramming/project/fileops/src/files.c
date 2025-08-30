#include <stdio.h>

int main() {

  FILE *fp = fopen("files.txt", "r");
  if(!fp){
      printf("file couldnt be opened.\n");
      return 1;
  }
   
  int charCnt = 0;
  char c = fgetc(fp);
  while(c!=EOF){
      printf("%c~", c);
      charCnt++;
      c = fgetc(fp);  //else infinite loop printing first char.
  }
  printf("Char Count: %d\n\n", charCnt);

  rewind(fp);
  int lineCnt=0;
  char line[100];
  while (fgets(line, sizeof(line), fp)) {
    printf("%s", line);
    lineCnt++;
  }
  printf("Line Count: %d\n\n", lineCnt);

  // does not stop at 10 chars but multiple calls are made in batches of 10
  // bytes. useful in network sockets, embedded systems with small buffers.
  rewind(fp);
  while (fgets(line, 10, fp)) {
    printf("%s", line);
  }


 // char ip[128], names[1];
 // rewind(fp);
 // while(fgets(line, sizeof(line), fp)){
 //     if(line=="#"||line=="\n"|| line ==":"){
 //         printf("SKPIILING LINE.");
 //         continue;
 //     }
 //     fscanf(line, "%d%*", ip); 
 //     printf("IP: %d\n", ip);
 //}

  fclose(fp);
  fp = NULL;

  // fscanf processes the file as a stream, consuming only as much input as
  // needed by the format string for each call—typically, this means a few bytes
  // or tokens at a time, not even necessarily a whole line. Example: With "%*s
  // %*s %s", it will read 3 strings per call (whitespace-separated), one line
  // at a time for typical tabular data, but it’s not strictly line-oriented.
}
