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
#include "execution.h"
#include "parse.h"

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


            if(count(commands[i], '>') - 1 > 0 && count(commands[i], '<') - 1 > 0) {
                if((int)(strchr(commands[i],'<') - commands[i]) - (int)(strchr(commands[i],'>') - commands[i]))
                    exec_redir(commands[i], '>', 1);
                // else
                    // exec_out_and_in(commands[i]);
            }

            else if(count(commands[i], '>') - 1 == 1) {
                exec_redir(commands[i], '>', 0);
            }

            else if (count(commands[i], '<') - 1 == 1) {
                exec_redir(commands[i], '<', 0);
            }

            else {
                exec_command(commands[i]);
            }
        }
    }

    free(commands);
    return 0;
}

int exec_command(char * command) {
    char ** args = parser(command, ' ');

    if(args[0] == NULL) { }

    else if(strcmp(args[0], "cd") == 0) {
        chdir(args[1]);
    }

    else if(fork() == 0) {
        exec_fork(command, args);
    }
    else {
        wait(0);
    }
    free(args);
    return 0;
}

int exec_fork(char * command, char ** args) {
    int i;
    if(execvp(args[0], args) == -1) {
        if(count(command, ' ') > 1) {
            printf("%s: command not found\n", args[0]);
        }
    }
    free(args);
    exit(0);
}

int exec_redir(char * command, char std, int multi) {
    char ** args = parser(command, std);
    stripper(args[1], ' ');
    int put = get_fd(args[1], std);

    int num = (std == '>') ? STDOUT_FILENO : STDIN_FILENO;
    int save = dup(num);
    close(num);
    dup(put);
    if(multi) {
        if (std == '>') {
            printf("here\n");
            exec_redir(args[0], '<', 0);
        }
        // else {
        //     exec_redir(args[0], '>', 0);
        // }
    }
    else {
        exec_command(args[0]);
    }
    close(put);
    dup2(save, num);
    return 0;
}