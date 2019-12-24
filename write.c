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

#include "headers.h"

int main() {
    int semd = semget(SEM_KEY, 1, 0);
    struct sembuf sb;
    sb.sem_num = 0;
    sb.sem_op = -1;
    printf("trying to get in\n");
    semop(semd, &sb, 1);

    write_line();

    sb.sem_op = 1;
    semop(semd, &sb, 1);
    return 0;
}