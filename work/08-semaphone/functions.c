#include "headers.h"

int create_semaphore() {
    int v, r;

    int semd = semget(SEM_KEY, 1, IPC_CREAT | IPC_EXCL | 0644);
    if(semd == -1) {
        semd = semget(SEM_KEY, 1, 0);
        v = semctl(semd, 0, GETVAL, 0);
    } else {
        union semun us;
        us.val = 1;
        r = semctl(semd, 0, SETVAL, us);
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
    while(read(fd, buff, SEG_SIZE) > 0) {
        printf("%s\n", buff);
    }
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

int write_line() {
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

    shmdt(data);

    return 0;
}