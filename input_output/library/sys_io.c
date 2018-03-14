//
// Created by radekkoziol on 13.03.18.
//
#include <bits/types/FILE.h>
#include <stdio.h>
#include "utils.c"


generate(char *path, unsigned int record_num, unsigned int record_length){

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


}
