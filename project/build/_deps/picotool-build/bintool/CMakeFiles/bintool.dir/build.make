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
CMAKE_SOURCE_DIR = /home/duckmadeofwood/Desktop/project/build/_deps/picotool-src

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/duckmadeofwood/Desktop/project/build/_deps/picotool-build

# Include any dependencies generated for this target.
include bintool/CMakeFiles/bintool.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include bintool/CMakeFiles/bintool.dir/compiler_depend.make

# Include the compile flags for this target's objects.
include bintool/CMakeFiles/bintool.dir/flags.make

bintool/CMakeFiles/bintool.dir/bintool.cpp.o: bintool/CMakeFiles/bintool.dir/flags.make
bintool/CMakeFiles/bintool.dir/bintool.cpp.o: /home/duckmadeofwood/Desktop/project/build/_deps/picotool-src/bintool/bintool.cpp
bintool/CMakeFiles/bintool.dir/bintool.cpp.o: bintool/CMakeFiles/bintool.dir/compiler_depend.ts
	cd /home/duckmadeofwood/Desktop/project/build/_deps/picotool-build/bintool && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT bintool/CMakeFiles/bintool.dir/bintool.cpp.o -MF CMakeFiles/bintool.dir/bintool.cpp.o.d -o CMakeFiles/bintool.dir/bintool.cpp.o -c /home/duckmadeofwood/Desktop/project/build/_deps/picotool-src/bintool/bintool.cpp

bintool/CMakeFiles/bintool.dir/bintool.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/bintool.dir/bintool.cpp.i"
	cd /home/duckmadeofwood/Desktop/project/build/_deps/picotool-build/bintool && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/duckmadeofwood/Desktop/project/build/_deps/picotool-src/bintool/bintool.cpp > CMakeFiles/bintool.dir/bintool.cpp.i

bintool/CMakeFiles/bintool.dir/bintool.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/bintool.dir/bintool.cpp.s"
	cd /home/duckmadeofwood/Desktop/project/build/_deps/picotool-build/bintool && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/duckmadeofwood/Desktop/project/build/_deps/picotool-src/bintool/bintool.cpp -o CMakeFiles/bintool.dir/bintool.cpp.s

# Object files for target bintool
bintool_OBJECTS = \
"CMakeFiles/bintool.dir/bintool.cpp.o"

# External object files for target bintool
bintool_EXTERNAL_OBJECTS =

bintool/libbintool.a: bintool/CMakeFiles/bintool.dir/bintool.cpp.o
bintool/libbintool.a: bintool/CMakeFiles/bintool.dir/build.make
bintool/libbintool.a: bintool/CMakeFiles/bintool.dir/link.txt
	cd /home/duckmadeofwood/Desktop/project/build/_deps/picotool-build/bintool && $(CMAKE_COMMAND) -P CMakeFiles/bintool.dir/cmake_clean_target.cmake
	cd /home/duckmadeofwood/Desktop/project/build/_deps/picotool-build/bintool && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/bintool.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
bintool/CMakeFiles/bintool.dir/build: bintool/libbintool.a
.PHONY : bintool/CMakeFiles/bintool.dir/build

bintool/CMakeFiles/bintool.dir/clean:
	cd /home/duckmadeofwood/Desktop/project/build/_deps/picotool-build/bintool && $(CMAKE_COMMAND) -P CMakeFiles/bintool.dir/cmake_clean.cmake
.PHONY : bintool/CMakeFiles/bintool.dir/clean

bintool/CMakeFiles/bintool.dir/depend:
	cd /home/duckmadeofwood/Desktop/project/build/_deps/picotool-build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/duckmadeofwood/Desktop/project/build/_deps/picotool-src /home/duckmadeofwood/Desktop/project/build/_deps/picotool-src/bintool /home/duckmadeofwood/Desktop/project/build/_deps/picotool-build /home/duckmadeofwood/Desktop/project/build/_deps/picotool-build/bintool /home/duckmadeofwood/Desktop/project/build/_deps/picotool-build/bintool/CMakeFiles/bintool.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : bintool/CMakeFiles/bintool.dir/depend

