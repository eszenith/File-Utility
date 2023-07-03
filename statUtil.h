#ifndef STATUTIL_H
#define STATUTIL_H


void displayStatInfo(const struct stat *sb);
void stat_file(char filname[]);
void printPermissions(mode_t mode);

#endif