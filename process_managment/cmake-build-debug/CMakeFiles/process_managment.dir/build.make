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
CMAKE_SOURCE_DIR = "/home/radekkoziol/Projects/CLionProjects/Operating systems/process_managment"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/home/radekkoziol/Projects/CLionProjects/Operating systems/process_managment/cmake-build-debug"

# Include any dependencies generated for this target.
include CMakeFiles/process_managment.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/process_managment.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/process_managment.dir/flags.make

CMakeFiles/process_managment.dir/library.c.o: CMakeFiles/process_managment.dir/flags.make
CMakeFiles/process_managment.dir/library.c.o: ../library.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/radekkoziol/Projects/CLionProjects/Operating systems/process_managment/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/process_managment.dir/library.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/process_managment.dir/library.c.o   -c "/home/radekkoziol/Projects/CLionProjects/Operating systems/process_managment/library.c"

CMakeFiles/process_managment.dir/library.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/process_managment.dir/library.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "/home/radekkoziol/Projects/CLionProjects/Operating systems/process_managment/library.c" > CMakeFiles/process_managment.dir/library.c.i

CMakeFiles/process_managment.dir/library.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/process_managment.dir/library.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "/home/radekkoziol/Projects/CLionProjects/Operating systems/process_managment/library.c" -o CMakeFiles/process_managment.dir/library.c.s

CMakeFiles/process_managment.dir/library.c.o.requires:

.PHONY : CMakeFiles/process_managment.dir/library.c.o.requires

CMakeFiles/process_managment.dir/library.c.o.provides: CMakeFiles/process_managment.dir/library.c.o.requires
	$(MAKE) -f CMakeFiles/process_managment.dir/build.make CMakeFiles/process_managment.dir/library.c.o.provides.build
.PHONY : CMakeFiles/process_managment.dir/library.c.o.provides

CMakeFiles/process_managment.dir/library.c.o.provides.build: CMakeFiles/process_managment.dir/library.c.o


# Object files for target process_managment
process_managment_OBJECTS = \
"CMakeFiles/process_managment.dir/library.c.o"

# External object files for target process_managment
process_managment_EXTERNAL_OBJECTS =

libprocess_managment.a: CMakeFiles/process_managment.dir/library.c.o
libprocess_managment.a: CMakeFiles/process_managment.dir/build.make
libprocess_managment.a: CMakeFiles/process_managment.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/home/radekkoziol/Projects/CLionProjects/Operating systems/process_managment/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking C static library libprocess_managment.a"
	$(CMAKE_COMMAND) -P CMakeFiles/process_managment.dir/cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/process_managment.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/process_managment.dir/build: libprocess_managment.a

.PHONY : CMakeFiles/process_managment.dir/build

CMakeFiles/process_managment.dir/requires: CMakeFiles/process_managment.dir/library.c.o.requires

.PHONY : CMakeFiles/process_managment.dir/requires

CMakeFiles/process_managment.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/process_managment.dir/cmake_clean.cmake
.PHONY : CMakeFiles/process_managment.dir/clean

CMakeFiles/process_managment.dir/depend:
	cd "/home/radekkoziol/Projects/CLionProjects/Operating systems/process_managment/cmake-build-debug" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/home/radekkoziol/Projects/CLionProjects/Operating systems/process_managment" "/home/radekkoziol/Projects/CLionProjects/Operating systems/process_managment" "/home/radekkoziol/Projects/CLionProjects/Operating systems/process_managment/cmake-build-debug" "/home/radekkoziol/Projects/CLionProjects/Operating systems/process_managment/cmake-build-debug" "/home/radekkoziol/Projects/CLionProjects/Operating systems/process_managment/cmake-build-debug/CMakeFiles/process_managment.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/process_managment.dir/depend

