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

struct stat fill_buff(char * path);
long print_directory(char * path, int sub);
long print_file(struct stat buff, struct dirent * file);
int print_permissions(int perm);
int print_time(char * time); 

int main(int argc, char * argv[]) {
    char directory[256];
    if(argc == 1) {
        printf("Enter a directory to scan: ");
        fgets(directory, sizeof(directory), stdin);
    } else {
        strcpy(directory, argv[1]);
    }
    int i;
    for(i = 0; i < sizeof(directory); i++) {
        if(directory[i] == '\n') {
            directory[i] = '\0';
        }
    }
    printf("Statistics for directory: %s\n", directory);
    printf("Total size: %ld bytes\n", print_directory(directory, 0));
    return 0;
}

long print_directory(char * path, int sub) {
    long total_size = 0;
    struct stat buff = fill_buff(path);
    // printf("%s\n",path);
    // st_mode returns the permissions and whether is directory. 
    // the first digit is 4 if is a directory 
    if(buff.st_mode / 010000 == DT_DIR) {
        DIR * stream = opendir(path);
        struct dirent * file;
        long size = 0;
        for(file = readdir(stream); file != NULL; file = readdir(stream)) {
            char file_path[256] = ""; 
            strcat(file_path, path);
            strcat(file_path,"/");
            strcat(file_path, file->d_name);
            buff = fill_buff(file_path);

            int i;
            for(i = 0; i < sub; i++) {
                printf("\t");
            }

            size += print_file(buff, file);
            if(file->d_type == DT_DIR && strcmp(file->d_name, "..") != 0 && strcmp(file->d_name, ".") != 0) {
                size += print_directory(file_path, sub+1);
            }
        }
        total_size += size;
        closedir(stream);
    }
    return total_size;
}

struct stat fill_buff(char * path) {
    struct stat buff;
    if(stat(path, &buff) < 0) {
        printf("errno: %d error: %s\n", errno, strerror(errno));
        return buff; 
    }
    return buff; 
}

long print_file(struct stat buff, struct dirent * file) {
    long size = 0;
    if(file->d_type == DT_DIR) {
        printf("d");
    } else { //files otherwise are regular files. 
        printf("-");
        size += buff.st_size;
    }

    print_permissions(buff.st_mode % 01000);

    printf(" %2ld", buff.st_nlink);  

    //2 left justifies 
    //user and group owners 
    printf(" %s %s", getpwuid(buff.st_uid)->pw_name, getgrgid(buff.st_gid)->gr_name);
    
    //5 left justifies 
    printf(" %5ld", buff.st_size);

    print_time(ctime(&buff.st_mtime));

    printf(" %s\n",file->d_name);

    return size; 
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