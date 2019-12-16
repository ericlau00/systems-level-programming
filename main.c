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

    char host[HOST_NAME_MAX];
    char cwd[PATH_MAX];

    while(1) {
        getcwd(cwd, PATH_MAX);
        gethostname(host, HOST_NAME_MAX);
        printf("%s@%s:%s$ ", pw->pw_name, host, cwd);
        fgets(input, SIZE, stdin);
        stripper(input, '\n');
        exec_line(input);
    }
    return 0;
}