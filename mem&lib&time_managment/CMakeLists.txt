cmake_minimum_required(VERSION 3.9)
project(mem_lib_time_managment C)

set(CMAKE_C_STANDARD 99)

include_directories(test (ex 2))
include_directories(library (ex 1))

add_executable(main main.c)

# list of source files
set(mem_lib_time_managment main.c  "library (ex 1)/block_arrays_dynamically.h" "library (ex 1)/block_arrays_dynamically.c"
        "library (ex 1)/block_arrays_statically.c" "library (ex 1)/block_arrays_dynamically.h"
        "test (ex 2)/dynamic_arrays_test.c" "test (ex 2)/static_arrays_test.c"
        "test (ex 2)/static_arrays_test.h" "test (ex 2)/dynamic_arrays_test.h"
        "test (ex 2)/random.c" "test (ex 2)/test.c" "test (ex 2)/test.h"
        "test (ex 2)/random.c" "test (ex 2)/random.h")

# this is the "object library" target: compiles the sources only once
add_library(objlib OBJECT ${mem_lib_time_managment})

# shared libraries need PIC
set_property(TARGET ${objlib} PROPERTY POSITION_INDEPENDENT_CODE 1)

# shared and static libraries built from the same object files
add_library(MyLib_shared SHARED $<TARGET_OBJECTS:objlib>)
add_library(MyLib_static STATIC $<TARGET_OBJECTS:objlib>)



