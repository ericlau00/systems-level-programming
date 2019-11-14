#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h> //open 
#include <unistd.h> //read, write, close 
#include <errno.h> //errno
#include <sys/stat.h> //umask, stat
#include <time.h> //ctime

int main() {
    struct stat buff; 
    if(stat("./main.c", &buff) < 0) {
        printf("errno: %d error: %s\n", errno, strerror(errno));
        return 0;
    }
    printf("%ld bytes\n",buff.st_size);
    printf("%o\n", buff.st_mode);
    printf("%s", ctime(&buff.st_atime));
    return 0;
}