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
CMAKE_SOURCE_DIR = //home/rablair/cpe471/Lab07/L07

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = //home/rablair/cpe471/Lab07/L07/build

# Include any dependencies generated for this target.
include CMakeFiles/lab7.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/lab7.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/lab7.dir/flags.make

CMakeFiles/lab7.dir/src/GLSL.cpp.o: CMakeFiles/lab7.dir/flags.make
CMakeFiles/lab7.dir/src/GLSL.cpp.o: ../src/GLSL.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report //home/rablair/cpe471/Lab07/L07/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/lab7.dir/src/GLSL.cpp.o"
	/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/lab7.dir/src/GLSL.cpp.o -c //home/rablair/cpe471/Lab07/L07/src/GLSL.cpp

CMakeFiles/lab7.dir/src/GLSL.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/lab7.dir/src/GLSL.cpp.i"
	/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E //home/rablair/cpe471/Lab07/L07/src/GLSL.cpp > CMakeFiles/lab7.dir/src/GLSL.cpp.i

CMakeFiles/lab7.dir/src/GLSL.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/lab7.dir/src/GLSL.cpp.s"
	/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S //home/rablair/cpe471/Lab07/L07/src/GLSL.cpp -o CMakeFiles/lab7.dir/src/GLSL.cpp.s

CMakeFiles/lab7.dir/src/GLSL.cpp.o.requires:
.PHONY : CMakeFiles/lab7.dir/src/GLSL.cpp.o.requires

CMakeFiles/lab7.dir/src/GLSL.cpp.o.provides: CMakeFiles/lab7.dir/src/GLSL.cpp.o.requires
	$(MAKE) -f CMakeFiles/lab7.dir/build.make CMakeFiles/lab7.dir/src/GLSL.cpp.o.provides.build
.PHONY : CMakeFiles/lab7.dir/src/GLSL.cpp.o.provides

CMakeFiles/lab7.dir/src/GLSL.cpp.o.provides.build: CMakeFiles/lab7.dir/src/GLSL.cpp.o

CMakeFiles/lab7.dir/src/main.cpp.o: CMakeFiles/lab7.dir/flags.make
CMakeFiles/lab7.dir/src/main.cpp.o: ../src/main.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report //home/rablair/cpe471/Lab07/L07/build/CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/lab7.dir/src/main.cpp.o"
	/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/lab7.dir/src/main.cpp.o -c //home/rablair/cpe471/Lab07/L07/src/main.cpp

CMakeFiles/lab7.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/lab7.dir/src/main.cpp.i"
	/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E //home/rablair/cpe471/Lab07/L07/src/main.cpp > CMakeFiles/lab7.dir/src/main.cpp.i

CMakeFiles/lab7.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/lab7.dir/src/main.cpp.s"
	/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S //home/rablair/cpe471/Lab07/L07/src/main.cpp -o CMakeFiles/lab7.dir/src/main.cpp.s

CMakeFiles/lab7.dir/src/main.cpp.o.requires:
.PHONY : CMakeFiles/lab7.dir/src/main.cpp.o.requires

CMakeFiles/lab7.dir/src/main.cpp.o.provides: CMakeFiles/lab7.dir/src/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/lab7.dir/build.make CMakeFiles/lab7.dir/src/main.cpp.o.provides.build
.PHONY : CMakeFiles/lab7.dir/src/main.cpp.o.provides

CMakeFiles/lab7.dir/src/main.cpp.o.provides.build: CMakeFiles/lab7.dir/src/main.cpp.o

CMakeFiles/lab7.dir/src/MatrixStack.cpp.o: CMakeFiles/lab7.dir/flags.make
CMakeFiles/lab7.dir/src/MatrixStack.cpp.o: ../src/MatrixStack.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report //home/rablair/cpe471/Lab07/L07/build/CMakeFiles $(CMAKE_PROGRESS_3)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/lab7.dir/src/MatrixStack.cpp.o"
	/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/lab7.dir/src/MatrixStack.cpp.o -c //home/rablair/cpe471/Lab07/L07/src/MatrixStack.cpp

CMakeFiles/lab7.dir/src/MatrixStack.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/lab7.dir/src/MatrixStack.cpp.i"
	/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E //home/rablair/cpe471/Lab07/L07/src/MatrixStack.cpp > CMakeFiles/lab7.dir/src/MatrixStack.cpp.i

CMakeFiles/lab7.dir/src/MatrixStack.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/lab7.dir/src/MatrixStack.cpp.s"
	/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S //home/rablair/cpe471/Lab07/L07/src/MatrixStack.cpp -o CMakeFiles/lab7.dir/src/MatrixStack.cpp.s

CMakeFiles/lab7.dir/src/MatrixStack.cpp.o.requires:
.PHONY : CMakeFiles/lab7.dir/src/MatrixStack.cpp.o.requires

CMakeFiles/lab7.dir/src/MatrixStack.cpp.o.provides: CMakeFiles/lab7.dir/src/MatrixStack.cpp.o.requires
	$(MAKE) -f CMakeFiles/lab7.dir/build.make CMakeFiles/lab7.dir/src/MatrixStack.cpp.o.provides.build
.PHONY : CMakeFiles/lab7.dir/src/MatrixStack.cpp.o.provides

CMakeFiles/lab7.dir/src/MatrixStack.cpp.o.provides.build: CMakeFiles/lab7.dir/src/MatrixStack.cpp.o

CMakeFiles/lab7.dir/src/Program.cpp.o: CMakeFiles/lab7.dir/flags.make
CMakeFiles/lab7.dir/src/Program.cpp.o: ../src/Program.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report //home/rablair/cpe471/Lab07/L07/build/CMakeFiles $(CMAKE_PROGRESS_4)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/lab7.dir/src/Program.cpp.o"
	/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/lab7.dir/src/Program.cpp.o -c //home/rablair/cpe471/Lab07/L07/src/Program.cpp

CMakeFiles/lab7.dir/src/Program.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/lab7.dir/src/Program.cpp.i"
	/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E //home/rablair/cpe471/Lab07/L07/src/Program.cpp > CMakeFiles/lab7.dir/src/Program.cpp.i

CMakeFiles/lab7.dir/src/Program.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/lab7.dir/src/Program.cpp.s"
	/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S //home/rablair/cpe471/Lab07/L07/src/Program.cpp -o CMakeFiles/lab7.dir/src/Program.cpp.s

CMakeFiles/lab7.dir/src/Program.cpp.o.requires:
.PHONY : CMakeFiles/lab7.dir/src/Program.cpp.o.requires

CMakeFiles/lab7.dir/src/Program.cpp.o.provides: CMakeFiles/lab7.dir/src/Program.cpp.o.requires
	$(MAKE) -f CMakeFiles/lab7.dir/build.make CMakeFiles/lab7.dir/src/Program.cpp.o.provides.build
.PHONY : CMakeFiles/lab7.dir/src/Program.cpp.o.provides

CMakeFiles/lab7.dir/src/Program.cpp.o.provides.build: CMakeFiles/lab7.dir/src/Program.cpp.o

CMakeFiles/lab7.dir/src/Shape.cpp.o: CMakeFiles/lab7.dir/flags.make
CMakeFiles/lab7.dir/src/Shape.cpp.o: ../src/Shape.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report //home/rablair/cpe471/Lab07/L07/build/CMakeFiles $(CMAKE_PROGRESS_5)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/lab7.dir/src/Shape.cpp.o"
	/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/lab7.dir/src/Shape.cpp.o -c //home/rablair/cpe471/Lab07/L07/src/Shape.cpp

CMakeFiles/lab7.dir/src/Shape.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/lab7.dir/src/Shape.cpp.i"
	/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E //home/rablair/cpe471/Lab07/L07/src/Shape.cpp > CMakeFiles/lab7.dir/src/Shape.cpp.i

CMakeFiles/lab7.dir/src/Shape.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/lab7.dir/src/Shape.cpp.s"
	/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S //home/rablair/cpe471/Lab07/L07/src/Shape.cpp -o CMakeFiles/lab7.dir/src/Shape.cpp.s

CMakeFiles/lab7.dir/src/Shape.cpp.o.requires:
.PHONY : CMakeFiles/lab7.dir/src/Shape.cpp.o.requires

CMakeFiles/lab7.dir/src/Shape.cpp.o.provides: CMakeFiles/lab7.dir/src/Shape.cpp.o.requires
	$(MAKE) -f CMakeFiles/lab7.dir/build.make CMakeFiles/lab7.dir/src/Shape.cpp.o.provides.build
.PHONY : CMakeFiles/lab7.dir/src/Shape.cpp.o.provides

CMakeFiles/lab7.dir/src/Shape.cpp.o.provides.build: CMakeFiles/lab7.dir/src/Shape.cpp.o

# Object files for target lab7
lab7_OBJECTS = \
"CMakeFiles/lab7.dir/src/GLSL.cpp.o" \
"CMakeFiles/lab7.dir/src/main.cpp.o" \
"CMakeFiles/lab7.dir/src/MatrixStack.cpp.o" \
"CMakeFiles/lab7.dir/src/Program.cpp.o" \
"CMakeFiles/lab7.dir/src/Shape.cpp.o"

# External object files for target lab7
lab7_EXTERNAL_OBJECTS =

lab7: CMakeFiles/lab7.dir/src/GLSL.cpp.o
lab7: CMakeFiles/lab7.dir/src/main.cpp.o
lab7: CMakeFiles/lab7.dir/src/MatrixStack.cpp.o
lab7: CMakeFiles/lab7.dir/src/Program.cpp.o
lab7: CMakeFiles/lab7.dir/src/Shape.cpp.o
lab7: CMakeFiles/lab7.dir/build.make
lab7: //home/rablair/lib/glfw-3.1.2/debug/src/libglfw3.a
lab7: /usr/lib64/librt.so
lab7: /usr/lib64/libm.so
lab7: /usr/lib64/libX11.so
lab7: /usr/lib64/libXrandr.so
lab7: /usr/lib64/libXinerama.so
lab7: /usr/lib64/libXi.so
lab7: /usr/lib64/libXxf86vm.so
lab7: /usr/lib64/libXcursor.so
lab7: /usr/lib64/libGL.so
lab7: /home/rablair/lib/glew-2.0.0/lib/libGLEW.a
lab7: CMakeFiles/lab7.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable lab7"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/lab7.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/lab7.dir/build: lab7
.PHONY : CMakeFiles/lab7.dir/build

CMakeFiles/lab7.dir/requires: CMakeFiles/lab7.dir/src/GLSL.cpp.o.requires
CMakeFiles/lab7.dir/requires: CMakeFiles/lab7.dir/src/main.cpp.o.requires
CMakeFiles/lab7.dir/requires: CMakeFiles/lab7.dir/src/MatrixStack.cpp.o.requires
CMakeFiles/lab7.dir/requires: CMakeFiles/lab7.dir/src/Program.cpp.o.requires
CMakeFiles/lab7.dir/requires: CMakeFiles/lab7.dir/src/Shape.cpp.o.requires
.PHONY : CMakeFiles/lab7.dir/requires

CMakeFiles/lab7.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/lab7.dir/cmake_clean.cmake
.PHONY : CMakeFiles/lab7.dir/clean

CMakeFiles/lab7.dir/depend:
	cd //home/rablair/cpe471/Lab07/L07/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" //home/rablair/cpe471/Lab07/L07 //home/rablair/cpe471/Lab07/L07 //home/rablair/cpe471/Lab07/L07/build //home/rablair/cpe471/Lab07/L07/build //home/rablair/cpe471/Lab07/L07/build/CMakeFiles/lab7.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/lab7.dir/depend

