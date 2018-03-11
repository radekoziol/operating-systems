cmake_minimum_required(VERSION 3.9)
project(mem_lib_time_managment C)

set(CMAKE_C_STANDARD 99)

include_directories(test (ex 2))
include_directories(library (ex 1))

add_library(mem_lib_time_managment main.c  "library (ex 1)/block_arrays_dynamically.h" "library (ex 1)/block_arrays_dynamically.c"
        "library (ex 1)/block_arrays_statically.c" "library (ex 1)/block_arrays_dynamically.h"
        "test (ex 2)/dynamic_arrays_test.c" "test (ex 2)/static_arrays_test.c"
        "test (ex 2)/random.c")

add_executable(main main.c)

add_executable(test1 "test (ex 2)/test.c")


## Install project namespaced headers
include_directories(include
        ${catkin_INCLUDE_DIRS}
        ${Boost_INCLUDE_DIRS}
        ${GSTREAMER_INCLUDE_DIRS})




