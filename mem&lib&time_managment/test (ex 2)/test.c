//
// Created by radekkoziol on 11.03.18.
//

#include <malloc.h>
#include <time.h>
#include "dynamic_arrays_test.c"
#include <stdarg.h>
#include "static_arrays_test.c"
#include <sys/time.h>
#include <sys/resource.h>


double * run_time_test(void (*f)()){

    struct rusage usage;
    struct timeval user_start, user_end, system_start, system_end;

    getrusage(RUSAGE_SELF, &usage);
    user_start = usage.ru_utime;
    system_start = usage.ru_stime;
    clock_t begin = clock();

    f();

    getrusage(RUSAGE_SELF, &usage);
    user_end = usage.ru_utime;
    system_end = usage.ru_stime;
    clock_t end = clock();
    double real_time_m = (double)(end - begin) / CLOCKS_PER_SEC;

    char real_time[10];
    snprintf(real_time, 10, "%f", real_time_m);

    char * system_time = parse_to_string(system_start,system_end);

    char * user_time = parse_to_string(user_start,user_end);

    double * result = calloc(3, sizeof(double));
    result[0] = real_time_m;
    result[1] = atof(system_time);
    result[2] = atof(user_time);

    return result;

}

void print_average_time(int test_number, double results [9][3]) {

    printf("After %d tests, the results are:\n\n", test_number);

    printf("Creating array dynamically time measurement \n");
    printf("Real time : ");
    printf("%f", results[0][0]/test_number);
    printf("\n");
    printf("User time : ");
    printf("%f", results[0][1]/test_number);
    printf("\n");
    printf("System time : ");
    printf("%f", results[0][2]/test_number);
    printf("\n\n");

    printf("Adding blocks dynamically array time measurement \n");
    printf("Real time : ");
    printf("%f", results[1][0]/test_number);
    printf("\n");
    printf("User time : ");
    printf("%f", results[1][1]/test_number);
    printf("\n");
    printf("System time : ");
    printf("%f", results[1][2]/test_number);
    printf("\n\n");

    printf("Adding blocks statically time measurement \n");
    printf("Real time : ");
    printf("%f", results[2][0]/test_number);
    printf("\n");
    printf("User time : ");
    printf("%f", results[2][1]/test_number);
    printf("\n");
    printf("System time : ");
    printf("%f", results[2][2]/test_number);
    printf("\n\n");

    printf("Deleting blocks dynamically array time measurement \n");
    printf("Real time : ");
    printf("%f", results[3][0]/test_number);
    printf("\n");
    printf("User time : ");
    printf("%f", results[3][1]/test_number);
    printf("\n");
    printf("System time : ");
    printf("%f", results[3][2]/test_number);
    printf("\n\n");

    printf("Deleting blocks statically array time measurement \n");
    printf("Real time : ");
    printf("%f", results[4][0]/test_number);
    printf("\n");
    printf("User time : ");
    printf("%f", results[4][1]/test_number);
    printf("\n");
    printf("System time : ");
    printf("%f", results[4][2]/test_number);
    printf("\n\n");

    printf("Finding (dynamic array) closet sum to given argument time measurement \n");
    printf("Real time : ");
    printf("%f", results[5][0]/test_number);
    printf("\n");
    printf("User time : ");
    printf("%f", results[5][1]/test_number);
    printf("\n");
    printf("System time : ");
    printf("%f", results[5][2]/test_number);
    printf("\n\n");

    printf("Finding (static array) closet sum to given argument time measurement \n");
    printf("Real time : ");
    printf("%f", results[6][0]/test_number);
    printf("\n");
    printf("User time : ");
    printf("%f", results[6][1]/test_number);
    printf("\n");
    printf("System time : ");
    printf("%f", results[6][2]/test_number);
    printf("\n\n");

    printf("Adding, deleting and adding again blocks (dynamic array) time measurement \n");
    printf("Real time : ");
    printf("%f", results[7][0]/test_number);
    printf("\n");
    printf("User time : ");
    printf("%f", results[7][1]/test_number);
    printf("\n");
    printf("System time : ");
    printf("%f", results[7][2]/test_number);
    printf("\n\n");

    printf("Adding, deleting and adding again blocks (static array) time measurement \n");
    printf("Real time : ");
    printf("%f", results[8][0]/test_number);
    printf("\n");
    printf("User time : ");
    printf("%f", results[8][1]/test_number);
    printf("\n");
    printf("System time : ");
    printf("%f", results[8][2]/test_number);
    printf("\n\n");


}



void test(){

    /*
       Jako argumenty przekaż liczbę elementów tablicy, rozmiar bloku, sposób alokacji
        pamięci oraz spis wykonywanych operacji. Zakładamy, że możliwe jest zlecenie
        trzech operacji (np. stworzenie tablicy, wyszukanie elementu oraz usunięcie i
        dodanie zadanej liczby bloków albo stworzenie tablicy, usunięcie i dodanie zadanej
        liczby bloków i naprzemienne usunięcie i dodanie zadanej liczby bloków).
     */

    unsigned int array_size = 1000;
    unsigned int block_size = 10;
    // static = 's' or dynamic = 'd'
    char allocation = 's';
    /*
     * Possible input :
     * 'c' = create array (with blocks)
     * 'b' = finding block
     * 'd' = delete blocks and then add them again
     */
    char operations [3] = {'c','b','d'};

    int test_number = 1000;
    double results [9][3];

    int i,j;
    for(i = 0; i < 9; i++) {
        for (j = 0; j < 3; j++) {
            results[i][j] = 0.0;
        }
    }

    for(i = 0; i < test_number; i++) {


        //"Creating array dynamically time measurement"
        double * result = run_time_test(create_array_d_test);
        for(j = 0; j < 3; j++){
            results[0][j] += result[j];
        }


        //"Adding blocks dynamically array time measurement"
        result = run_time_test(add_blocks_d_test);

        for(j = 0; j < 3; j++){
            results[1][j] += result[j];
        }

        //"Adding blocks  statically time measurement"
        result = run_time_test(add_blocks_s_test);

        for(j = 0; j < 3; j++){
            results[2][j] += result[j];
        }

        //"Deleting blocks dynamically array time measurement"
        result = run_time_test(delete_blocks_d_test);

        for(j = 0; j < 3; j++){
            results[3][j] += result[j];
        }

        //"Deleting blocks statically array time measurement"
        result = run_time_test(delete_blocks_s_test);

        for(j = 0; j < 3; j++){
            results[4][j] += result[j];
        }

        //"Finding (dynamic array) closet sum to given argument time measurement"
        result = run_time_test(closest_block_sum_to_d_test);

        for(j = 0; j < 3; j++){
            results[5][j] += result[j];
        }

        //"Finding (static array) closet sum to given argument time measurement"
        result = run_time_test(closest_block_sum_to_s_test);

        for(j = 0; j < 3; j++){
            results[6][j] += result[j];
        }

        //"Adding, deleting and adding again blocks (dynamic array) time measurement"
        result = run_time_test(re_adding_to_array_d_test);

        for(j = 0; j < 3; j++){
            results[7][j] += result[j];
        }

        //"Adding, deleting and adding again blocks (static array) time measurement"
        result = run_time_test(re_adding_to_array_s_test);

        for(j = 0; j < 3; j++){
            results[8][j] += result[j];
        }
    }

    print_average_time(test_number, results);



    /*
     * W programie zmierz, wypisz na konsolę i zapisz  do pliku
     * z raportem  czasy realizacji podstawowych operacji:
-       stworzenie tablicy z zadaną liczbą bloków o zdanym rozmiarze i
     przy pomocy wybranej funkcji alokującej,
-    wyszukanie najbardziej podobnego elementu z punktu widzenia
     sumy znaków do elementu zadanego jako argument
-   usunięcie kolejno zadanej liczby bloków a następnie dodanie
     na ich miejsce nowych bloków
-   na przemian usunięcie i dodanie zadanej liczby bloków
     */

}
