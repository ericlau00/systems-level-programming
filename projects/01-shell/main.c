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
#include <limits.h>
#include <sys/types.h>
#include <pwd.h>
#include <grp.h>
#include <sys/wait.h>
#include "execution.h"
#include "parse.h"

int main() {
    int SIZE = 256;
    char input[SIZE];

    int uid = getuid();
    struct passwd * pw = getpwuid(uid);

    char host[64];
    char cwd[4096];

    while(1) {
        getcwd(cwd, 4096);
        gethostname(host, 64);
        // printf("%s@%s:%s$ ", pw->pw_name, host, cwd);
        fgets(input, SIZE, stdin);
        stripper(input, '\n');
        exec_line(input);
    }
    return 0;
}