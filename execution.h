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

int exec_line(char *line);

int exec_command(char * command);

int exec_redir(char * command, char std, int multi);

int exec_fork(char * command, char ** args);
