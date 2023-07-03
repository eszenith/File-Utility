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
    mode_t mode = strtol(mode1, NULL, 8);
    mode_t old = umask(mode);
    int fd = creat(filename, mode);
    umask(old);
    closef(fd);
}