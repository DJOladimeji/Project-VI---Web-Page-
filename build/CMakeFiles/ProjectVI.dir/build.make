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
CMAKE_SOURCE_DIR = /SharedWebserver

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /SharedWebserver/build

# Include any dependencies generated for this target.
include CMakeFiles/ProjectVI.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/ProjectVI.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/ProjectVI.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/ProjectVI.dir/flags.make

CMakeFiles/ProjectVI.dir/main.cpp.o: CMakeFiles/ProjectVI.dir/flags.make
CMakeFiles/ProjectVI.dir/main.cpp.o: ../main.cpp
CMakeFiles/ProjectVI.dir/main.cpp.o: CMakeFiles/ProjectVI.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/SharedWebserver/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/ProjectVI.dir/main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/ProjectVI.dir/main.cpp.o -MF CMakeFiles/ProjectVI.dir/main.cpp.o.d -o CMakeFiles/ProjectVI.dir/main.cpp.o -c /SharedWebserver/main.cpp

CMakeFiles/ProjectVI.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ProjectVI.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /SharedWebserver/main.cpp > CMakeFiles/ProjectVI.dir/main.cpp.i

CMakeFiles/ProjectVI.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ProjectVI.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /SharedWebserver/main.cpp -o CMakeFiles/ProjectVI.dir/main.cpp.s

CMakeFiles/ProjectVI.dir/DB.cpp.o: CMakeFiles/ProjectVI.dir/flags.make
CMakeFiles/ProjectVI.dir/DB.cpp.o: ../DB.cpp
CMakeFiles/ProjectVI.dir/DB.cpp.o: CMakeFiles/ProjectVI.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/SharedWebserver/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/ProjectVI.dir/DB.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/ProjectVI.dir/DB.cpp.o -MF CMakeFiles/ProjectVI.dir/DB.cpp.o.d -o CMakeFiles/ProjectVI.dir/DB.cpp.o -c /SharedWebserver/DB.cpp

CMakeFiles/ProjectVI.dir/DB.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ProjectVI.dir/DB.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /SharedWebserver/DB.cpp > CMakeFiles/ProjectVI.dir/DB.cpp.i

CMakeFiles/ProjectVI.dir/DB.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ProjectVI.dir/DB.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /SharedWebserver/DB.cpp -o CMakeFiles/ProjectVI.dir/DB.cpp.s

CMakeFiles/ProjectVI.dir/Tasks.cpp.o: CMakeFiles/ProjectVI.dir/flags.make
CMakeFiles/ProjectVI.dir/Tasks.cpp.o: ../Tasks.cpp
CMakeFiles/ProjectVI.dir/Tasks.cpp.o: CMakeFiles/ProjectVI.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/SharedWebserver/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/ProjectVI.dir/Tasks.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/ProjectVI.dir/Tasks.cpp.o -MF CMakeFiles/ProjectVI.dir/Tasks.cpp.o.d -o CMakeFiles/ProjectVI.dir/Tasks.cpp.o -c /SharedWebserver/Tasks.cpp

CMakeFiles/ProjectVI.dir/Tasks.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ProjectVI.dir/Tasks.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /SharedWebserver/Tasks.cpp > CMakeFiles/ProjectVI.dir/Tasks.cpp.i

CMakeFiles/ProjectVI.dir/Tasks.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ProjectVI.dir/Tasks.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /SharedWebserver/Tasks.cpp -o CMakeFiles/ProjectVI.dir/Tasks.cpp.s

CMakeFiles/ProjectVI.dir/User.cpp.o: CMakeFiles/ProjectVI.dir/flags.make
CMakeFiles/ProjectVI.dir/User.cpp.o: ../User.cpp
CMakeFiles/ProjectVI.dir/User.cpp.o: CMakeFiles/ProjectVI.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/SharedWebserver/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/ProjectVI.dir/User.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/ProjectVI.dir/User.cpp.o -MF CMakeFiles/ProjectVI.dir/User.cpp.o.d -o CMakeFiles/ProjectVI.dir/User.cpp.o -c /SharedWebserver/User.cpp

CMakeFiles/ProjectVI.dir/User.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ProjectVI.dir/User.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /SharedWebserver/User.cpp > CMakeFiles/ProjectVI.dir/User.cpp.i

CMakeFiles/ProjectVI.dir/User.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ProjectVI.dir/User.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /SharedWebserver/User.cpp -o CMakeFiles/ProjectVI.dir/User.cpp.s

# Object files for target ProjectVI
ProjectVI_OBJECTS = \
"CMakeFiles/ProjectVI.dir/main.cpp.o" \
"CMakeFiles/ProjectVI.dir/DB.cpp.o" \
"CMakeFiles/ProjectVI.dir/Tasks.cpp.o" \
"CMakeFiles/ProjectVI.dir/User.cpp.o"

# External object files for target ProjectVI
ProjectVI_EXTERNAL_OBJECTS =

ProjectVI: CMakeFiles/ProjectVI.dir/main.cpp.o
ProjectVI: CMakeFiles/ProjectVI.dir/DB.cpp.o
ProjectVI: CMakeFiles/ProjectVI.dir/Tasks.cpp.o
ProjectVI: CMakeFiles/ProjectVI.dir/User.cpp.o
ProjectVI: CMakeFiles/ProjectVI.dir/build.make
ProjectVI: /usr/lib/x86_64-linux-gnu/libboost_system.so.1.74.0
ProjectVI: /usr/lib/x86_64-linux-gnu/libboost_filesystem.so.1.74.0
ProjectVI: CMakeFiles/ProjectVI.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/SharedWebserver/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Linking CXX executable ProjectVI"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/ProjectVI.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/ProjectVI.dir/build: ProjectVI
.PHONY : CMakeFiles/ProjectVI.dir/build

CMakeFiles/ProjectVI.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/ProjectVI.dir/cmake_clean.cmake
.PHONY : CMakeFiles/ProjectVI.dir/clean

CMakeFiles/ProjectVI.dir/depend:
	cd /SharedWebserver/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /SharedWebserver /SharedWebserver /SharedWebserver/build /SharedWebserver/build /SharedWebserver/build/CMakeFiles/ProjectVI.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/ProjectVI.dir/depend

