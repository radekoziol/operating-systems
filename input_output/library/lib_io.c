#include <stdio.h>
#include <stdlib.h>
#include "utils.c"

void hello() {

//    char file_name [20];
    unsigned int record_length = 10 ;
    unsigned int record_num = 10;
    char records [record_num][record_length];

    generate_array(record_num, record_length, records);

    FILE *f = fopen("../file.txt", "w");

    if (f == NULL)
    {
        printf("Error opening file!\n");
        exit(1);
    }


    for(int i = 0; i < record_num; i++) {
        fprintf(f, "Block : ");
        fwrite(records[i] , sizeof(char),record_length , f );
        fprintf(f, "\n");
    }

    fclose(f);
//
//
//    char * pathname = "../file.txt";
//    int we, wy;
//
//    size_t liczyt;
//
//    we=open(pathname, O_RDONLY);
//    wy=open(pathname,O_WRONLY|O_CREAT,S_IRUSR|S_IWUSR);
//
//    for(int i = 0; i < record_num; i++) {
//        while ((liczyt = read(we, records[i], sizeof(records[i]))) > 0)
//            write(wy, records[i], (size_t) liczyt);
//    }



}
