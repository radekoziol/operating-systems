cmake_minimum_required(VERSION 3.10)
project(inter_processes_communication C)

set(CMAKE_C_STANDARD 99)

add_library(inter_processes_communication server.c client.c utils.c)

add_executable(server server.c )