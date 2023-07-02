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

void create_file(char filename[]) {
    int fd = creat(filename,0644 );
    closef(fd);
}