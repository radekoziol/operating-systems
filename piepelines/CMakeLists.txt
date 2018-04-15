cmake_minimum_required(VERSION 3.10)
project(piepelines C)

set(CMAKE_C_STANDARD 99)

add_library(piepelines main.c)

add_executable(main main.c)