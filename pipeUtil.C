#include <stdio.h>
#include<unistd.h>
#include <fcntl.h>
#include <cstdlib>
#include <sys/stat.h>
#include "pipeUtil.h"
#include "readUtil.h"
#include "writeUtil.h"

int pipef(char filename1[], char filename2[], int bytecount) {
    int pipefd[2];
    char* buff  = (char*)malloc(bytecount * (sizeof(char)));

    int bytesRead;

    if (pipe(pipefd) == -1) {
        printf("\nError while creating pipe\n");
        return -1;
    }

    int inputFile = open(filename1, O_RDONLY);
    if (inputFile == -1) {
        printf("\nError while creating pipe\n");
        return -1;
    }

    int outputFile = open(filename2, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (outputFile == -1) {
        printf("\nError while creating pipe\n");
        return -1;
    }

    bytesRead = read(inputFile, buff, bytecount);
    
    if (write(pipefd[1], buff, bytesRead) != bytesRead){
        printf("\nError while creating pipe\n");
        return -1;
        }
    

    close(inputFile);  
    close(pipefd[1]);  

    bytesRead = read(pipefd[0], buff, bytecount);

    if (write(outputFile, buff, bytesRead) != bytesRead) {
        printf("\nError while creating pipe\n");
        return -1;
        }
    

    close(outputFile);  
    close(pipefd[0]);  
    return 0;

}
