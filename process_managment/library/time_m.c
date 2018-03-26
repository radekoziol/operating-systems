//
// Created by radekkoziol on 11.03.18.
//

#include <malloc.h>
#include <time.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <stdlib.h>
#include <string.h>

double
parse_to_double(struct timeval end){

    __time_t sec_diff = end.tv_sec;
    __suseconds_t usec_diff = end.tv_usec;

    static char array1[10];
    char array2[10];
    char dot [2] = ".";

    sprintf(array1, "%ld", sec_diff);
    sprintf(array2, "%ld", usec_diff);

    strcat(array1,dot);
    strcat(array1,array2);


    return strtod(array1,NULL);
}

double * measure_time(){

    struct rusage usage;
    struct timeval user_end, system_end;

    getrusage(RUSAGE_CHILDREN, &usage);
    user_end = usage.ru_utime;
    system_end = usage.ru_stime;

    double system_time = parse_to_double(system_end);

    double user_time = parse_to_double(user_end);

    double * result = calloc(3, sizeof(double));
    result[0] = user_time;
    result[1] = system_time;

    return result;
}
        void
print_results(double *results) {

    printf("User time : ");
    printf("%f", results[0]);
    printf("\n");
    printf("System time : ");
    printf("%f", results[1]);
    printf("\n\n");

}

