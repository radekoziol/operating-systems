cmake_minimum_required(VERSION 3.10)
project(inter_processes_communication C)

set(CMAKE_C_STANDARD 99)

add_library(inter_processes_communication system_v/server.c system_v/client.c system_v/utils.c)

add_executable(server system_v/server.c)

add_executable(utils system_v/utils.c)