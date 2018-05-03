cmake_minimum_required(VERSION 3.10)
project(inter_processes_communication C)

set(CMAKE_C_STANDARD 99)

add_library(inter_processes_communication library/system_v/server.c library/system_v/client.c library/system_v/utils.c
        library/posix/server.c library/posix/client.c library/posix/utils.c library/posix/posix.h
        library/utils.c)

add_executable(server library/posix/server.c)

add_executable(utils library/system_v/utils.c)