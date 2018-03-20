//
// Created by radekkoziol on 18.03.18.
//

#if defined(__linux__) || defined(__MINT__)
# define _GNU_SOURCE /* strptime(), getsubopt() */
#endif

#include <time.h>
#include <locale.h>
#include "library/dir_sys.c"
#include "library/date.c"
#include "library/dir_nftw.c"


int
main(int argc, char **argv) {

    char *buf = "Tue 10/30/2001 10:59:10 AM";
    time_t t;
    struct tm result;

    setlocale(LC_ALL, "/QSYS.LIB/EN_US.LOCALE");
    t = time(NULL);

    if (strptime(buf, "%a %m/%d/%Y %r", &result) == NULL)
        printf("\nstrptime failed\n");

    char *buf1 = "Tue 10/30/2001 10:59:10 AM";
    time_t t1;
    struct tm result1;


    if (strptime(buf1, "%a %m/%d/%Y %r", &result1) == NULL)
        printf("\nstrptime failed\n");

    time_t t3 = mktime(&result);
    time_t t2 = mktime(&result1);



    t1= mktime(&result);

    char path[256] = "../test_dir";

//    list_files(path, is_later, t1);

    list_files_nftw(path, is_later, t1);

    return 0;
}
