# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.31

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
CMAKE_COMMAND = C:\Users\Asus\AppData\Local\Programs\Python\Python313\Lib\site-packages\cmake\data\bin\cmake.exe

# The command to remove a file.
RM = C:\Users\Asus\AppData\Local\Programs\Python\Python313\Lib\site-packages\cmake\data\bin\cmake.exe -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\Asus\Favorites\base

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\Asus\Favorites\base\build-w

# Include any dependencies generated for this target.
include CMakeFiles/exe.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/exe.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/exe.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/exe.dir/flags.make

CMakeFiles/exe.dir/codegen:
.PHONY : CMakeFiles/exe.dir/codegen

CMakeFiles/exe.dir/src/main.c.obj: CMakeFiles/exe.dir/flags.make
CMakeFiles/exe.dir/src/main.c.obj: CMakeFiles/exe.dir/includes_C.rsp
CMakeFiles/exe.dir/src/main.c.obj: C:/Users/Asus/Favorites/base/src/main.c
CMakeFiles/exe.dir/src/main.c.obj: CMakeFiles/exe.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=C:\Users\Asus\Favorites\base\build-w\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/exe.dir/src/main.c.obj"
	C:\msys64\mingw64\bin\cc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/exe.dir/src/main.c.obj -MF CMakeFiles\exe.dir\src\main.c.obj.d -o CMakeFiles\exe.dir\src\main.c.obj -c C:\Users\Asus\Favorites\base\src\main.c

CMakeFiles/exe.dir/src/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/exe.dir/src/main.c.i"
	C:\msys64\mingw64\bin\cc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\Users\Asus\Favorites\base\src\main.c > CMakeFiles\exe.dir\src\main.c.i

CMakeFiles/exe.dir/src/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/exe.dir/src/main.c.s"
	C:\msys64\mingw64\bin\cc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\Users\Asus\Favorites\base\src\main.c -o CMakeFiles\exe.dir\src\main.c.s

# Object files for target exe
exe_OBJECTS = \
"CMakeFiles/exe.dir/src/main.c.obj"

# External object files for target exe
exe_EXTERNAL_OBJECTS =

exe.exe: CMakeFiles/exe.dir/src/main.c.obj
exe.exe: CMakeFiles/exe.dir/build.make
exe.exe: liblib_impl.dll.a
exe.exe: libmalloc_l.dll.a
exe.exe: CMakeFiles/exe.dir/linkLibs.rsp
exe.exe: CMakeFiles/exe.dir/objects1.rsp
exe.exe: CMakeFiles/exe.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=C:\Users\Asus\Favorites\base\build-w\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable exe.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\exe.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/exe.dir/build: exe.exe
.PHONY : CMakeFiles/exe.dir/build

CMakeFiles/exe.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\exe.dir\cmake_clean.cmake
.PHONY : CMakeFiles/exe.dir/clean

CMakeFiles/exe.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\Asus\Favorites\base C:\Users\Asus\Favorites\base C:\Users\Asus\Favorites\base\build-w C:\Users\Asus\Favorites\base\build-w C:\Users\Asus\Favorites\base\build-w\CMakeFiles\exe.dir\DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/exe.dir/depend

