# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

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
CMAKE_SOURCE_DIR = /workspaces/cs225/Chess-graph/code

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /workspaces/cs225/Chess-graph/code/build

# Include any dependencies generated for this target.
include src/CMakeFiles/src.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include src/CMakeFiles/src.dir/compiler_depend.make

# Include the progress variables for this target.
include src/CMakeFiles/src.dir/progress.make

# Include the compile flags for this target's objects.
include src/CMakeFiles/src.dir/flags.make

src/CMakeFiles/src.dir/graph.cpp.o: src/CMakeFiles/src.dir/flags.make
src/CMakeFiles/src.dir/graph.cpp.o: ../src/graph.cpp
src/CMakeFiles/src.dir/graph.cpp.o: src/CMakeFiles/src.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/workspaces/cs225/Chess-graph/code/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/CMakeFiles/src.dir/graph.cpp.o"
	cd /workspaces/cs225/Chess-graph/code/build/src && /usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/CMakeFiles/src.dir/graph.cpp.o -MF CMakeFiles/src.dir/graph.cpp.o.d -o CMakeFiles/src.dir/graph.cpp.o -c /workspaces/cs225/Chess-graph/code/src/graph.cpp

src/CMakeFiles/src.dir/graph.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/src.dir/graph.cpp.i"
	cd /workspaces/cs225/Chess-graph/code/build/src && /usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /workspaces/cs225/Chess-graph/code/src/graph.cpp > CMakeFiles/src.dir/graph.cpp.i

src/CMakeFiles/src.dir/graph.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/src.dir/graph.cpp.s"
	cd /workspaces/cs225/Chess-graph/code/build/src && /usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /workspaces/cs225/Chess-graph/code/src/graph.cpp -o CMakeFiles/src.dir/graph.cpp.s

src/CMakeFiles/src.dir/graph_algorithms.cpp.o: src/CMakeFiles/src.dir/flags.make
src/CMakeFiles/src.dir/graph_algorithms.cpp.o: ../src/graph_algorithms.cpp
src/CMakeFiles/src.dir/graph_algorithms.cpp.o: src/CMakeFiles/src.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/workspaces/cs225/Chess-graph/code/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object src/CMakeFiles/src.dir/graph_algorithms.cpp.o"
	cd /workspaces/cs225/Chess-graph/code/build/src && /usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/CMakeFiles/src.dir/graph_algorithms.cpp.o -MF CMakeFiles/src.dir/graph_algorithms.cpp.o.d -o CMakeFiles/src.dir/graph_algorithms.cpp.o -c /workspaces/cs225/Chess-graph/code/src/graph_algorithms.cpp

src/CMakeFiles/src.dir/graph_algorithms.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/src.dir/graph_algorithms.cpp.i"
	cd /workspaces/cs225/Chess-graph/code/build/src && /usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /workspaces/cs225/Chess-graph/code/src/graph_algorithms.cpp > CMakeFiles/src.dir/graph_algorithms.cpp.i

src/CMakeFiles/src.dir/graph_algorithms.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/src.dir/graph_algorithms.cpp.s"
	cd /workspaces/cs225/Chess-graph/code/build/src && /usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /workspaces/cs225/Chess-graph/code/src/graph_algorithms.cpp -o CMakeFiles/src.dir/graph_algorithms.cpp.s

src/CMakeFiles/src.dir/graph_generator.cpp.o: src/CMakeFiles/src.dir/flags.make
src/CMakeFiles/src.dir/graph_generator.cpp.o: ../src/graph_generator.cpp
src/CMakeFiles/src.dir/graph_generator.cpp.o: src/CMakeFiles/src.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/workspaces/cs225/Chess-graph/code/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object src/CMakeFiles/src.dir/graph_generator.cpp.o"
	cd /workspaces/cs225/Chess-graph/code/build/src && /usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/CMakeFiles/src.dir/graph_generator.cpp.o -MF CMakeFiles/src.dir/graph_generator.cpp.o.d -o CMakeFiles/src.dir/graph_generator.cpp.o -c /workspaces/cs225/Chess-graph/code/src/graph_generator.cpp

src/CMakeFiles/src.dir/graph_generator.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/src.dir/graph_generator.cpp.i"
	cd /workspaces/cs225/Chess-graph/code/build/src && /usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /workspaces/cs225/Chess-graph/code/src/graph_generator.cpp > CMakeFiles/src.dir/graph_generator.cpp.i

src/CMakeFiles/src.dir/graph_generator.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/src.dir/graph_generator.cpp.s"
	cd /workspaces/cs225/Chess-graph/code/build/src && /usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /workspaces/cs225/Chess-graph/code/src/graph_generator.cpp -o CMakeFiles/src.dir/graph_generator.cpp.s

src/CMakeFiles/src.dir/position.cpp.o: src/CMakeFiles/src.dir/flags.make
src/CMakeFiles/src.dir/position.cpp.o: ../src/position.cpp
src/CMakeFiles/src.dir/position.cpp.o: src/CMakeFiles/src.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/workspaces/cs225/Chess-graph/code/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object src/CMakeFiles/src.dir/position.cpp.o"
	cd /workspaces/cs225/Chess-graph/code/build/src && /usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/CMakeFiles/src.dir/position.cpp.o -MF CMakeFiles/src.dir/position.cpp.o.d -o CMakeFiles/src.dir/position.cpp.o -c /workspaces/cs225/Chess-graph/code/src/position.cpp

src/CMakeFiles/src.dir/position.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/src.dir/position.cpp.i"
	cd /workspaces/cs225/Chess-graph/code/build/src && /usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /workspaces/cs225/Chess-graph/code/src/position.cpp > CMakeFiles/src.dir/position.cpp.i

src/CMakeFiles/src.dir/position.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/src.dir/position.cpp.s"
	cd /workspaces/cs225/Chess-graph/code/build/src && /usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /workspaces/cs225/Chess-graph/code/src/position.cpp -o CMakeFiles/src.dir/position.cpp.s

src/CMakeFiles/src.dir/utils.cpp.o: src/CMakeFiles/src.dir/flags.make
src/CMakeFiles/src.dir/utils.cpp.o: ../src/utils.cpp
src/CMakeFiles/src.dir/utils.cpp.o: src/CMakeFiles/src.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/workspaces/cs225/Chess-graph/code/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object src/CMakeFiles/src.dir/utils.cpp.o"
	cd /workspaces/cs225/Chess-graph/code/build/src && /usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/CMakeFiles/src.dir/utils.cpp.o -MF CMakeFiles/src.dir/utils.cpp.o.d -o CMakeFiles/src.dir/utils.cpp.o -c /workspaces/cs225/Chess-graph/code/src/utils.cpp

src/CMakeFiles/src.dir/utils.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/src.dir/utils.cpp.i"
	cd /workspaces/cs225/Chess-graph/code/build/src && /usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /workspaces/cs225/Chess-graph/code/src/utils.cpp > CMakeFiles/src.dir/utils.cpp.i

src/CMakeFiles/src.dir/utils.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/src.dir/utils.cpp.s"
	cd /workspaces/cs225/Chess-graph/code/build/src && /usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /workspaces/cs225/Chess-graph/code/src/utils.cpp -o CMakeFiles/src.dir/utils.cpp.s

# Object files for target src
src_OBJECTS = \
"CMakeFiles/src.dir/graph.cpp.o" \
"CMakeFiles/src.dir/graph_algorithms.cpp.o" \
"CMakeFiles/src.dir/graph_generator.cpp.o" \
"CMakeFiles/src.dir/position.cpp.o" \
"CMakeFiles/src.dir/utils.cpp.o"

# External object files for target src
src_EXTERNAL_OBJECTS =

src/libsrc.a: src/CMakeFiles/src.dir/graph.cpp.o
src/libsrc.a: src/CMakeFiles/src.dir/graph_algorithms.cpp.o
src/libsrc.a: src/CMakeFiles/src.dir/graph_generator.cpp.o
src/libsrc.a: src/CMakeFiles/src.dir/position.cpp.o
src/libsrc.a: src/CMakeFiles/src.dir/utils.cpp.o
src/libsrc.a: src/CMakeFiles/src.dir/build.make
src/libsrc.a: src/CMakeFiles/src.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/workspaces/cs225/Chess-graph/code/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Linking CXX static library libsrc.a"
	cd /workspaces/cs225/Chess-graph/code/build/src && $(CMAKE_COMMAND) -P CMakeFiles/src.dir/cmake_clean_target.cmake
	cd /workspaces/cs225/Chess-graph/code/build/src && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/src.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/CMakeFiles/src.dir/build: src/libsrc.a
.PHONY : src/CMakeFiles/src.dir/build

src/CMakeFiles/src.dir/clean:
	cd /workspaces/cs225/Chess-graph/code/build/src && $(CMAKE_COMMAND) -P CMakeFiles/src.dir/cmake_clean.cmake
.PHONY : src/CMakeFiles/src.dir/clean

src/CMakeFiles/src.dir/depend:
	cd /workspaces/cs225/Chess-graph/code/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /workspaces/cs225/Chess-graph/code /workspaces/cs225/Chess-graph/code/src /workspaces/cs225/Chess-graph/code/build /workspaces/cs225/Chess-graph/code/build/src /workspaces/cs225/Chess-graph/code/build/src/CMakeFiles/src.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/CMakeFiles/src.dir/depend

