//
// Created by radekkoziol on 19.03.18.
//

#if defined(__linux__) || defined(__MINT__)
# define _GNU_SOURCE /* strptime(), getsubopt() */
#endif



#include <stdbool.h>
#include <bits/types/time_t.h>
#include <time.h>
#include <locale.h>
#include <stdio.h>

bool is_later(time_t* time){
    return difftime(time[0],time[1]) > 0;
}
bool is_earlier(time_t* time){
    return difftime(time[0],time[1]) < 0;
}
bool is_equal(time_t* time){
    return difftime(time[0],time[1]) == 0;
}

time_t parse_date(char * date){

    time_t t,t1;
    struct tm result;

    setlocale(LC_ALL, "/QSYS.LIB/EN_US.LOCALE");
    t = time(NULL);

    if (strptime(date, "%a %m/%d/%Y %r", &result) == NULL)
        printf("\nstrptime failed\n");

    t1= mktime(&result);

    return t1;

}