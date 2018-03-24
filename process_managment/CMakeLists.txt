cmake_minimum_required(VERSION 3.9)
project(directories C)

set(CMAKE_C_STANDARD 99)

add_library(directories main.c library/dir_sys.c library/date.c )

add_executable(main main.c)