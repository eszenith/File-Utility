#ifndef WRITEUTIL_H
#define WRITEUTIL_H

int writef(int fd , int bytecount, char* buff);
int write_file(char filename[], int bytecount, int offset, int whence) ;


#endif