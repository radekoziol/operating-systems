//
// Created by radekkoziol on 11.03.18.
//

#include <malloc.h>
#include <time.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <stdlib.h>
#include <string.h>
#include "lib_test.c"
#include "sys_test.c"



char * parse_to_string(struct timeval start, struct timeval end){

    __time_t sec_diff = end.tv_sec - start.tv_sec;
    __suseconds_t usec_diff = end.tv_usec - start.tv_usec ;

    static char array1[10];
    char array2[10];
    char dot [2] = ".";

    sprintf(array1, "%ld", sec_diff);
    sprintf(array2, "%ld", usec_diff);

    strcat(array1,dot);
    strcat(array1,array2);


    return array1;
}

double * run_time_test(void (*f)(char*,char*,int,int),
                       char * path1, char * path2, unsigned int record_num ,unsigned int record_length){

    struct rusage usage;
    struct timeval user_start, user_end, system_start, system_end;

    getrusage(RUSAGE_SELF, &usage);
    user_start = usage.ru_utime;
    system_start = usage.ru_stime;
    clock_t begin = clock();

    f(path1,path2,record_num,record_length);

    getrusage(RUSAGE_SELF, &usage);
    user_end = usage.ru_utime;
    system_end = usage.ru_stime;
    clock_t end = clock();
    double real_time_m = (double)(end - begin) / CLOCKS_PER_SEC;

    char * system_time = parse_to_string(system_start,system_end);

    char * user_time = parse_to_string(user_start,user_end);

    double * result = calloc(3, sizeof(double));
    result[0] = real_time_m;
    result[1] = strtod(system_time, NULL);
    result[2] = strtod(user_time, NULL);

    return result;

}

void print_average_time(int test_number, double results [9][3]) {


    printf("After %d tests, the results are:\n\n", test_number);

    printf("Sorting file with system functions time measurement \n");
    printf("Real time : ");
    printf("%f", results[0][0]/test_number);
    printf("\n");
    printf("User time : ");
    printf("%f", results[0][1]/test_number);
    printf("\n");
    printf("System time : ");
    printf("%f", results[0][2]/test_number);
    printf("\n\n");

    printf("Sorting file with library functions time measurement \n");
    printf("Real time : ");
    printf("%f", results[1][0]/test_number);
    printf("\n");
    printf("User time : ");
    printf("%f", results[1][1]/test_number);
    printf("\n");
    printf("System time : ");
    printf("%f", results[1][2]/test_number);
    printf("\n\n");

    printf("Copying file with system functions time measurement \n");
    printf("Real time : ");
    printf("%f", results[2][0]/test_number);
    printf("\n");
    printf("User time : ");
    printf("%f", results[2][1]/test_number);
    printf("\n");
    printf("System time : ");
    printf("%f", results[2][2]/test_number);
    printf("\n\n");

    printf("Copying file with library functions time measurement \n");
    printf("Real time : ");
    printf("%f", results[3][0]/test_number);
    printf("\n");
    printf("User time : ");
    printf("%f", results[3][1]/test_number);
    printf("\n");
    printf("System time : ");
    printf("%f", results[3][2]/test_number);
    printf("\n\n");

}

void test(char * path1, char * path2, unsigned int record_num, unsigned int record_length){

    int test_number = 10;
    double results [4][3];

    int i,j;
    for(i = 0; i < 4; i++)
        for(j = 0; j < 3; j++)
            results[i][j] = 0;


    for(i = 0; i < test_number; i++) {

        generate(path1,record_num,record_length);

//        "Sorting file with system functions time measurement"
        double * result = run_time_test(
                (void (*)(char *, char *, int, int)) sort_sys_test,
                path1, path2, record_num, record_length);
        for(j = 0; j < 3; j++){
            results[0][j] += result[j];
        }

        generate(path1,record_num,record_length);

//        "Sorting file with library functions time measurement"
        result = run_time_test((void (*)(char *, char *, int, int)) sort_lib_test,
                               path1,path2,record_num,record_length);

        for(j = 0; j < 3; j++){
            results[1][j] += result[j];
        }


        //"Copying file with system functions time measurement"
        result = run_time_test((void (*)(char *, char *, int, int)) copy_sys_test,
                               path1,path2,record_num,record_length);

        for(j = 0; j < 3; j++){
            results[2][j] += result[j];
        }


        //"Copying file with library functions time measurement"
        result = run_time_test((void (*)(char *, char *, int, int)) copy_lib_test,
                path1,path2,record_num,record_length);

        for(j = 0; j < 3; j++){
            results[3][j] += result[j];
        }

    }

    print_average_time(test_number, results);

}
