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

int number (char * line, char sep) {
    int count = 0;
    int i;
    for(i = 0 ; line[i] != '\0'; i++) {
        if(line[i] == sep)
            count++;
    }
    return count+1;
}

char ** parser(char * line, char * delim) {
    char * buff = line;
    char sep = delim[0];
    char ** args = malloc(sizeof(char) * number(line, sep));
    int arg = 0;
    while(buff != NULL)
        args[arg++] = strsep(&buff, delim);
    args[arg] = NULL;
    return args;
}

int main() {
    int SIZE = 256;
    char input[SIZE];

    while(1) {
        fgets(input, SIZE, stdin);
        int i;
        for(i = 0; i < strlen(input); i++) {
            if(input[i] == '\n')
                input[i] = '\0';
        }
        int num_commands = number(input, ';');
        char ** commands = parser(input, ";");
        int command;
        for(command = 0; command < num_commands; command++) {
            char ** args = parser(commands[command], " ");
            if(strcmp(commands[command], "exit") == 0) exit(0);
            if(fork() == 0)
                if (execvp(args[0], args) == -1) exit(0);
            else wait(0);
            free(args);
        }
        free(commands);
    }
    return 0;
}
