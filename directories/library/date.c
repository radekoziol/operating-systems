//
// Created by radekkoziol on 19.03.18.
//



#include <stdbool.h>
#include <bits/types/time_t.h>
#include <time.h>

bool is_later(time_t* time){
    return difftime(time[0],time[1]) > 0;
}
bool is_earlier(time_t* time){
    return difftime(time[0],time[1]) < 0;
}
bool is_equal(time_t* time){
    return difftime(time[0],time[1]) == 0;
}
