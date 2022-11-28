# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.24

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/gpozzato/Repos/clay_assignment

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/gpozzato/Repos/clay_assignment

# Include any dependencies generated for this target.
include test/CMakeFiles/run_ut_kvp_server.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include test/CMakeFiles/run_ut_kvp_server.dir/compiler_depend.make

# Include the progress variables for this target.
include test/CMakeFiles/run_ut_kvp_server.dir/progress.make

# Include the compile flags for this target's objects.
include test/CMakeFiles/run_ut_kvp_server.dir/flags.make

test/CMakeFiles/run_ut_kvp_server.dir/test_kvp_server.cpp.o: test/CMakeFiles/run_ut_kvp_server.dir/flags.make
test/CMakeFiles/run_ut_kvp_server.dir/test_kvp_server.cpp.o: test/test_kvp_server.cpp
test/CMakeFiles/run_ut_kvp_server.dir/test_kvp_server.cpp.o: test/CMakeFiles/run_ut_kvp_server.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/gpozzato/Repos/clay_assignment/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object test/CMakeFiles/run_ut_kvp_server.dir/test_kvp_server.cpp.o"
	cd /home/gpozzato/Repos/clay_assignment/test && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT test/CMakeFiles/run_ut_kvp_server.dir/test_kvp_server.cpp.o -MF CMakeFiles/run_ut_kvp_server.dir/test_kvp_server.cpp.o.d -o CMakeFiles/run_ut_kvp_server.dir/test_kvp_server.cpp.o -c /home/gpozzato/Repos/clay_assignment/test/test_kvp_server.cpp

test/CMakeFiles/run_ut_kvp_server.dir/test_kvp_server.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/run_ut_kvp_server.dir/test_kvp_server.cpp.i"
	cd /home/gpozzato/Repos/clay_assignment/test && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/gpozzato/Repos/clay_assignment/test/test_kvp_server.cpp > CMakeFiles/run_ut_kvp_server.dir/test_kvp_server.cpp.i

test/CMakeFiles/run_ut_kvp_server.dir/test_kvp_server.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/run_ut_kvp_server.dir/test_kvp_server.cpp.s"
	cd /home/gpozzato/Repos/clay_assignment/test && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/gpozzato/Repos/clay_assignment/test/test_kvp_server.cpp -o CMakeFiles/run_ut_kvp_server.dir/test_kvp_server.cpp.s

# Object files for target run_ut_kvp_server
run_ut_kvp_server_OBJECTS = \
"CMakeFiles/run_ut_kvp_server.dir/test_kvp_server.cpp.o"

# External object files for target run_ut_kvp_server
run_ut_kvp_server_EXTERNAL_OBJECTS =

test/run_ut_kvp_server: test/CMakeFiles/run_ut_kvp_server.dir/test_kvp_server.cpp.o
test/run_ut_kvp_server: test/CMakeFiles/run_ut_kvp_server.dir/build.make
test/run_ut_kvp_server: server/src/libKvpServer.so
test/run_ut_kvp_server: /usr/lib/x86_64-linux-gnu/libgtest.a
test/run_ut_kvp_server: test/CMakeFiles/run_ut_kvp_server.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/gpozzato/Repos/clay_assignment/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable run_ut_kvp_server"
	cd /home/gpozzato/Repos/clay_assignment/test && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/run_ut_kvp_server.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
test/CMakeFiles/run_ut_kvp_server.dir/build: test/run_ut_kvp_server
.PHONY : test/CMakeFiles/run_ut_kvp_server.dir/build

test/CMakeFiles/run_ut_kvp_server.dir/clean:
	cd /home/gpozzato/Repos/clay_assignment/test && $(CMAKE_COMMAND) -P CMakeFiles/run_ut_kvp_server.dir/cmake_clean.cmake
.PHONY : test/CMakeFiles/run_ut_kvp_server.dir/clean

test/CMakeFiles/run_ut_kvp_server.dir/depend:
	cd /home/gpozzato/Repos/clay_assignment && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/gpozzato/Repos/clay_assignment /home/gpozzato/Repos/clay_assignment/test /home/gpozzato/Repos/clay_assignment /home/gpozzato/Repos/clay_assignment/test /home/gpozzato/Repos/clay_assignment/test/CMakeFiles/run_ut_kvp_server.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : test/CMakeFiles/run_ut_kvp_server.dir/depend
