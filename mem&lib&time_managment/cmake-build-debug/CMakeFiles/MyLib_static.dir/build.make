# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.9

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /home/radekkoziol/IDE/clion-2017.3.3/bin/cmake/bin/cmake

# The command to remove a file.
RM = /home/radekkoziol/IDE/clion-2017.3.3/bin/cmake/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "/home/radekkoziol/Projects/CLionProjects/Operating systems/mem&lib&time_managment"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/home/radekkoziol/Projects/CLionProjects/Operating systems/mem&lib&time_managment/cmake-build-debug"

# Include any dependencies generated for this target.
include CMakeFiles/MyLib_static.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/MyLib_static.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/MyLib_static.dir/flags.make

# Object files for target MyLib_static
MyLib_static_OBJECTS =

# External object files for target MyLib_static
MyLib_static_EXTERNAL_OBJECTS = \
"/home/radekkoziol/Projects/CLionProjects/Operating systems/mem&lib&time_managment/cmake-build-debug/CMakeFiles/objlib.dir/main.c.o" \
"/home/radekkoziol/Projects/CLionProjects/Operating systems/mem&lib&time_managment/cmake-build-debug/CMakeFiles/objlib.dir/library_(ex_1)/block_arrays_dynamically.c.o" \
"/home/radekkoziol/Projects/CLionProjects/Operating systems/mem&lib&time_managment/cmake-build-debug/CMakeFiles/objlib.dir/library_(ex_1)/block_arrays_statically.c.o" \
"/home/radekkoziol/Projects/CLionProjects/Operating systems/mem&lib&time_managment/cmake-build-debug/CMakeFiles/objlib.dir/test_(ex_2)/dynamic_arrays_test.c.o" \
"/home/radekkoziol/Projects/CLionProjects/Operating systems/mem&lib&time_managment/cmake-build-debug/CMakeFiles/objlib.dir/test_(ex_2)/static_arrays_test.c.o" \
"/home/radekkoziol/Projects/CLionProjects/Operating systems/mem&lib&time_managment/cmake-build-debug/CMakeFiles/objlib.dir/test_(ex_2)/random.c.o" \
"/home/radekkoziol/Projects/CLionProjects/Operating systems/mem&lib&time_managment/cmake-build-debug/CMakeFiles/objlib.dir/test_(ex_2)/test.c.o"

libMyLib_static.a: CMakeFiles/objlib.dir/main.c.o
libMyLib_static.a: CMakeFiles/objlib.dir/library_(ex_1)/block_arrays_dynamically.c.o
libMyLib_static.a: CMakeFiles/objlib.dir/library_(ex_1)/block_arrays_statically.c.o
libMyLib_static.a: CMakeFiles/objlib.dir/test_(ex_2)/dynamic_arrays_test.c.o
libMyLib_static.a: CMakeFiles/objlib.dir/test_(ex_2)/static_arrays_test.c.o
libMyLib_static.a: CMakeFiles/objlib.dir/test_(ex_2)/random.c.o
libMyLib_static.a: CMakeFiles/objlib.dir/test_(ex_2)/test.c.o
libMyLib_static.a: CMakeFiles/MyLib_static.dir/build.make
libMyLib_static.a: CMakeFiles/MyLib_static.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/home/radekkoziol/Projects/CLionProjects/Operating systems/mem&lib&time_managment/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Linking C static library libMyLib_static.a"
	$(CMAKE_COMMAND) -P CMakeFiles/MyLib_static.dir/cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/MyLib_static.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/MyLib_static.dir/build: libMyLib_static.a

.PHONY : CMakeFiles/MyLib_static.dir/build

CMakeFiles/MyLib_static.dir/requires:

.PHONY : CMakeFiles/MyLib_static.dir/requires

CMakeFiles/MyLib_static.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/MyLib_static.dir/cmake_clean.cmake
.PHONY : CMakeFiles/MyLib_static.dir/clean

CMakeFiles/MyLib_static.dir/depend:
	cd "/home/radekkoziol/Projects/CLionProjects/Operating systems/mem&lib&time_managment/cmake-build-debug" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/home/radekkoziol/Projects/CLionProjects/Operating systems/mem&lib&time_managment" "/home/radekkoziol/Projects/CLionProjects/Operating systems/mem&lib&time_managment" "/home/radekkoziol/Projects/CLionProjects/Operating systems/mem&lib&time_managment/cmake-build-debug" "/home/radekkoziol/Projects/CLionProjects/Operating systems/mem&lib&time_managment/cmake-build-debug" "/home/radekkoziol/Projects/CLionProjects/Operating systems/mem&lib&time_managment/cmake-build-debug/CMakeFiles/MyLib_static.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/MyLib_static.dir/depend

