# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.20

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\JetBrains\CLion 2021.2.3\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\JetBrains\CLion 2021.2.3\bin\cmake\win\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "C:\Users\Diogo Babo\Desktop\Projeto2_AED"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "C:\Users\Diogo Babo\Desktop\Projeto2_AED\cmake-build-debug"

# Include any dependencies generated for this target.
include CMakeFiles/Projeto2_AED.dir/depend.make
# Include the progress variables for this target.
include CMakeFiles/Projeto2_AED.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Projeto2_AED.dir/flags.make

CMakeFiles/Projeto2_AED.dir/main.cpp.obj: CMakeFiles/Projeto2_AED.dir/flags.make
CMakeFiles/Projeto2_AED.dir/main.cpp.obj: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="C:\Users\Diogo Babo\Desktop\Projeto2_AED\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Projeto2_AED.dir/main.cpp.obj"
	C:\PROGRA~1\MINGW-~1\X86_64~1.0-P\mingw64\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\Projeto2_AED.dir\main.cpp.obj -c "C:\Users\Diogo Babo\Desktop\Projeto2_AED\main.cpp"

CMakeFiles/Projeto2_AED.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Projeto2_AED.dir/main.cpp.i"
	C:\PROGRA~1\MINGW-~1\X86_64~1.0-P\mingw64\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "C:\Users\Diogo Babo\Desktop\Projeto2_AED\main.cpp" > CMakeFiles\Projeto2_AED.dir\main.cpp.i

CMakeFiles/Projeto2_AED.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Projeto2_AED.dir/main.cpp.s"
	C:\PROGRA~1\MINGW-~1\X86_64~1.0-P\mingw64\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "C:\Users\Diogo Babo\Desktop\Projeto2_AED\main.cpp" -o CMakeFiles\Projeto2_AED.dir\main.cpp.s

# Object files for target Projeto2_AED
Projeto2_AED_OBJECTS = \
"CMakeFiles/Projeto2_AED.dir/main.cpp.obj"

# External object files for target Projeto2_AED
Projeto2_AED_EXTERNAL_OBJECTS =

Projeto2_AED.exe: CMakeFiles/Projeto2_AED.dir/main.cpp.obj
Projeto2_AED.exe: CMakeFiles/Projeto2_AED.dir/build.make
Projeto2_AED.exe: CMakeFiles/Projeto2_AED.dir/linklibs.rsp
Projeto2_AED.exe: CMakeFiles/Projeto2_AED.dir/objects1.rsp
Projeto2_AED.exe: CMakeFiles/Projeto2_AED.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="C:\Users\Diogo Babo\Desktop\Projeto2_AED\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable Projeto2_AED.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\Projeto2_AED.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Projeto2_AED.dir/build: Projeto2_AED.exe
.PHONY : CMakeFiles/Projeto2_AED.dir/build

CMakeFiles/Projeto2_AED.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\Projeto2_AED.dir\cmake_clean.cmake
.PHONY : CMakeFiles/Projeto2_AED.dir/clean

CMakeFiles/Projeto2_AED.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" "C:\Users\Diogo Babo\Desktop\Projeto2_AED" "C:\Users\Diogo Babo\Desktop\Projeto2_AED" "C:\Users\Diogo Babo\Desktop\Projeto2_AED\cmake-build-debug" "C:\Users\Diogo Babo\Desktop\Projeto2_AED\cmake-build-debug" "C:\Users\Diogo Babo\Desktop\Projeto2_AED\cmake-build-debug\CMakeFiles\Projeto2_AED.dir\DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/Projeto2_AED.dir/depend
