#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <cstdlib>
#include <sys/stat.h>
#include "pipeUtil.h"
#include "readUtil.h"
#include "fileUtil.h"
#include "writeUtil.h"

//This function creates an unnamed pipe and transfers data from one file to another with error checking.
int pipef(char filename1[], char filename2[], int bytecount) {
    int pipefd[2];
    char* buff  = (char*)malloc(bytecount * (sizeof(char)));

    int no_of_bytes;

    if (pipe(pipefd) == -1) {
        printf("\nError while creating pipe\n");
        free(buff);
        return -1;
    }

    int input_fd = open(filename1, O_RDONLY);
    if (input_fd == -1) {
        printf("\nError while creating pipe\n");
        free(buff);
        closef(pipefd[1]);  
        closef(pipefd[0]);  
        return -1;
    }

    int output_fd= open(filename2, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (output_fd == -1) {
        printf("\nError while creating pipe\n");
        free(buff);
        closef(pipefd[1]);  
        closef(pipefd[0]);  
        return -1;
    }

    no_of_bytes = read(input_fd, buff, bytecount);
    
    if (write(pipefd[1], buff, no_of_bytes) != no_of_bytes){
        printf("\nError while creating pipe\n");
        free(buff);
        closef(pipefd[1]);  
        closef(pipefd[0]);  
        return -1;
        }
    

    close(input_fd);  
    close(pipefd[1]);  

    no_of_bytes = read(pipefd[0], buff, bytecount);

    if (write(output_fd, buff, no_of_bytes) != no_of_bytes) {
        printf("\nError while creating pipe\n");
        free(buff);
        return -1;
        }
    
    printf("Data succesfully written from %s to %s using an unnamed pipe\n", filename1, filename2);
    free(buff);
    close(output_fd);  
    close(pipefd[0]);  
    return 0;

}

// either makes and write to named pipe or read from named pipe depending on user argument to process
int namedpipef(char pipename[], int bytecount, int option, char* permissions) {
    char* buff  = (char*)malloc(bytecount * (sizeof(char)));

    if(option == 1) {
 
        printf("\n This is the writing process which creates and writes into the pipe \n");
        umask(0);
        mode_t mode = strtol(permissions, NULL, 8);
        mknod(pipename, S_IFIFO | mode, 0);
        int pipefd = open(pipename, O_WRONLY);
        printf("\nData to send through pipe : %s\n", pipename);
        fgets(buff,bytecount,stdin);
        if (write(pipefd, buff, bytecount) == -1) {
                printf("\nError while writing to named pipe\n");
                closef(pipefd);
                return -1;
        }
        closef(pipefd);
    }

    else {
        printf("\nThis is a reading process \n");
        char* buff2  = (char*)malloc(bytecount * (sizeof(char)));
        int pipefd = open(pipename, O_RDONLY);
        if (read(pipefd, buff2, bytecount) == -1) {
                printf("\nError while reading to named pipe\n");
                return -1;
        }
        printf("\nRecieved following from another writing process :\n");
        printf("%s\n", buff2);
        closef(pipefd);
        free(buff2);
    }

    free(buff);
    return 0;
}
