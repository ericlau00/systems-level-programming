#define _GNU_SOURCE
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h> //open 
#include <unistd.h> //read, write, close 
#include <errno.h> //errno
#include <sys/stat.h> //umask, stat
#include <time.h> //ctime
#include <dirent.h>
#include <sys/types.h>
#include <pwd.h>
#include <grp.h>

int print_permissions(int perm);
int print_time(char * time); 

int main() {
    DIR * stream = opendir("./");
    struct dirent * file;
    long size = 0; 

    printf("Statistics for directory: .\n");
    for(file = readdir(stream); file != NULL; file = readdir(stream)){
        struct stat buff;
        if(stat(file->d_name, &buff) < 0) {
            printf("errno: %d error: %s\n", errno, strerror(errno));
            return 0;
        }

        if(file->d_type == DT_DIR) {
            printf("d");
        } else { //files otherwise are regular files. 
            printf("-");
            size += buff.st_size;
        }

        print_permissions(buff.st_mode % 01000);

        printf(" %ld", buff.st_nlink);  

        //2 left justifies 
        //user and group owners 
        printf(" %2s %s", getpwuid(buff.st_uid)->pw_name, getgrgid(buff.st_gid)->gr_name);
        
        //5 left justifies 
        printf(" %5ld", buff.st_size);

        print_time(ctime(&buff.st_mtime));

        printf(" %s\n",file->d_name);
    }
    printf("total size: %ld bytes\n", size);
    closedir(stream);
    return 0;
}

int print_permissions(int perm) {
    char * perms[8] = {"---","--x","-w-","-wx","r--","r-x","rw-","rwx"};
    printf("%s%s%s", 
        perms[(perm % 01000) / 0100], 
        perms[(perm % 0100) / 010], 
        perms[perm % 010]
        );
    return 0;
}

int print_time(char * time) {
    //removes day of the week 
    int strip_front;
    for(strip_front = 0; strip_front < strlen(time); strip_front++) {
        time[strip_front] = time[strip_front + 3];
    }
    //removes year 
    int strip_end;
    for(strip_end = 3; strip_end > 0; strip_end--) {
        time[strlen(time) - strip_end] = '\0';
    }
    printf("%s", time);
    return 0;
}