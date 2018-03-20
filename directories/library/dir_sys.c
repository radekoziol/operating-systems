//
// Created by radekkoziol on 18.03.18.
//

#include <zconf.h>
#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <time.h>
#include <errno.h>
#include <string.h>
#include <stdbool.h>

/*
 * Checks if given path is directory
 */
bool is_directory(const char *path) {

    struct stat path_stat;
    stat(path, &path_stat);

    return S_ISDIR(path_stat.st_mode);
}


/*
 * Prints required file info
 */
void print_file_info(char *path) {

    // Finding absolute path
    char actual_path[PATH_MAX + 1];
    char *ab_path = realpath(path, actual_path);

    struct stat fileStat;
    if (stat(path, &fileStat) < 0)
        return;

    printf("%s\n", ab_path);
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
    printf(" %li bytes", fileStat.st_size);
    printf(" %s\n", ctime(&fileStat.st_mtime));


}


/*
 * List directories base on condition (method f)
 */
void list_files(char *path, bool (*f)(time_t*), time_t  arg) {

    // Opening dir, preparing variables
    DIR *dir = opendir(path);
    struct dirent *dirent;
    struct stat file;

    // In order to effectively iterate, lets slash is added to path
    strcat(path, "/");

    while (dir != NULL) {

        errno = 0;
        if (((dirent = readdir(dir)) != NULL) && // If it went ok
                ( strcmp(dirent->d_name,".") != 0) && // Not same directory
                ( strcmp(dirent->d_name,"..") != 0)){ // Not prev directory

            // Creating template to create paths to file
            char *temp_path = calloc(256, sizeof(char));
            strcpy(temp_path, path);

            // Concatenating with current file
            strcat(temp_path, dirent->d_name);

            // If it is not symbolic link
            if(!S_ISLNK(file.st_mode)) {

                stat(temp_path, &file);

                // Preparing arguments for condition
                time_t * date = calloc(2, sizeof(time_t));
                // Current time modification here
                date[0] = file.st_mtime;
                // Given input
                date[1] = arg;

                // Condition
                if(f(date))
                    print_file_info(temp_path);

                // Recursively for next directory
                if(is_directory(temp_path))
                    list_files(temp_path,f,arg);

            }
        } else {
            if (errno == 0) {
                closedir(dir);
                return;
            }
        }
    }
}
