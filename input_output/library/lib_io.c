#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool sorted_lib(unsigned int length, const char string1[length], const char string2[length]) {

    for (int i = 0; i < length; i++) {
        if (string1[i] < string2[i])
            return true;
        else if (string1[i] > string2[i])
            return false;
    }
    // Are equal
    return true;
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
            if (!sorted_lib(record_length, blocks[1], blocks[0])) {

                fseek(f, j *string_l , SEEK_SET);
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
void copy_lib(char *from, char *to, size_t file_size) {


    FILE *f1 = fopen(from, "r");
    FILE *f2 = fopen(to, "w");

    if ((f1 == NULL) || (f2 == NULL)) {
        printf("Error opening file!\n");
        exit(1);
    }

    char copy[file_size];

    fread(copy, file_size, 1, f1);

    fwrite(copy, sizeof(char), file_size, f2);

    fclose(f1);
    fclose(f2);

}

