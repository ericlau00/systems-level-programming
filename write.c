#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/types.h>
#include <errno.h>
#include <sys/shm.h>

#include <fcntl.h>
#define SEM_KEY 24602
#define SHM_KEY 24601
#define SEG_SIZE 200
#define FILE_NAME "file"

int main() {
    int shmd;
    char * data;

    shmd = shmget(SHM_KEY, SEG_SIZE, 0600);
    if(shmd < 0) {
        printf("error %d: %s\n", errno, strerror(errno));
        return 1;
    }

    data = shmat(shmd, 0, 0);
    printf("Last addition: %s\n", data);

    printf("Your addition: ");
    fgets(data, SEG_SIZE, stdin);
    *strchr(data, '\n') = 0;

    int fd = open(FILE_NAME, O_WRONLY | O_APPEND);
    write(fd, data, SEG_SIZE);
    close(fd);

    shmdt(data); // detach pointer from variable
    return 0;
}