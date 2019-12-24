#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/types.h>
#include <errno.h>

#define KEY 24602

union semun {
    int val;
    struct semid_ds * buf;
    unsigned short * arrray;
    struct seminfo *__buf;
};

int create_semaphore() {
    int semd;
    int v, r;

    semd = semget(KEY, 1, IPC_CREAT | IPC_EXCL | 0644);
    if(semd == -1) {
        printf("error %d: %s\n", errno, strerror(errno));
        semd = semget(KEY, 1, 0);
        v = semctl(semd, 0, GETVAL, 0);
        printf("semctl returned: %d\n", v);
    } else {
        union semun us;
        us.val = 1;
        r = semctl(semd, 0, SETVAL, us);
        printf("semctl returned: %d\n", r);
    }
    return semd;
}

int remove_semaphore(int semd) {
    semctl(semd, IPC_RMID, 0);
    return 0;
}

int main(int argc, char * argv[]) {
    int semd;
    if (argc > 1) {
        if(strcmp(argv[1], "-c") == 0) {
            // create
            semd = create_semaphore();
            printf("semaphore created\n");
            printf("shared memory created\n");
            printf("file created\n");
        }
        else if (strcmp(argv[1], "-r") == 0) {
            remove_semaphore(semd);
            printf("remove\n");
        }
        else if (strcmp(argv[1],"-v") == 0 ) {
            // view
            printf("The story so far:\n");
        }
    }
    // printf("%d %s %s\n", argc, argv[0], argv[1]);
    return 0;
}