# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/minyoung/kaliberai/cpp

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/minyoung/kaliberai/cpp

# Include any dependencies generated for this target.
include CMakeFiles/Tests.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Tests.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Tests.dir/flags.make

CMakeFiles/Tests.dir/tests.cpp.o: CMakeFiles/Tests.dir/flags.make
CMakeFiles/Tests.dir/tests.cpp.o: tests.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/minyoung/kaliberai/cpp/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Tests.dir/tests.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Tests.dir/tests.cpp.o -c /home/minyoung/kaliberai/cpp/tests.cpp

CMakeFiles/Tests.dir/tests.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Tests.dir/tests.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/minyoung/kaliberai/cpp/tests.cpp > CMakeFiles/Tests.dir/tests.cpp.i

CMakeFiles/Tests.dir/tests.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Tests.dir/tests.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/minyoung/kaliberai/cpp/tests.cpp -o CMakeFiles/Tests.dir/tests.cpp.s

# Object files for target Tests
Tests_OBJECTS = \
"CMakeFiles/Tests.dir/tests.cpp.o"

# External object files for target Tests
Tests_EXTERNAL_OBJECTS =

Tests: CMakeFiles/Tests.dir/tests.cpp.o
Tests: CMakeFiles/Tests.dir/build.make
Tests: CMakeFiles/Tests.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/minyoung/kaliberai/cpp/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable Tests"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Tests.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Tests.dir/build: Tests

.PHONY : CMakeFiles/Tests.dir/build

CMakeFiles/Tests.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Tests.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Tests.dir/clean

CMakeFiles/Tests.dir/depend:
	cd /home/minyoung/kaliberai/cpp && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/minyoung/kaliberai/cpp /home/minyoung/kaliberai/cpp /home/minyoung/kaliberai/cpp /home/minyoung/kaliberai/cpp /home/minyoung/kaliberai/cpp/CMakeFiles/Tests.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Tests.dir/depend

