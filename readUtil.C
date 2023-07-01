#include<stdio.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include "readUtil.h"
#include "fileUtil.h"
#include <cstdlib>

#define SIZE 20

int readf(int fd , int bytecount, char* buff) {
    if(read(fd, buff, bytecount) == -1) {
        printf("\nError while reading the file \n");
        return -1;
    }
    return 1;
}
//this function reads the file with given file name, byte count and position from where to read
// 
int read_file(char filename[], int bytecount) {

    int fd = open(filename, O_RDONLY);
    if (fd == -1) {
        printf("\nError in opening file : %s\n", filename);
        return -1;
    }

    char* buff  = (char*)malloc(bytecount * (sizeof(char)));
    if(readf(fd, bytecount, buff)== -1) {
        closef(fd);
        return -1;
    }

    printf("\nData in file %s is :\n\n", filename);
    printf("%s\n\n", buff);
    
    free(buff);

    closef(fd);

    return 1;
    

} 
