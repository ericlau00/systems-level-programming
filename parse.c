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
#include "parse.h"

int stripper(char * line, char strip) {
    shift(line, strip);
    int i;
    for(i = 0; i < strlen(line); i++) {
        if(line[i] == strip) {
            line[i] = '\0';
        }
    }
    return 0;
}

int shift(char * line, char strip) {
    while (line[0] == strip) {
        int shift;
        for(shift = 1; shift < strlen(line); shift++) {
            line[shift - 1] = line[shift];
        }
        line[shift - 1] = '\0';
    }
    return 0;
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

int get_fd(char * file, char std) {
    int put = (std == '>')
        ? open(file, O_CREAT | O_EXCL | O_WRONLY, 0777)
        : open(file, O_RDONLY);
    if (std == '>' && put < 0 && errno == 17) {
        put = open(file, O_TRUNC | O_WRONLY);
    }
    return put;
}