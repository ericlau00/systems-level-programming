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
#include <sys/wait.h>

int num_args(char * line) {
    int count = 0;
    int i;
    for(i = 0 ; line[i] != '\0'; i++) {
        if(line[i] == ' ') count++;
    }
    return count+1;
}

char ** parse_args(char * line) {
    char * buff = line;
    char ** args = malloc(sizeof(char) * num_args(line));
    int arg = 0;
    while(buff != NULL)
        args[arg++] = strsep(&buff, " ");
    args[arg] = NULL;
    return args;
}

int main() {
    int SIZE = 256;
    char input[SIZE];

    while(strcmp(input, "exit")) {
        fgets(input, SIZE, stdin);
        int i;
        for(i = 0; i < strlen(input); i++) {
            if(input[i] == '\n')
                input[i] = '\0';
        }
        char ** args = parse_args(input);
        if(fork() == 0)
            execvp(args[0], args);
        free(args);
    }
    return 0;
}
