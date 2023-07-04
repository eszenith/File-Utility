#include<stdio.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include "readUtil.h"
#include "fileUtil.h"
#include <cstdlib>

//Given a file descriptor, bytecount and buffer, This function reads the data into a buffer.
int readf(int fd , int bytecount, char* buff) {
    int no_of_bytes = 0;
    no_of_bytes = read(fd, buff, bytecount);
    if( no_of_bytes == -1) {
        printf("\nError while reading the file \n");
        return -1;
    }
    return no_of_bytes;
}

//This function takes a filename and bytecount and reads an prints data to the console. This function is a wrapper to readf() 
int read_file(char filename[], int bytecount, int offset, int whence) {

    int fd = open(filename, O_RDONLY);
    if (fd == -1) {
        printf("\nError in opening file : %s\n", filename);
        return -1;
    }
    
    movefile_pointer(fd, offset, whence);

    int no_of_bytes = 0;
    char* buff  = (char*)malloc(bytecount * (sizeof(char)));
    no_of_bytes = readf(fd, bytecount, buff);

    if(no_of_bytes== -1) {
        free(buff);
        closef(fd);
        return -1;
    }

    printf("\nData in file %s is :\n\n", filename);
    int k = 0;
    for(int i = 0;i<(bytecount);i++) {
        printf("%c", buff[i]);
    }
    printf("\n\n");
    
    free(buff);

    closef(fd);

    return 1;
    

} 
