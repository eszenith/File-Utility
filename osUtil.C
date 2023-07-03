#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "readUtil.h"
#include "writeUtil.h"
#include "statUtil.h"
#include "pipeUtil.h"
#include "fileUtil.h"

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
        printf("\n1. Read a file");
        printf("\n2. write to a file");
        printf("\n3. Get stat of file");
        printf("\n4. Unamed pipe to tansfer data from one file to another");
        printf("\n5. Named pipe for process communication (Read data)");
        printf("\n6. Named pipe for process communication (Write data)");
        printf("\n7. Create a new file");
        printf("\n0. Exit \nEnter Option : ");
        scanf("%d", &option);

        switch(option) {
            case 1 :{
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

                read_file(filename,bytecount, offset, whence-1);
            }
            break;
            case 2 :{
                int bytecount=0;
                char filename[2048];
                int whence = 0;
                int offset = 0;

                printf("\nEnter file name : ");
                scanf("%s", filename);
                printf("\nEnter bytes to write : ");
                scanf("%d", &bytecount);
                do {
                printf("\nEnter from where to start writing to file : ");
                printf("\n1. beginning\n");
                printf("\n2. current\n");
                printf("\n3. end\n");
                scanf("%d", &whence);
                }while(whence-1 < 0 || whence-1 > 2);

                printf("\n Enter offset inside file: ");
                scanf("%d", &offset);

                write_file(filename,bytecount, offset, whence-1);
                break;
            }
            case 3 : {
                int bytecount=0;
                char filename[2048];
                printf("\nEnter file name : ");
                scanf("%s", filename);
                stat_file(filename);
                break;
            }
            case 4: {
                int bytecount=0;
                char filename1[2048];
                char filename2[2048];
                printf("\nEnter filename1 : ");
                scanf("%s", filename1);
                printf("\nEnter filename2 : ");
                scanf("%s", filename2);
                printf("\nEnter bytes to read : ");
                scanf("%d", &bytecount);
                pipef(filename1, filename2, bytecount);
                break;
                
            }
            case 5: {
                int bytecount=0;
                char pipename[2048];
                printf("\nEnter pipename : ");
                scanf("%s", pipename);
                printf("\nEnter bytes to read : ");
                scanf("%d", &bytecount);
                namedpipef( pipename, bytecount, 1);
                break;
                
            }
            case 6: {
                int bytecount=0;
                char pipename[2048];
                printf("\nEnter pipename : ");
                scanf("%s", pipename);
                printf("\nEnter bytes to read : ");
                scanf("%d", &bytecount);
                namedpipef( pipename, bytecount, 2);
                break;
                
            }
            case 7: {
                char filename[2048];
                char perms[2048];
                printf("\nEnter filename : ");
                scanf("%s", filename);
                printf("\nEnter permissions : ");
                scanf("%s", perms);
                create_file( filename, perms);
                break;
                
            }
        }
    }while(0);
}

void help() {
    printf("\n-----------------help------------------\n");
    printf("\nUSAGE : ./main [OPTIONS] [PARAMETERS]\n");
    printf("\n1.  ./main read filename bytecount offset whence\n");
    printf("\n2.  ./main write filename bytecount offset whence \n");
    printf("\n3.  ./main stat filename \n");
    printf("\n4.  ./main pipe filename1 filename2 bytecount\n");
    printf("\n5.  ./main npipe bytecount\n");
    printf("\n6.  ./main creat filename permissions\n");
    printf("\n7.  ./main menu\n");
    printf("\n8.  ./main help\n");
}
int main(int argc, char** argv) {
    
    if(argc <= 1) {
        printf("Invalid arguments, check help using ./main help or ./main -h \n");
        return 1;
    }
    
    if ( (strcmp(argv[1], "read") == 0) || (strcmp(argv[1], "-r") == 0) ) {
        if( argc >= 6 && isnumber(argv[3]) && isnumber(argv[4]) && isnumber(argv[5]) )   {
            read_file( argv[2], getnumber(argv[3]), getnumber(argv[4]), getnumber(argv[5]) );
        }
        else {
            printf("Invalid arguments, check help using ./main help or ./main -h \n");
        }
    }
    else if ( (strcmp(argv[1], "creat") == 0) || (strcmp(argv[1], "-c") == 0) ) {
        if(argc >= 4 && isnumber(argv[3]))   {
            create_file(argv[2], argv[3]);
        }
        else {
            printf("Invalid arguments, check help using ./main help or ./main -h \n");
        }
    }

    else if ( (strcmp(argv[1], "write") == 0) || (strcmp(argv[1], "-w") == 0) ) {
        if( argc >= 6 && isnumber(argv[3]) && isnumber(argv[4]) && isnumber(argv[5]) )   {
            write_file( argv[2], getnumber(argv[3]), getnumber(argv[4]), getnumber(argv[5]) );
        }
        else {
            printf("Invalid arguments, check help using ./main help or ./main -h \n");
        }
    }

    
    else if ( (strcmp(argv[1], "stat") == 0) || (strcmp(argv[1], "-s") == 0) ) {
        if(argc >= 3)   {
            stat_file(argv[2]);
        }
        else {
            printf("Invalid arguments, check help using ./main help or ./main -h \n");
        }
    }

    else if ( (strcmp(argv[1], "pipe") == 0) || (strcmp(argv[1], "-p") == 0) ) {
        if( argc >= 5 && isnumber(argv[4]) )   {
            pipef( argv[2], argv[3],getnumber(argv[4]));
        }
        else {
            printf("Invalid arguments, check help using ./main help or ./main -h \n");
        }
    }

    else if ( (strcmp(argv[1], "npipe") == 0) || (strcmp(argv[1], "-np") == 0) ) {
        if( argc >= 5 && isnumber(argv[4]) )   {
            if (strcmp(argv[3],"read") == 0)
                namedpipef( argv[2], getnumber(argv[4]),1 );
            else if (strcmp(argv[3],"write") == 0)
                namedpipef( argv[2], getnumber(argv[4]),2 );
            else
                printf("Invalid arguments, check help using ./main help or ./main -h \n");
        }
        else {
            printf("Invalid arguments, check help using ./main help or ./main -h \n");
        }
    }
    else if ( (strcmp(argv[1], "menu") == 0) || (strcmp(argv[1], "-m") == 0) ) {
        if( argc >=2 )   {
            menu();
        }
        else {
            printf("Invalid arguments, check help using ./main help or ./main -h \n");
        }
    }
    else if ( (strcmp(argv[1], "help") == 0) || (strcmp(argv[1], "-h") == 0) ) {
        help();
    }
    else {
        printf("Invalid arguments, check help using ./main help or ./main -h \n");
    }


    return 0;
}