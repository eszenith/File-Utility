#ifndef FILEUTIL_H
#define FILEUTIL_H

void closef(int fd);
void create_file(char filename[], char* mode1);
void movefile_pointer(int fd, int offset, int whence);

#endif