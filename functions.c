#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h> //open 
#include <unistd.h> //read, write, close 
#include <errno.h> //errno
#include <sys/stat.h> //umask, stat
#include <time.h> //ctime
#include <dirent.h>
#include <sys/types.h>

void rand_characters(char * characters[]) { 
  FILE * charfile;
  charfile = fopen("characters", "r");
  char temp[255];
  int i;
  for (i = 0; i < 16; i++) {
    fgets(temp, 255, charfile);
    char *pos;
    if ((pos=strchr(temp, '\n')) != NULL)
        *pos = '\0';
    char* str = malloc(strlen(temp)+1);
    strcpy(str, temp);
    characters[i] = str;
  }
  fclose(charfile);
}
int main() {
  char * characters[16];
  rand_characters(characters);
  int i;
  for (i = 0; i < 16; i++) {
    printf("%d:\t%s\n", i, characters[i]);
  }
  return 0;
}
