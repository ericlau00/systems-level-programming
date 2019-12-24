#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/types.h>
#include <errno.h>
#include <sys/shm.h>

#define SEM_KEY 24602
#define SHM_KEY 24601
#define SEG_SIZE 200

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
        printf("error %d: %s\n", errno, strerror(errno));
        semd = semget(SEM_KEY, 1, 0);
        v = semctl(semd, 0, GETVAL, 0);
        printf("semctl returned: %d\n", v);
    } else {
        union semun us;
        us.val = 1;
        r = semctl(semd, 0, SETVAL, us);
        printf("semctl returned: %d\n", r);
    }
    printf("semaphore created\n");
    return semd;
}

int remove_semaphore(int semd) {
    semctl(semd, IPC_RMID, 0);
    printf("semaphore removed\n");
    return 0;
}

int create_shared_memory() {
    int shmd;
    shmd = shmget(SHM_KEY, SEG_SIZE, IPC_CREAT | 0644);
    printf("shared memory created\n");
    return shmd;
}

int remove_shared_memory(int shmd) {
    shmctl(shmd, IPC_RMID, 0);
    printf("shared memory removed\n");
    return 0;
}

int main(int argc, char * argv[]) {
    int semd;
    int shmd;
    if (argc > 1) {
        if(strcmp(argv[1], "-c") == 0) {
            semd = create_semaphore();
            shmd = create_shared_memory();
            // printf("file created\n");
        }
        else if (strcmp(argv[1], "-r") == 0) {
            remove_shared_memory(shmd);
            printf("file removed\n");
            remove_semaphore(semd);
        }
        else if (strcmp(argv[1],"-v") == 0 ) {
            // view
            printf("The story so far:\n");
        }
    }
    // printf("%d %s %s\n", argc, argv[0], argv[1]);
    return 0;
}