#include<stdio.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include "writeUtil.h"
#include "fileUtil.h"
#include <cstdlib>

int writef(int fd , int bytecount, char* buff) {
    if(write(fd, buff, bytecount) == -1) {
        printf("\nError while writing to the file \n");
        return -1;
    }
    return 1;
}



void movefile_pointer(int fd, int offset, int whence) {
    if(whence == 2) 
        whence = SEEK_END;
    else if (whence == 1) 
        whence = SEEK_CUR;
    else 
        whence = SEEK_SET;

    int curr = lseek(fd, offset ,whence);
    printf("\ncurrent is : %d\n", curr);
    if (curr == -1) {
        printf("\n Error while seeking in file\n");
        exit(0);
    }
}
//this function reads the file with given file name, byte count and position from where to read
// 
int write_file(char filename[], int bytecount, int offset, int whence) {

    int fd = open(filename, O_WRONLY);
    if (fd == -1) {
        printf("\nError in opening file : %s\n", filename);
        return -1;
    }

    movefile_pointer(fd, offset, whence);

    char* buff  = (char*)malloc(bytecount * (sizeof(char)));

    printf("i\n nput the data that needs to be written : ");
    scanf("%s", buff);
    printf("Data to be written : %s\n\n", buff);

    writef(fd, bytecount, buff);
    
    free(buff);

    closef(fd);

    return 1;
    

} 
