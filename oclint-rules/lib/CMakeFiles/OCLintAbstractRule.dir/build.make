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
include lib/CMakeFiles/OCLintAbstractRule.dir/depend.make

# Include the progress variables for this target.
include lib/CMakeFiles/OCLintAbstractRule.dir/progress.make

# Include the compile flags for this target's objects.
include lib/CMakeFiles/OCLintAbstractRule.dir/flags.make

lib/CMakeFiles/OCLintAbstractRule.dir/AbstractASTMatcherRule.cpp.o: lib/CMakeFiles/OCLintAbstractRule.dir/flags.make
lib/CMakeFiles/OCLintAbstractRule.dir/AbstractASTMatcherRule.cpp.o: lib/AbstractASTMatcherRule.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/fdh/nn/oclint/oclint-rules/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object lib/CMakeFiles/OCLintAbstractRule.dir/AbstractASTMatcherRule.cpp.o"
	cd /home/fdh/nn/oclint/oclint-rules/lib && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/OCLintAbstractRule.dir/AbstractASTMatcherRule.cpp.o -c /home/fdh/nn/oclint/oclint-rules/lib/AbstractASTMatcherRule.cpp

lib/CMakeFiles/OCLintAbstractRule.dir/AbstractASTMatcherRule.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/OCLintAbstractRule.dir/AbstractASTMatcherRule.cpp.i"
	cd /home/fdh/nn/oclint/oclint-rules/lib && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/fdh/nn/oclint/oclint-rules/lib/AbstractASTMatcherRule.cpp > CMakeFiles/OCLintAbstractRule.dir/AbstractASTMatcherRule.cpp.i

lib/CMakeFiles/OCLintAbstractRule.dir/AbstractASTMatcherRule.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/OCLintAbstractRule.dir/AbstractASTMatcherRule.cpp.s"
	cd /home/fdh/nn/oclint/oclint-rules/lib && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/fdh/nn/oclint/oclint-rules/lib/AbstractASTMatcherRule.cpp -o CMakeFiles/OCLintAbstractRule.dir/AbstractASTMatcherRule.cpp.s

lib/CMakeFiles/OCLintAbstractRule.dir/AbstractASTMatcherRule.cpp.o.requires:

.PHONY : lib/CMakeFiles/OCLintAbstractRule.dir/AbstractASTMatcherRule.cpp.o.requires

lib/CMakeFiles/OCLintAbstractRule.dir/AbstractASTMatcherRule.cpp.o.provides: lib/CMakeFiles/OCLintAbstractRule.dir/AbstractASTMatcherRule.cpp.o.requires
	$(MAKE) -f lib/CMakeFiles/OCLintAbstractRule.dir/build.make lib/CMakeFiles/OCLintAbstractRule.dir/AbstractASTMatcherRule.cpp.o.provides.build
.PHONY : lib/CMakeFiles/OCLintAbstractRule.dir/AbstractASTMatcherRule.cpp.o.provides

lib/CMakeFiles/OCLintAbstractRule.dir/AbstractASTMatcherRule.cpp.o.provides.build: lib/CMakeFiles/OCLintAbstractRule.dir/AbstractASTMatcherRule.cpp.o


lib/CMakeFiles/OCLintAbstractRule.dir/AbstractASTRuleBase.cpp.o: lib/CMakeFiles/OCLintAbstractRule.dir/flags.make
lib/CMakeFiles/OCLintAbstractRule.dir/AbstractASTRuleBase.cpp.o: lib/AbstractASTRuleBase.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/fdh/nn/oclint/oclint-rules/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object lib/CMakeFiles/OCLintAbstractRule.dir/AbstractASTRuleBase.cpp.o"
	cd /home/fdh/nn/oclint/oclint-rules/lib && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/OCLintAbstractRule.dir/AbstractASTRuleBase.cpp.o -c /home/fdh/nn/oclint/oclint-rules/lib/AbstractASTRuleBase.cpp

lib/CMakeFiles/OCLintAbstractRule.dir/AbstractASTRuleBase.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/OCLintAbstractRule.dir/AbstractASTRuleBase.cpp.i"
	cd /home/fdh/nn/oclint/oclint-rules/lib && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/fdh/nn/oclint/oclint-rules/lib/AbstractASTRuleBase.cpp > CMakeFiles/OCLintAbstractRule.dir/AbstractASTRuleBase.cpp.i

lib/CMakeFiles/OCLintAbstractRule.dir/AbstractASTRuleBase.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/OCLintAbstractRule.dir/AbstractASTRuleBase.cpp.s"
	cd /home/fdh/nn/oclint/oclint-rules/lib && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/fdh/nn/oclint/oclint-rules/lib/AbstractASTRuleBase.cpp -o CMakeFiles/OCLintAbstractRule.dir/AbstractASTRuleBase.cpp.s

lib/CMakeFiles/OCLintAbstractRule.dir/AbstractASTRuleBase.cpp.o.requires:

.PHONY : lib/CMakeFiles/OCLintAbstractRule.dir/AbstractASTRuleBase.cpp.o.requires

lib/CMakeFiles/OCLintAbstractRule.dir/AbstractASTRuleBase.cpp.o.provides: lib/CMakeFiles/OCLintAbstractRule.dir/AbstractASTRuleBase.cpp.o.requires
	$(MAKE) -f lib/CMakeFiles/OCLintAbstractRule.dir/build.make lib/CMakeFiles/OCLintAbstractRule.dir/AbstractASTRuleBase.cpp.o.provides.build
.PHONY : lib/CMakeFiles/OCLintAbstractRule.dir/AbstractASTRuleBase.cpp.o.provides

lib/CMakeFiles/OCLintAbstractRule.dir/AbstractASTRuleBase.cpp.o.provides.build: lib/CMakeFiles/OCLintAbstractRule.dir/AbstractASTRuleBase.cpp.o


lib/CMakeFiles/OCLintAbstractRule.dir/AbstractSourceCodeReaderRule.cpp.o: lib/CMakeFiles/OCLintAbstractRule.dir/flags.make
lib/CMakeFiles/OCLintAbstractRule.dir/AbstractSourceCodeReaderRule.cpp.o: lib/AbstractSourceCodeReaderRule.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/fdh/nn/oclint/oclint-rules/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object lib/CMakeFiles/OCLintAbstractRule.dir/AbstractSourceCodeReaderRule.cpp.o"
	cd /home/fdh/nn/oclint/oclint-rules/lib && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/OCLintAbstractRule.dir/AbstractSourceCodeReaderRule.cpp.o -c /home/fdh/nn/oclint/oclint-rules/lib/AbstractSourceCodeReaderRule.cpp

lib/CMakeFiles/OCLintAbstractRule.dir/AbstractSourceCodeReaderRule.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/OCLintAbstractRule.dir/AbstractSourceCodeReaderRule.cpp.i"
	cd /home/fdh/nn/oclint/oclint-rules/lib && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/fdh/nn/oclint/oclint-rules/lib/AbstractSourceCodeReaderRule.cpp > CMakeFiles/OCLintAbstractRule.dir/AbstractSourceCodeReaderRule.cpp.i

lib/CMakeFiles/OCLintAbstractRule.dir/AbstractSourceCodeReaderRule.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/OCLintAbstractRule.dir/AbstractSourceCodeReaderRule.cpp.s"
	cd /home/fdh/nn/oclint/oclint-rules/lib && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/fdh/nn/oclint/oclint-rules/lib/AbstractSourceCodeReaderRule.cpp -o CMakeFiles/OCLintAbstractRule.dir/AbstractSourceCodeReaderRule.cpp.s

lib/CMakeFiles/OCLintAbstractRule.dir/AbstractSourceCodeReaderRule.cpp.o.requires:

.PHONY : lib/CMakeFiles/OCLintAbstractRule.dir/AbstractSourceCodeReaderRule.cpp.o.requires

lib/CMakeFiles/OCLintAbstractRule.dir/AbstractSourceCodeReaderRule.cpp.o.provides: lib/CMakeFiles/OCLintAbstractRule.dir/AbstractSourceCodeReaderRule.cpp.o.requires
	$(MAKE) -f lib/CMakeFiles/OCLintAbstractRule.dir/build.make lib/CMakeFiles/OCLintAbstractRule.dir/AbstractSourceCodeReaderRule.cpp.o.provides.build
.PHONY : lib/CMakeFiles/OCLintAbstractRule.dir/AbstractSourceCodeReaderRule.cpp.o.provides

lib/CMakeFiles/OCLintAbstractRule.dir/AbstractSourceCodeReaderRule.cpp.o.provides.build: lib/CMakeFiles/OCLintAbstractRule.dir/AbstractSourceCodeReaderRule.cpp.o


# Object files for target OCLintAbstractRule
OCLintAbstractRule_OBJECTS = \
"CMakeFiles/OCLintAbstractRule.dir/AbstractASTMatcherRule.cpp.o" \
"CMakeFiles/OCLintAbstractRule.dir/AbstractASTRuleBase.cpp.o" \
"CMakeFiles/OCLintAbstractRule.dir/AbstractSourceCodeReaderRule.cpp.o"

# External object files for target OCLintAbstractRule
OCLintAbstractRule_EXTERNAL_OBJECTS =

lib/libOCLintAbstractRule.a: lib/CMakeFiles/OCLintAbstractRule.dir/AbstractASTMatcherRule.cpp.o
lib/libOCLintAbstractRule.a: lib/CMakeFiles/OCLintAbstractRule.dir/AbstractASTRuleBase.cpp.o
lib/libOCLintAbstractRule.a: lib/CMakeFiles/OCLintAbstractRule.dir/AbstractSourceCodeReaderRule.cpp.o
lib/libOCLintAbstractRule.a: lib/CMakeFiles/OCLintAbstractRule.dir/build.make
lib/libOCLintAbstractRule.a: lib/CMakeFiles/OCLintAbstractRule.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/fdh/nn/oclint/oclint-rules/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX static library libOCLintAbstractRule.a"
	cd /home/fdh/nn/oclint/oclint-rules/lib && $(CMAKE_COMMAND) -P CMakeFiles/OCLintAbstractRule.dir/cmake_clean_target.cmake
	cd /home/fdh/nn/oclint/oclint-rules/lib && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/OCLintAbstractRule.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
lib/CMakeFiles/OCLintAbstractRule.dir/build: lib/libOCLintAbstractRule.a

.PHONY : lib/CMakeFiles/OCLintAbstractRule.dir/build

lib/CMakeFiles/OCLintAbstractRule.dir/requires: lib/CMakeFiles/OCLintAbstractRule.dir/AbstractASTMatcherRule.cpp.o.requires
lib/CMakeFiles/OCLintAbstractRule.dir/requires: lib/CMakeFiles/OCLintAbstractRule.dir/AbstractASTRuleBase.cpp.o.requires
lib/CMakeFiles/OCLintAbstractRule.dir/requires: lib/CMakeFiles/OCLintAbstractRule.dir/AbstractSourceCodeReaderRule.cpp.o.requires

.PHONY : lib/CMakeFiles/OCLintAbstractRule.dir/requires

lib/CMakeFiles/OCLintAbstractRule.dir/clean:
	cd /home/fdh/nn/oclint/oclint-rules/lib && $(CMAKE_COMMAND) -P CMakeFiles/OCLintAbstractRule.dir/cmake_clean.cmake
.PHONY : lib/CMakeFiles/OCLintAbstractRule.dir/clean

lib/CMakeFiles/OCLintAbstractRule.dir/depend:
	cd /home/fdh/nn/oclint/oclint-rules && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/fdh/nn/oclint/oclint-rules /home/fdh/nn/oclint/oclint-rules/lib /home/fdh/nn/oclint/oclint-rules /home/fdh/nn/oclint/oclint-rules/lib /home/fdh/nn/oclint/oclint-rules/lib/CMakeFiles/OCLintAbstractRule.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : lib/CMakeFiles/OCLintAbstractRule.dir/depend

