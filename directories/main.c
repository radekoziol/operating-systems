//
// Created by radekkoziol on 18.03.18.
//

#if defined(__linux__) || defined(__MINT__)
# define _GNU_SOURCE /* strptime(), getsubopt() */
#endif

#include <time.h>
#include <string.h>
#include "library/date.c"
#include "library/dir_nftw.c"
#include "library/dir_sys.c"


int
main(int argc, char **argv) {


// Example input
//    argc = 4;
//    argv[1] = "../test_dir";
//    argv[2] = ">";
//    argv[3] =  "Tue 10/30/2001 10:59:10 AM";
//    argv[4] = "sys";


    if( (argv[1] == NULL)  || strcmp(argv[1], "-help" ) == 0 ) {
        printf("Arguments are: \n"
                       "   path condition date (how)\n");
        printf("Description: \n");
        printf(" Possible conditions: \n"
                       "  '>' modified later than <date> \n"
                       "  '=' modified at the same <date> \n"
                       "  '<' modified earlier than <date> \n");
        printf(" Path must be in format day mm//dd/yy hh:mm:ss AM/PM "
                       "f.e 'Tue 10/30/2001 10:59:10 AM'\n");
        printf(" <how = 'sys'> (default) uses methods like opendir, ..\n"
                       " <how = 'nftw' uses method nftw\n");
        exit(0);
    }
    if(argc < 3){
        printf("You did not input enough arguments!\nFor more information write -help\n");
        exit(0);
    }

    time_t input_date = parse_date(argv[3]);

    char condition = argv[2][0];

    if(strcmp(argv[4],"nftw") == 0){
        switch (condition){
            case '>':
                list_files_nftw
                        (argv[1],is_later,input_date);
            case '<':
                list_files_nftw
                        (argv[1],is_earlier,input_date);
            case '=':
                list_files_nftw
                        (argv[1],is_equal,input_date);

            default:break;
        }
    }
    else if(strcmp(argv[4],"sys") == 0){
        switch (condition){
            case '>':
                list_files
                        (argv[1],is_later,input_date);
            case '<':
                list_files
                        (argv[1],is_earlier,input_date);
            case '=':
                list_files
                        (argv[1],is_equal,input_date);

            default:break;
        }
    }


    return 0;
}
