#define _GNU_SOURCE
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
#include <pwd.h>
#include <grp.h>

char ** parse_args(char * line ) { 
    char * buff = line;
    char ** args;
    int arg = 0;
    while(buff != NULL) { 
        args[arg++] = strsep(&buff, " ");
    }
    args[arg] = NULL;
    printf("%p\n", args);
    return args; 
}

int main() {
    char line[8] = "ls -a -l";
    char ** args = parse_args(line);
    printf("%p\n", args);
    execvp(args[0], args);
    return 0;
}