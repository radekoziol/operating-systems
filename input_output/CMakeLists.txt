cmake_minimum_required(VERSION 3.9)
project(input_output C)

set(CMAKE_C_STANDARD 99)

add_library(input_output library/lib_io.c library/lib_io.h
        library/sys_io.c library/sys_io.h
        test/utils.c test/utils.h
        test/test.c test/test.h test/lib_test.c test/lib_test.h
        test/sys_test.c test/lib_test.h)

add_executable(main main.c)