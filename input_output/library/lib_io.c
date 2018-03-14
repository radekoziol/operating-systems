#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <zconf.h>
#include <string.h>
#include "utils.c"


void generate(char *path, unsigned int record_num, unsigned int record_length){

    char ** records;

    records = generate_array(record_num, record_length);

    FILE *f = fopen(path, "w");

    if (f == NULL)
    {
        printf("Error opening file!\n");
        exit(1);
    }

    for(int i = 0; i < record_num; i++) {
        fwrite(records[i] , sizeof(char),record_length , f );
        fprintf(f, "\n");
    }

    fclose(f);

    free(records);

}




void hello() {

//    char file_name [20];
    unsigned int record_length = 10 ;
    unsigned int record_num = 10;

    char pathname [100] = "../file.txt";

    generate(pathname,record_num,record_length);

    sort(pathname, record_num, record_length);





}
