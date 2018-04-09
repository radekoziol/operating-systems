cmake_minimum_required(VERSION 3.9)
project(untitled C)

set(CMAKE_C_STANDARD 99)

add_library(lib ex1/main.c ex2/main.c)

add_executable(main1 ex1/main.c)

add_executable(main2 ex2/main.c)