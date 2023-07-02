#ifndef PIPEUTIL_H
#define PIPEUTIL_H

int pipef(char filename1[], char filename2[], int bytecount);
int namedpipef(char pipename[], int bytecount);

#endif