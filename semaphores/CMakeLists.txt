cmake_minimum_required(VERSION 3.10)
project(semaphores C)

add_library(semaphores library/posix/main.h library/posix/main.c library/system_v/main.c)

set(CMAKE_C_STANDARD 99)

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -s -O3 -I C:/Users/Shiro/Desktop/asio-1.10.6/include")
#set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${GCC_COVERAGE_LINK_FLAGS} -static")
link_libraries(-pthread -lrt)


set(SOURCE_FILES library/posix/main.c)
add_executable(posix ${SOURCE_FILES})

