cmake_minimum_required(VERSION 3.9)
project(directories C)

set(CMAKE_C_STANDARD 99)

add_library(directories main.c library/utils.c library/time_m.c)

add_executable(main main.c)