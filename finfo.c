/******************************************************************************************************************
* @file finfo.c
* @brief System Calls
*
* Course: CPE2600
* Section: 111
* Assignment: CPE Lab 9
* Author: Reagan Burkemper
*
* Description: displays the file information about a given file provided via the command line. The file name
*              MUST be specified via the command line. Specifically, - The type of file - print this in a user 
*              readable way - The permissions set on the file - print these in a user readable way - The owner
*              of the file - printing the user identifier (number) is enough - The size of the file IN BYTES - 
*              The date and time of last modification (format this for easy viewing, do NOT print out raw bytes 
*              or a large integer). - If at any point, there is an error print an error and exit
* Date: 11/15/2024
*
* Compile Instructions: 
*   To compile the fino.c, run:
*   - compile with: 
*       - make clean
*       - make
*   - run: ./finfo <file_path>
*   
*****************************************************************************************************************/

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>

void print_file_type(mode_t mode) {
    if (S_ISREG(mode)) {
        printf("File Type: Regular file\n");
    } else if (S_ISDIR(mode)) {
        printf("File Type: Directory\n");
    } else if (S_ISCHR(mode)) {
        printf("File Type: Character device\n");
    } else if (S_ISBLK(mode)) {
        printf("File Type: Block device\n");
    } else if (S_ISFIFO(mode)) {
        printf("File Type: FIFO/pipe\n");
    } else if (S_ISLNK(mode)) {
        printf("File Type: Symlink\n");
    } else if (S_ISSOCK(mode)) {
        printf("File Type: Socket\n");
    } else {
        printf("File Type: Unknown\n");
    }
}

void print_permissions(mode_t mode) {
    printf("Permissions: ");
    //check and print:
    printf((mode & S_IRUSR) ? "r" : "-"); //owner read permission
    printf((mode & S_IWUSR) ? "w" : "-"); //owner write permission
    printf((mode & S_IXUSR) ? "x" : "-"); //owner execute permission
    printf((mode & S_IRGRP) ? "r" : "-"); //group read permission
    printf((mode & S_IWGRP) ? "w" : "-"); //group write permission
    printf((mode & S_IXGRP) ? "x" : "-"); //group execute permission
    printf((mode & S_IROTH) ? "r" : "-"); //world read permission
    printf((mode & S_IWOTH) ? "w" : "-"); //world write permission
    printf((mode & S_IXOTH) ? "x" : "-"); //world execute permission
    printf("\n"); // newline character at the end
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Error. Use this format: %s <file_path>\n", argv[0]);
        return 1;
    }

    struct stat fileStat;
    if (stat(argv[1], &fileStat) == -1) {
        perror("stat");
        return 1;
    }

    print_file_type(fileStat.st_mode); //print file type
    print_permissions(fileStat.st_mode); //print permissions
    printf("Owner UID: %d\n", fileStat.st_uid); //print owner
    printf("File size: %ld bytes\n", fileStat.st_size); //print size

    //print last modification time
    char timebuf[80];
    struct tm *timeinfo = localtime(&fileStat.st_mtime);
    strftime(timebuf, sizeof(timebuf), "%Y-%m-%d %H:%M:%S", timeinfo);
    printf("Last modification: %s\n", timebuf);

    return 0;
}