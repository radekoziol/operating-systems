cmake_minimum_required(VERSION 3.10)
project(piepelines C)

set(CMAKE_C_STANDARD 99)

add_library(piepelines ex1/main.c ex1/library/utils.c ex2/main.c ex2/master.c ex2/slave.c)

add_executable( main1 ex1/main.c)

add_executable( main2 ex2/main.c)