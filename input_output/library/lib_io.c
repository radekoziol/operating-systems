#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <zconf.h>
#include <string.h>
#include <stdbool.h>
#include "utils.c"


void generate_lib(char *path, unsigned int record_num, unsigned int record_length) {

    char **records;

    records = generate_array(record_num, record_length);

    FILE *f = fopen(path, "w+");

    if (f == NULL) {
        printf("Error opening file!\n");
        exit(1);
    }

    for (int i = 0; i < record_num; i++) {
        fwrite(records[i], sizeof(char), record_length, f);
        fprintf(f, "\n");
    }

    fclose(f);

    free(records);

}


void sort_lib(char *path, unsigned int record_num, unsigned int record_length) {

    FILE *f = fopen(path, "r+");

    if (f == NULL) {
        printf("Error opening file!\n");
        exit(1);
    }

    unsigned int string_l = (record_length + 1);
    // Only 2 strings will be stored
    char blocks[2][record_length];

    for (int i = 0; i < record_num; i++) {

        // Iterating over each string
        fseek(f, i*string_l, SEEK_SET);

        //Reading
        fread(blocks[0], string_l, 1, f);

        // Setting to beginning of file for next loop
        fseek(f, 0, SEEK_SET);

        // Creating sorted file
        for (int j = 0; j < i; j++) {

            fread(blocks[1], record_length + 1, 1, f);

            // If not sorted swap them
            if (!sorted(record_length, blocks[1], blocks[0])) {

                fseek(f, -string_l , SEEK_CUR);
                fwrite(blocks[0], sizeof(char), record_length , f);

                fseek(f, i*string_l, SEEK_SET);
                fwrite(blocks[1], sizeof(char), record_length , f);


                // We need to need to check again for swapped string
                i--;
                break;
            }
        }


    }

        fclose(f);
}

void copy_lib(char *from, char *to, size_t file_size){


    FILE *f1 = fopen(from, "r");
    FILE *f2 = fopen(from, "w");

    if ((f1 == NULL) || (f2 == NULL) ) {
        printf("Error opening file!\n");
        exit(1);
    }

    char copy[file_size];

    fread(copy, file_size, 1, f1);

    fwrite(copy, sizeof(char), file_size , f2);

    close(f1);
    close(f2);

}

void hello() {

    unsigned int record_length = 10;
    unsigned int record_num = 100;

    char path1[50] = "../file.txt";

    char path2[50] = "../file1.txt";


    generate_lib(path1, record_num, record_length);

    sort_lib(path1, record_num, record_length);

    copy_lib(path1,path2,record_length*record_num);

}
