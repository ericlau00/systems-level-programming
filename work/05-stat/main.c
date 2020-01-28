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
    char * perms[8] = {"---","--x","-w-","-wx","r--","r-x","rw-","rwx"};
    if(stat("./main.c", &buff) < 0) {
        printf("errno: %d error: %s\n", errno, strerror(errno));
        return 0;
    }
    printf("metadata about ./main.c\n");
    printf("\tbytes: %ld \n",buff.st_size);
    int perm = buff.st_mode % 01000;
    printf("\tpermissions: %o\n", perm);
    printf("\tlast accessed: %s\n", ctime(&buff.st_atime));

    printf("bytes humanized\n");
    printf("\t%ld GB %ld MB %ld KB %ld B\n\n", 
            buff.st_size/1000000000, 
            buff.st_size/1000000, 
            buff.st_size/1000, 
            buff.st_size);

    printf("ls -l form attempt\n");
    printf("\t-%s%s%s %ld %s\n", 
            perms[(perm % 01000) / 0100], 
            perms[(perm % 0100) / 010], 
            perms[perm % 010],
            buff.st_size, 
            ctime(&buff.st_atime));
    // printf("%o\n", buff.st_mode % 01000);
    return 0;
}