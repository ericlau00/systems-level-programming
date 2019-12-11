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
#include "headers.h"

int exec_line(char * line) {
    int num_commands = count(line, ';');
    char ** commands = parser(line, ';');

    int i;
    for(i = 0; i < num_commands; i++) {
        if(commands[i] != NULL) {
            if(strcmp(commands[i], "exit") == 0) {
                free(commands);
                exit(0);
            }

            if(count(commands[i], '>') - 1 > 0) {
                redir(commands[i], '>');
            }

            else if (count(commands[i], '<') - 1 > 0) {
                redir(commands[i], '<');
            }

            else {
                exec_command(commands[i]);
            }
        }
    }

    free(commands);
    return 0;
}

int stripper(char * line, char strip) {
    while (line[0] == strip) {
        int shift;
        for(shift = 1; shift < strlen(line); shift++) {
            line[shift - 1] = line[shift];
        }
        line[shift - 1] = '\0';
    }
    int i;
    for(i = 0; i < strlen(line); i++) {
        if(line[i] == strip) {
            line[i] = '\0';
        }
    }
    return 0;
}

int count(char * line, char delim) {
    int count = 1;
    int i;
    for(i = 0 ; line[i] != '\0'; i++) {
        if(line[i] == delim) {
            count++;
        }
    }
    return count;
}

char ** parser(char * line, char delim) {
    char * buff = line;
    char separator[1] = {delim};
    char ** args = malloc(sizeof(char *) * (count(line, delim) + 1));
    int arg = 0;
    while(buff != NULL) {
        char * argument = strsep(&buff, separator);
        if(strcmp(argument, "") == 0) {
            continue;
        }
        args[arg++] = argument;
    }
    args[arg] = NULL;
    return args;
}

int exec_command(char * command) {
    char ** args = parser(command, ' ');

    if(args[0] == NULL) { }

    else if(strcmp(args[0], "cd") == 0) {
        chdir(args[1]);
    }

    else if(fork() == 0) {
        int i;
        if(execvp(args[0], args) == -1) {
            if(count(command, ' ') > 1) {
                printf("%s: command not found\n", args[0]);
            }
        }
        free(args);
        exit(0);
    }
    else {
        wait(0);
    }
    free(args);
    return 0;
}

int redir(char * command, char std) {
    char ** args = parser(command, std);
    stripper(args[1], ' ');
    int put = get_fd(args[1], std);

    int num = (std == '>') ? 1 : 0;
    int save = dup(num);
    close(num);
    dup(put);
    exec_command(args[0]);
    close(put);
    dup2(save, num);
    return 0;
}

int get_fd(char * file, char std) {
    int put = (std == '>')
        ? open(file, O_CREAT | O_EXCL | O_WRONLY, 0777)
        : open(file, O_RDONLY);
    if (std == '>' && put < 0 && errno == 17) {
        put = open(file, O_TRUNC | O_WRONLY);
    }
    return put;
}