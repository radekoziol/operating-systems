cmake_minimum_required(VERSION 3.10)
project(threads C)

set(CMAKE_C_STANDARD 99)

add_library(threads main/main.c main/main.h library/utils.c library/filter.c)

link_libraries( -lpthread -pthread -lm)
add_executable(main main/main.c)