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