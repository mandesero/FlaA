# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.25

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
CMAKE_COMMAND = /var/lib/snapd/snap/cmake/1216/bin/cmake

# The command to remove a file.
RM = /var/lib/snapd/snap/cmake/1216/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/mandesero/Desktop/VMK/FLaA/1

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/mandesero/Desktop/VMK/FLaA/1

# Include any dependencies generated for this target.
include CMakeFiles/re2dfa.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/re2dfa.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/re2dfa.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/re2dfa.dir/flags.make

CMakeFiles/re2dfa.dir/main.cpp.o: CMakeFiles/re2dfa.dir/flags.make
CMakeFiles/re2dfa.dir/main.cpp.o: main.cpp
CMakeFiles/re2dfa.dir/main.cpp.o: CMakeFiles/re2dfa.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/mandesero/Desktop/VMK/FLaA/1/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/re2dfa.dir/main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/re2dfa.dir/main.cpp.o -MF CMakeFiles/re2dfa.dir/main.cpp.o.d -o CMakeFiles/re2dfa.dir/main.cpp.o -c /home/mandesero/Desktop/VMK/FLaA/1/main.cpp

CMakeFiles/re2dfa.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/re2dfa.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/mandesero/Desktop/VMK/FLaA/1/main.cpp > CMakeFiles/re2dfa.dir/main.cpp.i

CMakeFiles/re2dfa.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/re2dfa.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/mandesero/Desktop/VMK/FLaA/1/main.cpp -o CMakeFiles/re2dfa.dir/main.cpp.s

CMakeFiles/re2dfa.dir/task.cpp.o: CMakeFiles/re2dfa.dir/flags.make
CMakeFiles/re2dfa.dir/task.cpp.o: task.cpp
CMakeFiles/re2dfa.dir/task.cpp.o: CMakeFiles/re2dfa.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/mandesero/Desktop/VMK/FLaA/1/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/re2dfa.dir/task.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/re2dfa.dir/task.cpp.o -MF CMakeFiles/re2dfa.dir/task.cpp.o.d -o CMakeFiles/re2dfa.dir/task.cpp.o -c /home/mandesero/Desktop/VMK/FLaA/1/task.cpp

CMakeFiles/re2dfa.dir/task.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/re2dfa.dir/task.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/mandesero/Desktop/VMK/FLaA/1/task.cpp > CMakeFiles/re2dfa.dir/task.cpp.i

CMakeFiles/re2dfa.dir/task.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/re2dfa.dir/task.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/mandesero/Desktop/VMK/FLaA/1/task.cpp -o CMakeFiles/re2dfa.dir/task.cpp.s

# Object files for target re2dfa
re2dfa_OBJECTS = \
"CMakeFiles/re2dfa.dir/main.cpp.o" \
"CMakeFiles/re2dfa.dir/task.cpp.o"

# External object files for target re2dfa
re2dfa_EXTERNAL_OBJECTS =

re2dfa: CMakeFiles/re2dfa.dir/main.cpp.o
re2dfa: CMakeFiles/re2dfa.dir/task.cpp.o
re2dfa: CMakeFiles/re2dfa.dir/build.make
re2dfa: CMakeFiles/re2dfa.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/mandesero/Desktop/VMK/FLaA/1/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable re2dfa"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/re2dfa.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/re2dfa.dir/build: re2dfa
.PHONY : CMakeFiles/re2dfa.dir/build

CMakeFiles/re2dfa.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/re2dfa.dir/cmake_clean.cmake
.PHONY : CMakeFiles/re2dfa.dir/clean

CMakeFiles/re2dfa.dir/depend:
	cd /home/mandesero/Desktop/VMK/FLaA/1 && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/mandesero/Desktop/VMK/FLaA/1 /home/mandesero/Desktop/VMK/FLaA/1 /home/mandesero/Desktop/VMK/FLaA/1 /home/mandesero/Desktop/VMK/FLaA/1 /home/mandesero/Desktop/VMK/FLaA/1/CMakeFiles/re2dfa.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/re2dfa.dir/depend

