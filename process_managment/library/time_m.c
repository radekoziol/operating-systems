//
// Created by radekkoziol on 11.03.18.
//

#include <malloc.h>
#include <time.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <stdlib.h>
#include <string.h>



double parse_to_double(struct timeval start, struct timeval end){

    __time_t sec_diff = end.tv_sec - start.tv_sec;
    __suseconds_t usec_diff = end.tv_usec - start.tv_usec ;

    static char array1[10];
    char array2[10];
    char dot [2] = ".";

    sprintf(array1, "%ld", sec_diff);
    sprintf(array2, "%ld", usec_diff);

    strcat(array1,dot);
    strcat(array1,array2);


    return strtod(array1,NULL);
}


double * run_time_test(void (*f)(char*,char*,int,int),
        char *command, char *args, int time_limit, int mem_limit){

    struct rusage usage;
    struct timeval user_start, user_end, system_start, system_end;

    getrusage(RUSAGE_SELF, &usage);
    user_start = usage.ru_utime;
    system_start = usage.ru_stime;
    clock_t begin = clock();

    f(command,args,time_limit,mem_limit);

    getrusage(RUSAGE_SELF, &usage);
    user_end = usage.ru_utime;
    system_end = usage.ru_stime;
    clock_t end = clock();

    double real_time_m = (double)(end - begin) / CLOCKS_PER_SEC;

    double system_time = parse_to_double(system_start,system_end);

    double user_time = parse_to_double(user_start,user_end);


    double * result = calloc(3, sizeof(double));
    result[0] = real_time_m;
    result[1] = system_time;
    result[2] = user_time;

    return result;

}
