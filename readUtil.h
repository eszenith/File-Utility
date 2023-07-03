#ifndef READUTIL_H
#define READUTIL_H

int readf(int fd , int bytecount, char* buff);
int read_file(char filename[], int bytecount, int offset, int whence);

#endif