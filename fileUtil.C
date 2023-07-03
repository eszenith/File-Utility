#include<stdio.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include <cstdlib>

void closef(int fd) {
    if(close(fd) == -1) {
        printf("\nError while closing the file\n");
        exit(0);
    }
}

void create_file(char filename[], char* mode1) {
    umask(0);
    mode_t mode = strtol(mode1, NULL, 8);
    int fd = creat(filename, mode);
    if(fd == -1) {
        printf("\nError while creating file.\n");
    }
    printf("\nFile succesfully created\n");
    closef(fd);
}

void movefile_pointer(int fd, int offset, int whence) {
    if(whence == 2) 
        whence = SEEK_END;
    else if (whence == 1) 
        whence = SEEK_CUR;
    else 
        whence = SEEK_SET;

    int curr = lseek(fd, offset ,whence);
    //printf("\ncurrent is : %d\n", curr);
    if (curr == -1) {
        printf("\n Error while seeking in file\n");
        exit(0);
    }
}