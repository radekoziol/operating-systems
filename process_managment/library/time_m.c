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

void
print_results(double *results) {

    printf("User time : ");
    printf("%f", results[0]);
    printf("\n");
    printf("System time : ");
    printf("%f", results[1]);
    printf("\n\n");

}
