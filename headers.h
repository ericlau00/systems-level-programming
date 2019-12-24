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

int create_semaphore();
int remove_semaphore(int semd);

int create_shared_memory();
int remove_shared_memory(int shmd);

int create_file(char * name);
int remove_file(char * name);
int read_file(char * name);

int write_line();
