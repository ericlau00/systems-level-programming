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

int main() {
    char * perms[8] = {"---","--x","-w-","-wx","r--","r-x","rw-","rwx"};
    DIR * stream = opendir("./");
    struct dirent * file;
    long size = 0; 
    for(file = readdir(stream); file != NULL; file = readdir(stream)){
        struct stat buff;
        if(stat(file->d_name, &buff) < 0) {
            printf("errno: %d error: %s\n", errno, strerror(errno));
            return 0;
        }

        if(file->d_type == DT_DIR) {
            printf("d");
        } else {
            printf("-");
            size += buff.st_size;
        }

        int perm = buff.st_mode % 01000;

        printf("%s%s%s", 
                perms[(perm % 01000) / 0100], 
                perms[(perm % 0100) / 010], 
                perms[perm % 010]
                );

        printf(" %ld", buff.st_nlink);
        printf(" %s %s", getpwuid(buff.st_uid)->pw_name, getgrgid(buff.st_gid)->gr_name);
        printf(" %5ld ", buff.st_size);

        char * time = ctime(&buff.st_atime);
        time[strlen(time) - 1] = '\0';
        printf("%s", time);
        printf(" %s\n",file->d_name);


    }
    printf("total size: %ld bytes\n", size);
    return 0;
}