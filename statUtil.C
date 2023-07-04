#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <cstdlib>
#include <stdio.h>

//This function prints the formatted file permission details for a given mode variable.
void printPermissions(mode_t mode)
{
    printf((mode & S_IRUSR) ? "r" : "-");
    printf((mode & S_IWUSR) ? "w" : "-");
    printf((mode & S_IXUSR) ? "x" : "-");
    printf((mode & S_IRGRP) ? "r" : "-");
    printf((mode & S_IWGRP) ? "w" : "-");
    printf((mode & S_IXGRP) ? "x" : "-");
    printf((mode & S_IROTH) ? "r" : "-");
    printf((mode & S_IWOTH) ? "w" : "-");
    printf((mode & S_IXOTH) ? "x" : "-");
    printf("\n");
}

//Given a filled structure stat, this function prints the data of structure on console.
void displayStats(char *filename, const struct stat *sb)
{
    printf("\n\nFile type: ");
    switch (sb->st_mode & S_IFMT)
    {
    case S_IFREG:
        printf("regular file\n");
        break;
    case S_IFDIR:
        printf("directory\n");
        break;
    case S_IFCHR:
        printf("character device\n");
        break;
    case S_IFBLK:
        printf("block device\n");
        break;
    case S_IFLNK:
        printf("symbolic (soft) link\n");
        break;
    case S_IFIFO:
        printf("FIFO or pipe\n");
        break;
    case S_IFSOCK:
        printf("socket\n");
        break;
    default:
        printf("unknown file type?\n");
        break;
    }
    printf("File permissions: 0%o  ", sb->st_mode & 4095);
    printPermissions(sb->st_mode);
    printf("Device containing i-node: %d \n", sb->st_dev);

    printf("I-node number: %d\n", sb->st_ino);

    printf("Number of (hard) links: %d\n", sb->st_nlink);

    printf("Ownership: UID=%d GID=%d\n", sb->st_uid, sb->st_gid);

    printf("File size: %d bytes\n", sb->st_size);
    printf("Optimal I/O block size: %d bytes\n", sb->st_blksize);
    printf("512B blocks allocated: %d\n", sb->st_blocks);
    printf("Last file access: %s", ctime(&sb->st_atime));
    printf("Last file modification: %s", ctime(&sb->st_mtime));
    printf("Last status change: %s", ctime(&sb->st_ctime));
}

//This function uses the stat system call to read data into a variable which is passed to displayStats to print the data.
void stat_file(char filename[])
{
    struct stat sb;
    if (stat(filename, &sb) == -1)
    {
        printf("\nError while getting stat file \n");
        exit(0);
    }
    displayStats(filename, &sb);
}