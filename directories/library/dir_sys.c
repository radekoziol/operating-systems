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

time_t* get_args(time_t time1, time_t time2){

    time_t * time = calloc(2, sizeof(time_t));
    time[0] = time1;
    time[1] = time2;

    return time;
}


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


void list_directories(char *path, bool (*f)(time_t*), time_t arg) {

    DIR *dir = opendir(path);
    struct dirent *dirent;
    struct stat file;

    strcat(path, "/");

    while (dir != NULL) {

        errno = 0;
        if (((dirent = readdir(dir)) != NULL) &&
                ( strcmp(dirent->d_name,".") != 0) &&
                ( strcmp(dirent->d_name,"..") != 0)){

            char *temp_path = calloc(256, sizeof(char));

            strcpy(temp_path, path);

            strcat(temp_path, dirent->d_name);

            if(!S_ISLNK(file.st_mode)) {

                stat(temp_path, &file);

                if(f(get_args(file.st_mtime, arg)))
                    print_file_info(temp_path);

                if(is_directory(temp_path)) {
                    list_directories(temp_path,f,arg);
                }

            }
        } else {
            if (errno == 0) {
                closedir(dir);
                return;
            }
        }
    }
}
