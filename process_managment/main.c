//
// Created by radekkoziol on 18.03.18.
//

#if defined(__linux__) || defined(__MINT__)
# define _GNU_SOURCE /* strptime(), getsubopt() */
#endif

#include <wait.h>
#include <bits/types/FILE.h>
#include <zconf.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void
parse_line(FILE *f, char *command, char *args){

    char file [256];

    int i;
    for (i = 0; i < 256; i++) {
        file[i] = command[i] = args[i] = NULL;
    }

    fscanf(f, "%[^\n]", file);


    i = 0;
    while ((file[i] != ' ') && (i < 256)) {
        command[i] = file[i];
        i++;
    }
    command[i] = NULL;

    i++;
    int l = 0;

    while ((i < 256) && (file[i] != NULL)) {
        args[l++] = file[i++];
    }
    args[i] = NULL;

}



int
main(int argc, char **argv) {

    FILE *f;
    f = fopen("../file.txt", "r");

    if (f == NULL) {
        printf("Error while opening file!");
        exit(-1);
    }

    char file[256];
    char command[256];
    char args[256];

    bool beg_char = true;

    while (getc(f) != EOF){

        if(beg_char)
            fseek(f,-1,SEEK_CUR);


        parse_line(f,command,args);

        pid_t child_pid;
        int status = 0;

        child_pid = vfork();

        if( 0 == child_pid ){
            execlp(command, command, args, (char *) NULL);
            _exit(127); /* terminate the child  */
        }

        // this way, the father waits for all the child processes
        while ( wait(&status) > 0);

        beg_char = false;

    }

    fclose(f);





//    if ((argc == 1) || strcmp(argv[1], "-help") == 0) {
//        printf("Arguments are: \n"
//                       "   path condition date (how)\n");
//        printf("Description: \n");
//        printf(" Possible conditions: \n"
//                       "  '>' modified later than <date> \n"
//                       "  '=' modified at the same <date> \n"
//                       "  '<' modified earlier than <date> \n");
//        printf(" Path must be in format day mm//dd/yy hh:mm:ss AM/PM "
//                       "f.e 'Tue 10/30/2001 10:59:10 AM'\n");
//        printf(" <how = 'sys'> (default) uses methods like opendir, ..\n"
//                       " <how = 'nftw' uses method nftw\n");
//        exit(0);
//    }
//    if (argc < 3) {
//        printf("You did not input enough arguments!\nFor more information write -help\n");
//        exit(0);
//    }
//
//    time_t input_date = parse_date(argv[3]);
//
//    char condition = argv[2][0];
//
//    switch (condition) {
//        case '>':
//            list_files
//                    (argv[1], is_later, input_date);
//        case '<':
//            list_files
//                    (argv[1], is_earlier, input_date);
//        case '=':
//            list_files
//                    (argv[1], is_equal, input_date);
//
//        default:
//            break;
//    }


    return 0;
}
