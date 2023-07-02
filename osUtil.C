#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
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

void menu(){
    int option = 0;
    do {

        printf("\n-----------------MENU-----------------\n");
        printf("\n1. Read a file\n");
        printf("\n2. write to a file\n");
        printf("\n3. Get stat of file\n");
        printf("\n4. Unamed pipe to tansfer data from one file to another\n");
        printf("\n5. Named pipe for process communication\n");
        scanf("%d", &option);

        switch(option) {
            case 1 :{
                int bytecount=0;
                char filename[2048];
                printf("\nEnter file name : ");
                scanf("%s", filename);
                printf("\nEnter bytes to read : ");
                scanf("%d", &bytecount);
                read_file(filename, bytecount);
                break;
            }
            
            case 2 :{
                int bytecount=0;
                char filename[2048];
                int whence = 0;
                int offset = 0;

                printf("\nEnter file name : ");
                scanf("%s", filename);
                printf("\nEnter bytes to read : ");
                scanf("%d", &bytecount);
                do {
                printf("\nEnter from where to read file : ");
                printf("\n1. beginning\n");
                printf("\n2. current\n");
                printf("\n3. end\n");
                scanf("%d", &whence);
                }while(whence-1 < 0 || whence-1 > 2);

                printf("\n Enter offset inside file: ");
                scanf("%d", &offset);

                write_file(filename,bytecount, offset, whence);
                break;
            }
            case 3 :{
                int bytecount=0;
                char filename[2048];
                printf("\nEnter file name : ");
                scanf("%s", filename);
                printf("\nEnter bytes to read : ");
                scanf("%d", bytecount);
                read_file(filename,bytecount);
                break;
            }
        }
    }while(option != 0);
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

    else if ( (strcmp(argv[1], "npipe") == 0) || (strcmp(argv[1], "-w") == 0) ) {
        if( argc >= 2 && isnumber(argv[3]) )   {
            namedpipef( argv[2], getnumber(argv[3]));
        }
        else {
            printf("Invalid arguments : ");
        }
    }
    else if ( (strcmp(argv[1], "menu") == 0) || (strcmp(argv[1], "-m") == 0) ) {
        if( argc >=1 )   {
            menu();
        }
        else {
            printf("Invalid arguments : ");
        }
    }


    return 0;
}