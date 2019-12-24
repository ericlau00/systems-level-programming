#include "headers.h"

int main(int argc, char * argv[]) {
    if (argc > 1) {
        if(strcmp(argv[1], "-c") == 0) {
            create_semaphore();
            create_shared_memory();
            create_file(FILE_NAME);
        }
        else if (strcmp(argv[1], "-r") == 0) {
            int semd = semget(SEM_KEY, 1, 0);

            struct sembuf sb;
            sb.sem_num = 0;
            sb.sem_op = -1;
            printf("trying to get in\n");
            semop(semd, &sb, 1);

            read_file(FILE_NAME);

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