cmake_minimum_required(VERSION 3.9)
project(input_output C)

set(CMAKE_C_STANDARD 99)

add_library(input_output library/lib_io.c library/sys_io.c library/utils.c library/utils.h)

add_executable(main main.c)