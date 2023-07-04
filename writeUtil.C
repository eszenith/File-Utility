#include<stdio.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include "writeUtil.h"
#include "fileUtil.h"
#include <cstdlib>

//Given a file descriptor, bytecount and buffer, This function writes data from file to buffer
int writef(int fd , int bytecount, char* buff) {
    if(write(fd, buff, bytecount) == -1) {
        printf("\nError while writing to the file \n");
        return -1;
    }
    return 1;
}

//Takes data from the user and writes it to a given file This function is a wrapper to writef()
int write_file(char filename[], int bytecount, int offset, int whence) {

    int fd = open(filename, O_WRONLY );
    if (fd == -1) {
        printf("\nError in opening file : %s\n", filename);
        return -1;
    }

    movefile_pointer(fd, offset, whence);

    char* buff  = (char*)malloc(bytecount * (sizeof(char)));

    printf("\ninput the data that needs to be written : ");
    //scanf("%s", buff);
    fgets(buff,bytecount,stdin);
    printf("\nData to be written : %s\n\n", buff);

    writef(fd, bytecount, buff);
    
    free(buff);

    closef(fd);

    return 1;
    

} 
