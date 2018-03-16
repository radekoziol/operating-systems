//
// Created by radekkoziol on 13.03.18.
//


#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>



char get_random_char(){
    return (char) ('A' + (random() % 26));
}


char ** generate_array(unsigned int record_num, unsigned int record_length ){

    char **records = calloc(record_num, sizeof(char*));
    if(!records) return NULL;

    for(int i = 0; i < record_num; i++) {
        records[i] = calloc(record_length, sizeof(char));
    }

    for(int i = 0; i < record_num; i++){
        for(int j = 0; j < record_length; j++){
            records[i][j] = get_random_char();
        }
    }

    return records;


}




void generate(char *path, unsigned int record_num, unsigned int record_length) {

    char **records;

    records = generate_array(record_num, record_length);

    FILE *f = fopen(path, "w");

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


