#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h> //open 
#include <unistd.h> //read, write, close 
#include <errno.h> //errno
#include <sys/stat.h> //umask

int _random();

int main() {
    int num = 10;
    int size_bytes = num * sizeof(int);

    printf("Generating random numbers:\n");
    int numbers[num];
    int i;
    for( i = 0; i < num; i++) {
        numbers[i] = _random();
        printf("\t random %d: %d\n", i, numbers[i]);
    }

    printf("\nWriting numbers to file...\n\n");
    umask(0);
    int fd = open("numbers", O_CREAT | O_RDWR | O_TRUNC, 0666);
    if( fd < 0 ) {
        printf("errno: %d error: %s\n", errno, strerror(errno));
        return 0;
    }

    if( write(fd, &numbers, size_bytes) < 0) {
        printf("errno: %d error: %s\n", errno, strerror(errno));
        return 0;
    }
    
    if( close(fd) < 0) {
        printf("errno: %d error: %s\n", errno, strerror(errno));
        return 0;
    }

    printf("Reading numbers from file...\n\n");
    fd = open("numbers", O_RDONLY);
    if(fd < 0) {
        printf("errno: %d error: %s\n", errno, strerror(errno));
        return 0; 
    }
    int buff[10];
    if( read(fd, &buff, size_bytes) < 0) {
        printf("errno: %d error: %s\n", errno, strerror(errno));
        return 0;
    }

    printf("Verification that written values were the same:\n");
    for( i = 0; i < num; i++) {
        printf("\t random %d: %d\n", i, buff[i]);
    }

    close(fd);

    return 0;
}

int _random() {
    int random;
    int fd = open("/dev/random", O_RDONLY); 
    if (fd < 0) {
        printf("errno: %d error: %s\n", errno, strerror(errno));
        return 0;
    } 
    if (read(fd, &random, sizeof(int)) < 0) {
        printf("errno: %d error: %s\n", errno, strerror(errno));
        return 0;
    } 
    close(fd);
    return random;
}