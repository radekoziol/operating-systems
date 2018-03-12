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

void run_time_test(void (*f)(), char message [50] ){


    printf("***********************\n");
    printf(message);
    printf("\n");

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

    printf("Real time : ");
    printf(real_time);
    printf("\n");

    char * user_time = parse_to_string(user_start,user_end);

    int i;

    printf("User time : ");
    for(i = 0; i < 10; i++) {
        if(*(user_time + i) != NULL)
            printf("%c", *(user_time + i));
    }
    printf("\n");

    char * system_time = parse_to_string(system_start,system_end);

    printf("System time : ");
    for(i = 0; i < 10; i++) {
        if(*(user_time + i) != NULL)
            printf("%c", *(system_time + i));
    }
    printf("\n");


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

    run_time_test(create_array_d_test,
                  "Creating array dynamically time measurement");


    run_time_test(add_blocks_d_test,
                  "Adding blocks dynamically array time measurement");

    run_time_test(add_blocks_s_test,
                  "Creating array statically time measurement");

    run_time_test(delete_blocks_d_test,
                  "Deleting blocks dynamically array time measurement");

    run_time_test(delete_blocks_s_test,
                  "Deleting blocks statically array time measurement");

    run_time_test(closest_block_sum_to_d_test,
                  "Finding (dynamic array) closet sum to given argument time measurement");

    run_time_test(closest_block_sum_to_s_test,
                  "Finding (static array) closet sum to given argument time measurement");

    run_time_test(re_adding_to_array_d_test,
                  "Adding, deleting and adding again blocks (dynamic array) time measurement");

    run_time_test(re_adding_to_array_s_test,
                  "Adding, deleting and adding again blocks (static array) time measurement");





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
