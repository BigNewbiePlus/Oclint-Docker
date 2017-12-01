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
CMAKE_COMMAND = /usr/local/bin/cmake

# The command to remove a file.
RM = /usr/local/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/fdh/nn/oclint/oclint-rules

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/fdh/nn/oclint/oclint-rules

# Include any dependencies generated for this target.
include lib/util/CMakeFiles/OCLintUtil.dir/depend.make

# Include the progress variables for this target.
include lib/util/CMakeFiles/OCLintUtil.dir/progress.make

# Include the compile flags for this target's objects.
include lib/util/CMakeFiles/OCLintUtil.dir/flags.make

lib/util/CMakeFiles/OCLintUtil.dir/ASTUtil.cpp.o: lib/util/CMakeFiles/OCLintUtil.dir/flags.make
lib/util/CMakeFiles/OCLintUtil.dir/ASTUtil.cpp.o: lib/util/ASTUtil.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/fdh/nn/oclint/oclint-rules/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object lib/util/CMakeFiles/OCLintUtil.dir/ASTUtil.cpp.o"
	cd /home/fdh/nn/oclint/oclint-rules/lib/util && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/OCLintUtil.dir/ASTUtil.cpp.o -c /home/fdh/nn/oclint/oclint-rules/lib/util/ASTUtil.cpp

lib/util/CMakeFiles/OCLintUtil.dir/ASTUtil.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/OCLintUtil.dir/ASTUtil.cpp.i"
	cd /home/fdh/nn/oclint/oclint-rules/lib/util && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/fdh/nn/oclint/oclint-rules/lib/util/ASTUtil.cpp > CMakeFiles/OCLintUtil.dir/ASTUtil.cpp.i

lib/util/CMakeFiles/OCLintUtil.dir/ASTUtil.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/OCLintUtil.dir/ASTUtil.cpp.s"
	cd /home/fdh/nn/oclint/oclint-rules/lib/util && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/fdh/nn/oclint/oclint-rules/lib/util/ASTUtil.cpp -o CMakeFiles/OCLintUtil.dir/ASTUtil.cpp.s

lib/util/CMakeFiles/OCLintUtil.dir/ASTUtil.cpp.o.requires:

.PHONY : lib/util/CMakeFiles/OCLintUtil.dir/ASTUtil.cpp.o.requires

lib/util/CMakeFiles/OCLintUtil.dir/ASTUtil.cpp.o.provides: lib/util/CMakeFiles/OCLintUtil.dir/ASTUtil.cpp.o.requires
	$(MAKE) -f lib/util/CMakeFiles/OCLintUtil.dir/build.make lib/util/CMakeFiles/OCLintUtil.dir/ASTUtil.cpp.o.provides.build
.PHONY : lib/util/CMakeFiles/OCLintUtil.dir/ASTUtil.cpp.o.provides

lib/util/CMakeFiles/OCLintUtil.dir/ASTUtil.cpp.o.provides.build: lib/util/CMakeFiles/OCLintUtil.dir/ASTUtil.cpp.o


lib/util/CMakeFiles/OCLintUtil.dir/StdUtil.cpp.o: lib/util/CMakeFiles/OCLintUtil.dir/flags.make
lib/util/CMakeFiles/OCLintUtil.dir/StdUtil.cpp.o: lib/util/StdUtil.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/fdh/nn/oclint/oclint-rules/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object lib/util/CMakeFiles/OCLintUtil.dir/StdUtil.cpp.o"
	cd /home/fdh/nn/oclint/oclint-rules/lib/util && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/OCLintUtil.dir/StdUtil.cpp.o -c /home/fdh/nn/oclint/oclint-rules/lib/util/StdUtil.cpp

lib/util/CMakeFiles/OCLintUtil.dir/StdUtil.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/OCLintUtil.dir/StdUtil.cpp.i"
	cd /home/fdh/nn/oclint/oclint-rules/lib/util && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/fdh/nn/oclint/oclint-rules/lib/util/StdUtil.cpp > CMakeFiles/OCLintUtil.dir/StdUtil.cpp.i

lib/util/CMakeFiles/OCLintUtil.dir/StdUtil.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/OCLintUtil.dir/StdUtil.cpp.s"
	cd /home/fdh/nn/oclint/oclint-rules/lib/util && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/fdh/nn/oclint/oclint-rules/lib/util/StdUtil.cpp -o CMakeFiles/OCLintUtil.dir/StdUtil.cpp.s

lib/util/CMakeFiles/OCLintUtil.dir/StdUtil.cpp.o.requires:

.PHONY : lib/util/CMakeFiles/OCLintUtil.dir/StdUtil.cpp.o.requires

lib/util/CMakeFiles/OCLintUtil.dir/StdUtil.cpp.o.provides: lib/util/CMakeFiles/OCLintUtil.dir/StdUtil.cpp.o.requires
	$(MAKE) -f lib/util/CMakeFiles/OCLintUtil.dir/build.make lib/util/CMakeFiles/OCLintUtil.dir/StdUtil.cpp.o.provides.build
.PHONY : lib/util/CMakeFiles/OCLintUtil.dir/StdUtil.cpp.o.provides

lib/util/CMakeFiles/OCLintUtil.dir/StdUtil.cpp.o.provides.build: lib/util/CMakeFiles/OCLintUtil.dir/StdUtil.cpp.o


# Object files for target OCLintUtil
OCLintUtil_OBJECTS = \
"CMakeFiles/OCLintUtil.dir/ASTUtil.cpp.o" \
"CMakeFiles/OCLintUtil.dir/StdUtil.cpp.o"

# External object files for target OCLintUtil
OCLintUtil_EXTERNAL_OBJECTS =

lib/util/libOCLintUtil.a: lib/util/CMakeFiles/OCLintUtil.dir/ASTUtil.cpp.o
lib/util/libOCLintUtil.a: lib/util/CMakeFiles/OCLintUtil.dir/StdUtil.cpp.o
lib/util/libOCLintUtil.a: lib/util/CMakeFiles/OCLintUtil.dir/build.make
lib/util/libOCLintUtil.a: lib/util/CMakeFiles/OCLintUtil.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/fdh/nn/oclint/oclint-rules/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX static library libOCLintUtil.a"
	cd /home/fdh/nn/oclint/oclint-rules/lib/util && $(CMAKE_COMMAND) -P CMakeFiles/OCLintUtil.dir/cmake_clean_target.cmake
	cd /home/fdh/nn/oclint/oclint-rules/lib/util && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/OCLintUtil.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
lib/util/CMakeFiles/OCLintUtil.dir/build: lib/util/libOCLintUtil.a

.PHONY : lib/util/CMakeFiles/OCLintUtil.dir/build

lib/util/CMakeFiles/OCLintUtil.dir/requires: lib/util/CMakeFiles/OCLintUtil.dir/ASTUtil.cpp.o.requires
lib/util/CMakeFiles/OCLintUtil.dir/requires: lib/util/CMakeFiles/OCLintUtil.dir/StdUtil.cpp.o.requires

.PHONY : lib/util/CMakeFiles/OCLintUtil.dir/requires

lib/util/CMakeFiles/OCLintUtil.dir/clean:
	cd /home/fdh/nn/oclint/oclint-rules/lib/util && $(CMAKE_COMMAND) -P CMakeFiles/OCLintUtil.dir/cmake_clean.cmake
.PHONY : lib/util/CMakeFiles/OCLintUtil.dir/clean

lib/util/CMakeFiles/OCLintUtil.dir/depend:
	cd /home/fdh/nn/oclint/oclint-rules && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/fdh/nn/oclint/oclint-rules /home/fdh/nn/oclint/oclint-rules/lib/util /home/fdh/nn/oclint/oclint-rules /home/fdh/nn/oclint/oclint-rules/lib/util /home/fdh/nn/oclint/oclint-rules/lib/util/CMakeFiles/OCLintUtil.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : lib/util/CMakeFiles/OCLintUtil.dir/depend

