cmake_minimum_required(VERSION 3.10)
project(semaphores C)

add_library(semaphores_posix  library/posix/main.h
        library/posix/client.c library/posix/server.c library/posix/utils.c)
add_library(semaphores_system_v library/system_v/main.h
        library/system_v/client.c library/system_v/server.c library/system_v/utils.c)


set(CMAKE_C_STANDARD 99)

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -s -O3 -I C:/Users/Shiro/Desktop/asio-1.10.6/include")
#set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${GCC_COVERAGE_LINK_FLAGS} -static")
link_libraries(-pthread -lrt)


add_executable(posix_server library/posix/server.c)
add_executable(posix_client library/posix/client.c)

add_executable(system_v_server library/system_v/server.c)
add_executable(system_v_client library/system_v/client.c)


