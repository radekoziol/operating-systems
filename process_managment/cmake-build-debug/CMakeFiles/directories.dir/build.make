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
include CMakeFiles/directories.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/directories.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/directories.dir/flags.make

CMakeFiles/directories.dir/main.c.o: CMakeFiles/directories.dir/flags.make
CMakeFiles/directories.dir/main.c.o: ../main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/radekkoziol/Projects/CLionProjects/Operating systems/process_managment/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/directories.dir/main.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/directories.dir/main.c.o   -c "/home/radekkoziol/Projects/CLionProjects/Operating systems/process_managment/main.c"

CMakeFiles/directories.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/directories.dir/main.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "/home/radekkoziol/Projects/CLionProjects/Operating systems/process_managment/main.c" > CMakeFiles/directories.dir/main.c.i

CMakeFiles/directories.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/directories.dir/main.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "/home/radekkoziol/Projects/CLionProjects/Operating systems/process_managment/main.c" -o CMakeFiles/directories.dir/main.c.s

CMakeFiles/directories.dir/main.c.o.requires:

.PHONY : CMakeFiles/directories.dir/main.c.o.requires

CMakeFiles/directories.dir/main.c.o.provides: CMakeFiles/directories.dir/main.c.o.requires
	$(MAKE) -f CMakeFiles/directories.dir/build.make CMakeFiles/directories.dir/main.c.o.provides.build
.PHONY : CMakeFiles/directories.dir/main.c.o.provides

CMakeFiles/directories.dir/main.c.o.provides.build: CMakeFiles/directories.dir/main.c.o


CMakeFiles/directories.dir/library/dir_sys.c.o: CMakeFiles/directories.dir/flags.make
CMakeFiles/directories.dir/library/dir_sys.c.o: ../library/dir_sys.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/radekkoziol/Projects/CLionProjects/Operating systems/process_managment/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/directories.dir/library/dir_sys.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/directories.dir/library/dir_sys.c.o   -c "/home/radekkoziol/Projects/CLionProjects/Operating systems/process_managment/library/dir_sys.c"

CMakeFiles/directories.dir/library/dir_sys.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/directories.dir/library/dir_sys.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "/home/radekkoziol/Projects/CLionProjects/Operating systems/process_managment/library/dir_sys.c" > CMakeFiles/directories.dir/library/dir_sys.c.i

CMakeFiles/directories.dir/library/dir_sys.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/directories.dir/library/dir_sys.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "/home/radekkoziol/Projects/CLionProjects/Operating systems/process_managment/library/dir_sys.c" -o CMakeFiles/directories.dir/library/dir_sys.c.s

CMakeFiles/directories.dir/library/dir_sys.c.o.requires:

.PHONY : CMakeFiles/directories.dir/library/dir_sys.c.o.requires

CMakeFiles/directories.dir/library/dir_sys.c.o.provides: CMakeFiles/directories.dir/library/dir_sys.c.o.requires
	$(MAKE) -f CMakeFiles/directories.dir/build.make CMakeFiles/directories.dir/library/dir_sys.c.o.provides.build
.PHONY : CMakeFiles/directories.dir/library/dir_sys.c.o.provides

CMakeFiles/directories.dir/library/dir_sys.c.o.provides.build: CMakeFiles/directories.dir/library/dir_sys.c.o


CMakeFiles/directories.dir/library/date.c.o: CMakeFiles/directories.dir/flags.make
CMakeFiles/directories.dir/library/date.c.o: ../library/date.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/radekkoziol/Projects/CLionProjects/Operating systems/process_managment/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/directories.dir/library/date.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/directories.dir/library/date.c.o   -c "/home/radekkoziol/Projects/CLionProjects/Operating systems/process_managment/library/date.c"

CMakeFiles/directories.dir/library/date.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/directories.dir/library/date.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "/home/radekkoziol/Projects/CLionProjects/Operating systems/process_managment/library/date.c" > CMakeFiles/directories.dir/library/date.c.i

CMakeFiles/directories.dir/library/date.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/directories.dir/library/date.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "/home/radekkoziol/Projects/CLionProjects/Operating systems/process_managment/library/date.c" -o CMakeFiles/directories.dir/library/date.c.s

CMakeFiles/directories.dir/library/date.c.o.requires:

.PHONY : CMakeFiles/directories.dir/library/date.c.o.requires

CMakeFiles/directories.dir/library/date.c.o.provides: CMakeFiles/directories.dir/library/date.c.o.requires
	$(MAKE) -f CMakeFiles/directories.dir/build.make CMakeFiles/directories.dir/library/date.c.o.provides.build
.PHONY : CMakeFiles/directories.dir/library/date.c.o.provides

CMakeFiles/directories.dir/library/date.c.o.provides.build: CMakeFiles/directories.dir/library/date.c.o


CMakeFiles/directories.dir/library/dir_nftw.c.o: CMakeFiles/directories.dir/flags.make
CMakeFiles/directories.dir/library/dir_nftw.c.o: ../library/dir_nftw.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/radekkoziol/Projects/CLionProjects/Operating systems/process_managment/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_4) "Building C object CMakeFiles/directories.dir/library/dir_nftw.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/directories.dir/library/dir_nftw.c.o   -c "/home/radekkoziol/Projects/CLionProjects/Operating systems/process_managment/library/dir_nftw.c"

CMakeFiles/directories.dir/library/dir_nftw.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/directories.dir/library/dir_nftw.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "/home/radekkoziol/Projects/CLionProjects/Operating systems/process_managment/library/dir_nftw.c" > CMakeFiles/directories.dir/library/dir_nftw.c.i

CMakeFiles/directories.dir/library/dir_nftw.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/directories.dir/library/dir_nftw.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "/home/radekkoziol/Projects/CLionProjects/Operating systems/process_managment/library/dir_nftw.c" -o CMakeFiles/directories.dir/library/dir_nftw.c.s

CMakeFiles/directories.dir/library/dir_nftw.c.o.requires:

.PHONY : CMakeFiles/directories.dir/library/dir_nftw.c.o.requires

CMakeFiles/directories.dir/library/dir_nftw.c.o.provides: CMakeFiles/directories.dir/library/dir_nftw.c.o.requires
	$(MAKE) -f CMakeFiles/directories.dir/build.make CMakeFiles/directories.dir/library/dir_nftw.c.o.provides.build
.PHONY : CMakeFiles/directories.dir/library/dir_nftw.c.o.provides

CMakeFiles/directories.dir/library/dir_nftw.c.o.provides.build: CMakeFiles/directories.dir/library/dir_nftw.c.o


# Object files for target directories
directories_OBJECTS = \
"CMakeFiles/directories.dir/main.c.o" \
"CMakeFiles/directories.dir/library/dir_sys.c.o" \
"CMakeFiles/directories.dir/library/date.c.o" \
"CMakeFiles/directories.dir/library/dir_nftw.c.o"

# External object files for target directories
directories_EXTERNAL_OBJECTS =

libdirectories.a: CMakeFiles/directories.dir/main.c.o
libdirectories.a: CMakeFiles/directories.dir/library/dir_sys.c.o
libdirectories.a: CMakeFiles/directories.dir/library/date.c.o
libdirectories.a: CMakeFiles/directories.dir/library/dir_nftw.c.o
libdirectories.a: CMakeFiles/directories.dir/build.make
libdirectories.a: CMakeFiles/directories.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/home/radekkoziol/Projects/CLionProjects/Operating systems/process_managment/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_5) "Linking C static library libdirectories.a"
	$(CMAKE_COMMAND) -P CMakeFiles/directories.dir/cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/directories.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/directories.dir/build: libdirectories.a

.PHONY : CMakeFiles/directories.dir/build

CMakeFiles/directories.dir/requires: CMakeFiles/directories.dir/main.c.o.requires
CMakeFiles/directories.dir/requires: CMakeFiles/directories.dir/library/dir_sys.c.o.requires
CMakeFiles/directories.dir/requires: CMakeFiles/directories.dir/library/date.c.o.requires
CMakeFiles/directories.dir/requires: CMakeFiles/directories.dir/library/dir_nftw.c.o.requires

.PHONY : CMakeFiles/directories.dir/requires

CMakeFiles/directories.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/directories.dir/cmake_clean.cmake
.PHONY : CMakeFiles/directories.dir/clean

CMakeFiles/directories.dir/depend:
	cd "/home/radekkoziol/Projects/CLionProjects/Operating systems/process_managment/cmake-build-debug" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/home/radekkoziol/Projects/CLionProjects/Operating systems/process_managment" "/home/radekkoziol/Projects/CLionProjects/Operating systems/process_managment" "/home/radekkoziol/Projects/CLionProjects/Operating systems/process_managment/cmake-build-debug" "/home/radekkoziol/Projects/CLionProjects/Operating systems/process_managment/cmake-build-debug" "/home/radekkoziol/Projects/CLionProjects/Operating systems/process_managment/cmake-build-debug/CMakeFiles/directories.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/directories.dir/depend

