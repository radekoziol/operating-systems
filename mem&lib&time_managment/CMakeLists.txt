cmake_minimum_required(VERSION 3.9)
project(mem_lib_time_managment C)

set(CMAKE_C_STANDARD 99)

add_library(mem_lib_time_managment library.h main.c block_arrays_dynamically.c block_arrays_statically.c block.h)

add_executable(main main.c)
