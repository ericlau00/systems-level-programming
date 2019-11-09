#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h> //open 
#include <unistd.h> //read, write, close 
#include <errno.h>

int _random() {
    int * buff = malloc(sizeof(int));
    int fd = open("/dev/random", O_RDONLY); 
    if (fd < 0) {
        printf("errno: %d error: %s\n", errno, strerror(errno));
        return 0;
    } 
    if (read(fd, buff, sizeof(int)) < 0) {
        printf("errno: %d error: %s\n", errno, strerror(errno));
        return 0;
    } 
    int rand = *buff;
    free(buff);
    close(fd);
    return rand;
}

int main() {
    printf("%d\n",_random());
    return 0;
}