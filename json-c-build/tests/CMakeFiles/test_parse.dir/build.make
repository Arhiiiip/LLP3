# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.28

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
CMAKE_SOURCE_DIR = /home/fermematch/Documents/llp-lab3/json-c

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/fermematch/Documents/llp-lab3/json-c-build

# Include any dependencies generated for this target.
include tests/CMakeFiles/test_parse.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include tests/CMakeFiles/test_parse.dir/compiler_depend.make

# Include the progress variables for this target.
include tests/CMakeFiles/test_parse.dir/progress.make

# Include the compile flags for this target's objects.
include tests/CMakeFiles/test_parse.dir/flags.make

tests/CMakeFiles/test_parse.dir/test_parse.c.o: tests/CMakeFiles/test_parse.dir/flags.make
tests/CMakeFiles/test_parse.dir/test_parse.c.o: /home/fermematch/Documents/llp-lab3/json-c/tests/test_parse.c
tests/CMakeFiles/test_parse.dir/test_parse.c.o: tests/CMakeFiles/test_parse.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/fermematch/Documents/llp-lab3/json-c-build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object tests/CMakeFiles/test_parse.dir/test_parse.c.o"
	cd /home/fermematch/Documents/llp-lab3/json-c-build/tests && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT tests/CMakeFiles/test_parse.dir/test_parse.c.o -MF CMakeFiles/test_parse.dir/test_parse.c.o.d -o CMakeFiles/test_parse.dir/test_parse.c.o -c /home/fermematch/Documents/llp-lab3/json-c/tests/test_parse.c

tests/CMakeFiles/test_parse.dir/test_parse.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/test_parse.dir/test_parse.c.i"
	cd /home/fermematch/Documents/llp-lab3/json-c-build/tests && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/fermematch/Documents/llp-lab3/json-c/tests/test_parse.c > CMakeFiles/test_parse.dir/test_parse.c.i

tests/CMakeFiles/test_parse.dir/test_parse.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/test_parse.dir/test_parse.c.s"
	cd /home/fermematch/Documents/llp-lab3/json-c-build/tests && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/fermematch/Documents/llp-lab3/json-c/tests/test_parse.c -o CMakeFiles/test_parse.dir/test_parse.c.s

# Object files for target test_parse
test_parse_OBJECTS = \
"CMakeFiles/test_parse.dir/test_parse.c.o"

# External object files for target test_parse
test_parse_EXTERNAL_OBJECTS =

tests/test_parse: tests/CMakeFiles/test_parse.dir/test_parse.c.o
tests/test_parse: tests/CMakeFiles/test_parse.dir/build.make
tests/test_parse: libjson-c.so.5.3.0
tests/test_parse: tests/CMakeFiles/test_parse.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/fermematch/Documents/llp-lab3/json-c-build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable test_parse"
	cd /home/fermematch/Documents/llp-lab3/json-c-build/tests && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/test_parse.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
tests/CMakeFiles/test_parse.dir/build: tests/test_parse
.PHONY : tests/CMakeFiles/test_parse.dir/build

tests/CMakeFiles/test_parse.dir/clean:
	cd /home/fermematch/Documents/llp-lab3/json-c-build/tests && $(CMAKE_COMMAND) -P CMakeFiles/test_parse.dir/cmake_clean.cmake
.PHONY : tests/CMakeFiles/test_parse.dir/clean

tests/CMakeFiles/test_parse.dir/depend:
	cd /home/fermematch/Documents/llp-lab3/json-c-build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/fermematch/Documents/llp-lab3/json-c /home/fermematch/Documents/llp-lab3/json-c/tests /home/fermematch/Documents/llp-lab3/json-c-build /home/fermematch/Documents/llp-lab3/json-c-build/tests /home/fermematch/Documents/llp-lab3/json-c-build/tests/CMakeFiles/test_parse.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : tests/CMakeFiles/test_parse.dir/depend

