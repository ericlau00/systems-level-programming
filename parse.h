#define _GNU_SOURCE
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>    //open
#include <unistd.h>   //read, write, close
#include <errno.h>    //errno
#include <sys/stat.h> //umask, stat
#include <time.h>     //ctime
#include <dirent.h>
#include <sys/types.h>
#include <pwd.h>
#include <grp.h>
#include <sys/wait.h>

int stripper(char * line, char strip);

char ** parser(char * line, char delim);

int count(char * line, char delim);

int get_fd(char * file, char std);