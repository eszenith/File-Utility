#include <stdio.h>
#include<unistd.h>
#include <fcntl.h>
#include <cstdlib>
#include <sys/stat.h>
#include "pipeUtil.h"
#include "readUtil.h"
#include "fileUtil.h"
#include "writeUtil.h"

int pipef(char filename1[], char filename2[], int bytecount) {
    int pipefd[2];
    char* buff  = (char*)malloc(bytecount * (sizeof(char)));

    int bytesRead;

    if (pipe(pipefd) == -1) {
        printf("\nError while creating pipe\n");
        free(buff);
        return -1;
    }

    int inputFile = open(filename1, O_RDONLY);
    if (inputFile == -1) {
        printf("\nError while creating pipe\n");
        free(buff);
        return -1;
    }

    int outputFile = open(filename2, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (outputFile == -1) {
        printf("\nError while creating pipe\n");
        free(buff);
        return -1;
    }

    bytesRead = read(inputFile, buff, bytecount);
    
    if (write(pipefd[1], buff, bytesRead) != bytesRead){
        printf("\nError while creating pipe\n");
        free(buff);
        return -1;
        }
    

    close(inputFile);  
    close(pipefd[1]);  

    bytesRead = read(pipefd[0], buff, bytecount);

    if (write(outputFile, buff, bytesRead) != bytesRead) {
        printf("\nError while creating pipe\n");
        free(buff);
        return -1;
        }
    
    free(buff);
    close(outputFile);  
    close(pipefd[0]);  
    return 0;

}


int namedpipef(char pipename[], int bytecount) {
    char* buff  = (char*)malloc(bytecount * (sizeof(char)));
    mknod(pipename, S_IFIFO | 0777, 0);

    if(fork() != 0) {
        int pipefd = open(pipename, O_WRONLY);
        printf("\nIn parent process write data to send to child process through pipe named : %s\n", pipename);
        scanf("%s", buff);
        if (write(pipefd, buff, bytecount) == -1) {
                printf("\nError while writing to named pipe\n");
                return -1;
            }
        closef(pipefd);
    }
    else {
        printf("\nIn child: %s\n", pipename);
        char* buff2  = (char*)malloc(bytecount * (sizeof(char)));
        int pipefd = open(pipename, O_RDONLY);
        if (read(pipefd, buff2, bytecount) == -1) {
                printf("\nError while readingto named pipe\n");
                return -1;
        }
        printf("%s", buff2);
        closef(pipefd);
        free(buff2);
    }

    free(buff);
    return 0;
}
