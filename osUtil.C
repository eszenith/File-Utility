#include<stdio.h>
#include <stdlib.h>
#include<string.h>
#include<ctype.h>
#include "readUtil.h"
#include "writeUtil.h"
#include "statUtil.h"
#include "pipeUtil.h"
int isnumber(char num[]) {
    //if string is empty it will only have the null character
    if (num[0] == '\0') {
        return 0;
    }

    int i = 0;
    if (num[0] == '-'){
        i+=1;
    }

    while( i < strlen(num) && isdigit(num[i]) ) {
        i++;
    }
    // if loop worked till last index then number is string
    return i==strlen(num);
}

int getnumber(char num[]) {
    //printf("\ngot : %d\n", atoi(num));
    return atoi(num);
}

int main(int argc, char** argv) {
    
    
    if ( (strcmp(argv[1], "read") == 0) || (strcmp(argv[1], "-r") == 0) ) {
        if(argc >= 3 && isnumber(argv[3]))   {
            read_file(argv[2], getnumber(argv[3]));
        }
        else {
            printf("Invalid arguments : ");
        }
    }

    else if ( (strcmp(argv[1], "write") == 0) || (strcmp(argv[1], "-w") == 0) ) {
        if( argc >= 4 && isnumber(argv[3]) && isnumber(argv[4]) && isnumber(argv[5]) )   {
            write_file( argv[2], getnumber(argv[3]), getnumber(argv[4]), getnumber(argv[5]) );
        }
        else {
            printf("Invalid arguments : ");
        }
    }

    
    else if ( (strcmp(argv[1], "stat") == 0) || (strcmp(argv[1], "-s") == 0) ) {
        if(argc >= 2)   {
            stat_file(argv[2]);
        }
        else {
            printf("Invalid arguments : ");
        }
    }

    else if ( (strcmp(argv[1], "pipe") == 0) || (strcmp(argv[1], "-w") == 0) ) {
        if( argc >= 4 && isnumber(argv[4]) )   {
            pipef( argv[2], argv[3],getnumber(argv[4]));
        }
        else {
            printf("Invalid arguments : ");
        }
    }

    return 0;
}