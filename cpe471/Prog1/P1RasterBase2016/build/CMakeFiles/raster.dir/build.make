# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

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

# The program to use to edit the cache.
CMAKE_EDIT_COMMAND = /usr/bin/ccmake

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = //home/rablair/cpe471/Prog1/P1RasterBase2016

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = //home/rablair/cpe471/Prog1/P1RasterBase2016/build

# Include any dependencies generated for this target.
include CMakeFiles/raster.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/raster.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/raster.dir/flags.make

CMakeFiles/raster.dir/src/Image.cpp.o: CMakeFiles/raster.dir/flags.make
CMakeFiles/raster.dir/src/Image.cpp.o: ../src/Image.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report //home/rablair/cpe471/Prog1/P1RasterBase2016/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/raster.dir/src/Image.cpp.o"
	/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/raster.dir/src/Image.cpp.o -c //home/rablair/cpe471/Prog1/P1RasterBase2016/src/Image.cpp

CMakeFiles/raster.dir/src/Image.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/raster.dir/src/Image.cpp.i"
	/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E //home/rablair/cpe471/Prog1/P1RasterBase2016/src/Image.cpp > CMakeFiles/raster.dir/src/Image.cpp.i

CMakeFiles/raster.dir/src/Image.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/raster.dir/src/Image.cpp.s"
	/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S //home/rablair/cpe471/Prog1/P1RasterBase2016/src/Image.cpp -o CMakeFiles/raster.dir/src/Image.cpp.s

CMakeFiles/raster.dir/src/Image.cpp.o.requires:
.PHONY : CMakeFiles/raster.dir/src/Image.cpp.o.requires

CMakeFiles/raster.dir/src/Image.cpp.o.provides: CMakeFiles/raster.dir/src/Image.cpp.o.requires
	$(MAKE) -f CMakeFiles/raster.dir/build.make CMakeFiles/raster.dir/src/Image.cpp.o.provides.build
.PHONY : CMakeFiles/raster.dir/src/Image.cpp.o.provides

CMakeFiles/raster.dir/src/Image.cpp.o.provides.build: CMakeFiles/raster.dir/src/Image.cpp.o

CMakeFiles/raster.dir/src/main.cpp.o: CMakeFiles/raster.dir/flags.make
CMakeFiles/raster.dir/src/main.cpp.o: ../src/main.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report //home/rablair/cpe471/Prog1/P1RasterBase2016/build/CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/raster.dir/src/main.cpp.o"
	/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/raster.dir/src/main.cpp.o -c //home/rablair/cpe471/Prog1/P1RasterBase2016/src/main.cpp

CMakeFiles/raster.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/raster.dir/src/main.cpp.i"
	/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E //home/rablair/cpe471/Prog1/P1RasterBase2016/src/main.cpp > CMakeFiles/raster.dir/src/main.cpp.i

CMakeFiles/raster.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/raster.dir/src/main.cpp.s"
	/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S //home/rablair/cpe471/Prog1/P1RasterBase2016/src/main.cpp -o CMakeFiles/raster.dir/src/main.cpp.s

CMakeFiles/raster.dir/src/main.cpp.o.requires:
.PHONY : CMakeFiles/raster.dir/src/main.cpp.o.requires

CMakeFiles/raster.dir/src/main.cpp.o.provides: CMakeFiles/raster.dir/src/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/raster.dir/build.make CMakeFiles/raster.dir/src/main.cpp.o.provides.build
.PHONY : CMakeFiles/raster.dir/src/main.cpp.o.provides

CMakeFiles/raster.dir/src/main.cpp.o.provides.build: CMakeFiles/raster.dir/src/main.cpp.o

# Object files for target raster
raster_OBJECTS = \
"CMakeFiles/raster.dir/src/Image.cpp.o" \
"CMakeFiles/raster.dir/src/main.cpp.o"

# External object files for target raster
raster_EXTERNAL_OBJECTS =

raster: CMakeFiles/raster.dir/src/Image.cpp.o
raster: CMakeFiles/raster.dir/src/main.cpp.o
raster: CMakeFiles/raster.dir/build.make
raster: CMakeFiles/raster.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable raster"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/raster.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/raster.dir/build: raster
.PHONY : CMakeFiles/raster.dir/build

CMakeFiles/raster.dir/requires: CMakeFiles/raster.dir/src/Image.cpp.o.requires
CMakeFiles/raster.dir/requires: CMakeFiles/raster.dir/src/main.cpp.o.requires
.PHONY : CMakeFiles/raster.dir/requires

CMakeFiles/raster.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/raster.dir/cmake_clean.cmake
.PHONY : CMakeFiles/raster.dir/clean

CMakeFiles/raster.dir/depend:
	cd //home/rablair/cpe471/Prog1/P1RasterBase2016/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" //home/rablair/cpe471/Prog1/P1RasterBase2016 //home/rablair/cpe471/Prog1/P1RasterBase2016 //home/rablair/cpe471/Prog1/P1RasterBase2016/build //home/rablair/cpe471/Prog1/P1RasterBase2016/build //home/rablair/cpe471/Prog1/P1RasterBase2016/build/CMakeFiles/raster.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/raster.dir/depend

