//
// Created by radekkoziol on 18.03.18.
//

#include <zconf.h>
#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>
#include <time.h>


/*
 * Prints required file info
 * File can not be linked
 */
void print_file_info(char * path){

    char *sym_link_path = "/home/radekkoziol/Downloads/slides.zip";

    // Finding absolute path
    char actual_path[PATH_MAX + 1];
    char *ab_path= realpath(sym_link_path, actual_path);

    struct stat fileStat;
    if(stat(path,&fileStat) < 0)
        return;

    if(!S_ISLNK(fileStat.st_mode)) {
        printf("Information for %s\n", path);
        printf("---------------------------\n");
        printf("File Size: \t\t%li bytes\n", fileStat.st_size);
        printf("Absolute path \t%s\n", ab_path);
        printf("Last modified time: %s", ctime(&fileStat.st_mtime));
        printf("File Permissions: \t");
        printf((S_ISDIR(fileStat.st_mode)) ? "d" : "-");
        printf((fileStat.st_mode & S_IRUSR) ? "r" : "-");
        printf((fileStat.st_mode & S_IWUSR) ? "w" : "-");
        printf((fileStat.st_mode & S_IXUSR) ? "x" : "-");
        printf((fileStat.st_mode & S_IRGRP) ? "r" : "-");
        printf((fileStat.st_mode & S_IWGRP) ? "w" : "-");
        printf((fileStat.st_mode & S_IXGRP) ? "x" : "-");
        printf((fileStat.st_mode & S_IROTH) ? "r" : "-");
        printf((fileStat.st_mode & S_IWOTH) ? "w" : "-");
        printf((fileStat.st_mode & S_IXOTH) ? "x" : "-");
        printf("\n\n");
    }
}



void hello() {

    char path[256] = "../main.c";

    print_file_info(path);

}