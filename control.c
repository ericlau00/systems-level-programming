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

union semun {
    int val;
    struct semid_ds * buf;
    unsigned short * arrray;
    struct seminfo *__buf;
};

int create_semaphore() {
    int semd;
    int v, r;

    semd = semget(SEM_KEY, 1, IPC_CREAT | IPC_EXCL | 0644);
    if(semd == -1) {
        // printf("error %d: %s\n", errno, strerror(errno));
        semd = semget(SEM_KEY, 1, 0);
        v = semctl(semd, 0, GETVAL, 0);
        // printf("semctl returned: %d\n", v);
    } else {
        union semun us;
        us.val = 1;
        r = semctl(semd, 0, SETVAL, us);
        // printf("semctl returned: %d\n", r);
    }
    printf("semaphore created\n");
    return semd;
}

int remove_semaphore(int semd) {
    semctl(semd, IPC_RMID, 0);
    printf("semaphore removed\n");
    return 0;
}

int create_file(char * name) {
    int fd;
    fd = open(name, O_CREAT | O_EXCL | O_TRUNC, 0644);
    if (fd < 0) {
        fd = open(name, O_TRUNC);
    }
    close(fd);
    printf("file created\n");
    return fd;
}

int remove_file(char * name) {
    if (remove(name) == 0) {
        printf("file removed\n");
    } else {
        printf("File not removed\n");
    }
    return 0;
}

int read_file(char * name) {
    int fd;
    fd = open(name, O_RDONLY);
    if(fd < 0) {
        printf("error %d: %s\n", errno, strerror(errno));
        return 1;
    }
    printf("The story so far:\n");
    char buff[SEG_SIZE];
    read(fd, buff, SEG_SIZE);
    printf("%s\n", buff);
    close(fd);
}

int create_shared_memory() {
    int shmd;
    shmd = shmget(SHM_KEY, SEG_SIZE, IPC_CREAT | 0600);
    printf("shared memory created\n");
    return shmd;
}

int remove_shared_memory(int shmd) {
    shmctl(shmd, IPC_RMID, 0);
    printf("shared memory removed\n");
    return 0;
}

int main(int argc, char * argv[]) {
    if (argc > 1) {
        if(strcmp(argv[1], "-c") == 0) {
            create_semaphore();
            create_shared_memory();
            create_file(FILE_NAME);
        }
        else if (strcmp(argv[1], "-r") == 0) {
            int semd = semget(SEM_KEY, 1, 0);
            int shmd = shmget(SHM_KEY, SEG_SIZE, 0600);
            remove_shared_memory(shmd);
            remove_file(FILE_NAME);
            remove_semaphore(semd);
        }
        else if (strcmp(argv[1],"-v") == 0 ) {
            read_file(FILE_NAME);
        }
    }
    return 0;
}