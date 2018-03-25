//
// Created by radekkoziol on 19.03.18.
//

#define _XOPEN_SOURCE 700

#define _LARGEFILE64_SOURCE
#define _FILE_OFFSET_BITS 64

#include <stdlib.h>
#include <unistd.h>
#include <ftw.h>
#include <stdio.h>
#include <errno.h>
#include <time.h>
#include <zconf.h>
#include <stdbool.h>

#ifndef USE_FDS
#define USE_FDS 15
#endif

bool (*fun)(time_t*);
time_t *arg;

int print_file_info_nftw(const char *fpath, const struct stat *sb, int tflag, struct FTW *ftwbuf) {

    stat(fpath, sb);

    // Preparing arguments for condition
    time_t * date = calloc(2, sizeof(time_t));
    // Current time modification here
    date[0] = (*sb).st_mtime;
    // Given input
    date[1] = *arg;
    if(!fun(date))
        return 0;

    // Finding absolute path
    char actual_path[PATH_MAX + 1];
    char *ab_path = realpath(fpath, actual_path);

    struct stat fileStat;
    if (stat(fpath, &fileStat) < 0)
        return -1;

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


    return 0;           /* To tell nftw() to continue */

}


int print_directory_tree(const char *const dirpath) {
    int result;

    /* Invalid directory path? */
    if (dirpath == NULL || *dirpath == '\0')
        return errno = EINVAL;

    result = nftw(dirpath, print_file_info_nftw, FTW_D, FTW_PHYS);
    if (result >= 0)
        errno = result;

    return errno;
}

void list_files_nftw(char * path, bool (*f)(time_t*), time_t date ) {

    arg = &date;
    fun = f;

    print_directory_tree(path);

}