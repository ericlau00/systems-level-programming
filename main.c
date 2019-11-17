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

int main() {
    DIR * stream = opendir("./");
    // printf("%p\n", stream);
    struct dirent * entry;
    long size = 0; 
    for(entry = readdir(stream); entry != NULL; entry = readdir(stream)){
        struct stat buff;
        if(stat(entry->d_name, &buff) < 0) {
            printf("errno: %d error: %s\n", errno, strerror(errno));
            return 0;
        }

        if(entry->d_type == 4) {
            printf("directory");
        } else {
            printf("regular file");
        }

        printf(" %ld bytes", buff.st_size);

        size += buff.st_size;

        printf(" %s\n",entry->d_name);

    }
    printf("total size: %ld bytes\n", size);
    return 0;
}