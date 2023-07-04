#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <cstdlib>

//Closes a file for a given file descriptor with error checking
void closef(int fd) {
    if(close(fd) == -1) {
        printf("\nError while closing the file\n");
        exit(0);
    }
}

//Creates a file for a given filename and permission and error checking
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


//This functions set the read/write pointer to the given offset from the given position in whence. 
//For example, offset 10 from the beginning of the file. With error checking.
void movefile_pointer(int fd, int offset, int whence) {
    if(whence == 2) 
        whence = SEEK_END;
    else if (whence == 1) 
        whence = SEEK_CUR;
    else 
        whence = SEEK_SET;

    int curr = lseek(fd, offset ,whence);
    if (curr == -1) {
        printf("\n Error while seeking in file\n");
        closef(fd);
        exit(0);
    }
}