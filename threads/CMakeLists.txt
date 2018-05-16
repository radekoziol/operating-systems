cmake_minimum_required(VERSION 3.10)
project(threads C)

set(CMAKE_C_STANDARD 99)

add_library(threads main.c main.h utils.c)

link_libraries( -lpthread -pthread)
add_executable(main main.c)