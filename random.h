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

int get_random(char random_characters[16][20]);

int _random(int div);

void get_characters(char ** characters);

int get_chosen(char * chosen, char characters[16][20]);