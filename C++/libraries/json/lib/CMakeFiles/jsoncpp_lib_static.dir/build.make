# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.8

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = C:\Users\sebru_000\Desktop\Compilers\cmake\bin\cmake.exe

# The command to remove a file.
RM = C:\Users\sebru_000\Desktop\Compilers\cmake\bin\cmake.exe -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\sebru_000\Desktop\json

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\sebru_000\Desktop\json\include

# Include any dependencies generated for this target.
include src/lib_json/CMakeFiles/jsoncpp_lib_static.dir/depend.make

# Include the progress variables for this target.
include src/lib_json/CMakeFiles/jsoncpp_lib_static.dir/progress.make

# Include the compile flags for this target's objects.
include src/lib_json/CMakeFiles/jsoncpp_lib_static.dir/flags.make

src/lib_json/CMakeFiles/jsoncpp_lib_static.dir/json_reader.cpp.obj: src/lib_json/CMakeFiles/jsoncpp_lib_static.dir/flags.make
src/lib_json/CMakeFiles/jsoncpp_lib_static.dir/json_reader.cpp.obj: src/lib_json/CMakeFiles/jsoncpp_lib_static.dir/includes_CXX.rsp
src/lib_json/CMakeFiles/jsoncpp_lib_static.dir/json_reader.cpp.obj: ../src/lib_json/json_reader.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\sebru_000\Desktop\json\include\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/lib_json/CMakeFiles/jsoncpp_lib_static.dir/json_reader.cpp.obj"
	cd /d C:\Users\sebru_000\Desktop\json\include\src\lib_json && C:\Users\sebru_000\Desktop\Compilers\mingw32\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\jsoncpp_lib_static.dir\json_reader.cpp.obj -c C:\Users\sebru_000\Desktop\json\src\lib_json\json_reader.cpp

src/lib_json/CMakeFiles/jsoncpp_lib_static.dir/json_reader.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/jsoncpp_lib_static.dir/json_reader.cpp.i"
	cd /d C:\Users\sebru_000\Desktop\json\include\src\lib_json && C:\Users\sebru_000\Desktop\Compilers\mingw32\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\sebru_000\Desktop\json\src\lib_json\json_reader.cpp > CMakeFiles\jsoncpp_lib_static.dir\json_reader.cpp.i

src/lib_json/CMakeFiles/jsoncpp_lib_static.dir/json_reader.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/jsoncpp_lib_static.dir/json_reader.cpp.s"
	cd /d C:\Users\sebru_000\Desktop\json\include\src\lib_json && C:\Users\sebru_000\Desktop\Compilers\mingw32\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\sebru_000\Desktop\json\src\lib_json\json_reader.cpp -o CMakeFiles\jsoncpp_lib_static.dir\json_reader.cpp.s

src/lib_json/CMakeFiles/jsoncpp_lib_static.dir/json_reader.cpp.obj.requires:

.PHONY : src/lib_json/CMakeFiles/jsoncpp_lib_static.dir/json_reader.cpp.obj.requires

src/lib_json/CMakeFiles/jsoncpp_lib_static.dir/json_reader.cpp.obj.provides: src/lib_json/CMakeFiles/jsoncpp_lib_static.dir/json_reader.cpp.obj.requires
	$(MAKE) -f src\lib_json\CMakeFiles\jsoncpp_lib_static.dir\build.make src/lib_json/CMakeFiles/jsoncpp_lib_static.dir/json_reader.cpp.obj.provides.build
.PHONY : src/lib_json/CMakeFiles/jsoncpp_lib_static.dir/json_reader.cpp.obj.provides

src/lib_json/CMakeFiles/jsoncpp_lib_static.dir/json_reader.cpp.obj.provides.build: src/lib_json/CMakeFiles/jsoncpp_lib_static.dir/json_reader.cpp.obj


src/lib_json/CMakeFiles/jsoncpp_lib_static.dir/json_value.cpp.obj: src/lib_json/CMakeFiles/jsoncpp_lib_static.dir/flags.make
src/lib_json/CMakeFiles/jsoncpp_lib_static.dir/json_value.cpp.obj: src/lib_json/CMakeFiles/jsoncpp_lib_static.dir/includes_CXX.rsp
src/lib_json/CMakeFiles/jsoncpp_lib_static.dir/json_value.cpp.obj: ../src/lib_json/json_value.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\sebru_000\Desktop\json\include\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object src/lib_json/CMakeFiles/jsoncpp_lib_static.dir/json_value.cpp.obj"
	cd /d C:\Users\sebru_000\Desktop\json\include\src\lib_json && C:\Users\sebru_000\Desktop\Compilers\mingw32\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\jsoncpp_lib_static.dir\json_value.cpp.obj -c C:\Users\sebru_000\Desktop\json\src\lib_json\json_value.cpp

src/lib_json/CMakeFiles/jsoncpp_lib_static.dir/json_value.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/jsoncpp_lib_static.dir/json_value.cpp.i"
	cd /d C:\Users\sebru_000\Desktop\json\include\src\lib_json && C:\Users\sebru_000\Desktop\Compilers\mingw32\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\sebru_000\Desktop\json\src\lib_json\json_value.cpp > CMakeFiles\jsoncpp_lib_static.dir\json_value.cpp.i

src/lib_json/CMakeFiles/jsoncpp_lib_static.dir/json_value.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/jsoncpp_lib_static.dir/json_value.cpp.s"
	cd /d C:\Users\sebru_000\Desktop\json\include\src\lib_json && C:\Users\sebru_000\Desktop\Compilers\mingw32\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\sebru_000\Desktop\json\src\lib_json\json_value.cpp -o CMakeFiles\jsoncpp_lib_static.dir\json_value.cpp.s

src/lib_json/CMakeFiles/jsoncpp_lib_static.dir/json_value.cpp.obj.requires:

.PHONY : src/lib_json/CMakeFiles/jsoncpp_lib_static.dir/json_value.cpp.obj.requires

src/lib_json/CMakeFiles/jsoncpp_lib_static.dir/json_value.cpp.obj.provides: src/lib_json/CMakeFiles/jsoncpp_lib_static.dir/json_value.cpp.obj.requires
	$(MAKE) -f src\lib_json\CMakeFiles\jsoncpp_lib_static.dir\build.make src/lib_json/CMakeFiles/jsoncpp_lib_static.dir/json_value.cpp.obj.provides.build
.PHONY : src/lib_json/CMakeFiles/jsoncpp_lib_static.dir/json_value.cpp.obj.provides

src/lib_json/CMakeFiles/jsoncpp_lib_static.dir/json_value.cpp.obj.provides.build: src/lib_json/CMakeFiles/jsoncpp_lib_static.dir/json_value.cpp.obj


src/lib_json/CMakeFiles/jsoncpp_lib_static.dir/json_writer.cpp.obj: src/lib_json/CMakeFiles/jsoncpp_lib_static.dir/flags.make
src/lib_json/CMakeFiles/jsoncpp_lib_static.dir/json_writer.cpp.obj: src/lib_json/CMakeFiles/jsoncpp_lib_static.dir/includes_CXX.rsp
src/lib_json/CMakeFiles/jsoncpp_lib_static.dir/json_writer.cpp.obj: ../src/lib_json/json_writer.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\sebru_000\Desktop\json\include\CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object src/lib_json/CMakeFiles/jsoncpp_lib_static.dir/json_writer.cpp.obj"
	cd /d C:\Users\sebru_000\Desktop\json\include\src\lib_json && C:\Users\sebru_000\Desktop\Compilers\mingw32\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\jsoncpp_lib_static.dir\json_writer.cpp.obj -c C:\Users\sebru_000\Desktop\json\src\lib_json\json_writer.cpp

src/lib_json/CMakeFiles/jsoncpp_lib_static.dir/json_writer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/jsoncpp_lib_static.dir/json_writer.cpp.i"
	cd /d C:\Users\sebru_000\Desktop\json\include\src\lib_json && C:\Users\sebru_000\Desktop\Compilers\mingw32\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\sebru_000\Desktop\json\src\lib_json\json_writer.cpp > CMakeFiles\jsoncpp_lib_static.dir\json_writer.cpp.i

src/lib_json/CMakeFiles/jsoncpp_lib_static.dir/json_writer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/jsoncpp_lib_static.dir/json_writer.cpp.s"
	cd /d C:\Users\sebru_000\Desktop\json\include\src\lib_json && C:\Users\sebru_000\Desktop\Compilers\mingw32\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\sebru_000\Desktop\json\src\lib_json\json_writer.cpp -o CMakeFiles\jsoncpp_lib_static.dir\json_writer.cpp.s

src/lib_json/CMakeFiles/jsoncpp_lib_static.dir/json_writer.cpp.obj.requires:

.PHONY : src/lib_json/CMakeFiles/jsoncpp_lib_static.dir/json_writer.cpp.obj.requires

src/lib_json/CMakeFiles/jsoncpp_lib_static.dir/json_writer.cpp.obj.provides: src/lib_json/CMakeFiles/jsoncpp_lib_static.dir/json_writer.cpp.obj.requires
	$(MAKE) -f src\lib_json\CMakeFiles\jsoncpp_lib_static.dir\build.make src/lib_json/CMakeFiles/jsoncpp_lib_static.dir/json_writer.cpp.obj.provides.build
.PHONY : src/lib_json/CMakeFiles/jsoncpp_lib_static.dir/json_writer.cpp.obj.provides

src/lib_json/CMakeFiles/jsoncpp_lib_static.dir/json_writer.cpp.obj.provides.build: src/lib_json/CMakeFiles/jsoncpp_lib_static.dir/json_writer.cpp.obj


# Object files for target jsoncpp_lib_static
jsoncpp_lib_static_OBJECTS = \
"CMakeFiles/jsoncpp_lib_static.dir/json_reader.cpp.obj" \
"CMakeFiles/jsoncpp_lib_static.dir/json_value.cpp.obj" \
"CMakeFiles/jsoncpp_lib_static.dir/json_writer.cpp.obj"

# External object files for target jsoncpp_lib_static
jsoncpp_lib_static_EXTERNAL_OBJECTS =

src/lib_json/libjsoncpp.a: src/lib_json/CMakeFiles/jsoncpp_lib_static.dir/json_reader.cpp.obj
src/lib_json/libjsoncpp.a: src/lib_json/CMakeFiles/jsoncpp_lib_static.dir/json_value.cpp.obj
src/lib_json/libjsoncpp.a: src/lib_json/CMakeFiles/jsoncpp_lib_static.dir/json_writer.cpp.obj
src/lib_json/libjsoncpp.a: src/lib_json/CMakeFiles/jsoncpp_lib_static.dir/build.make
src/lib_json/libjsoncpp.a: src/lib_json/CMakeFiles/jsoncpp_lib_static.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\sebru_000\Desktop\json\include\CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX static library libjsoncpp.a"
	cd /d C:\Users\sebru_000\Desktop\json\include\src\lib_json && $(CMAKE_COMMAND) -P CMakeFiles\jsoncpp_lib_static.dir\cmake_clean_target.cmake
	cd /d C:\Users\sebru_000\Desktop\json\include\src\lib_json && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\jsoncpp_lib_static.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/lib_json/CMakeFiles/jsoncpp_lib_static.dir/build: src/lib_json/libjsoncpp.a

.PHONY : src/lib_json/CMakeFiles/jsoncpp_lib_static.dir/build

src/lib_json/CMakeFiles/jsoncpp_lib_static.dir/requires: src/lib_json/CMakeFiles/jsoncpp_lib_static.dir/json_reader.cpp.obj.requires
src/lib_json/CMakeFiles/jsoncpp_lib_static.dir/requires: src/lib_json/CMakeFiles/jsoncpp_lib_static.dir/json_value.cpp.obj.requires
src/lib_json/CMakeFiles/jsoncpp_lib_static.dir/requires: src/lib_json/CMakeFiles/jsoncpp_lib_static.dir/json_writer.cpp.obj.requires

.PHONY : src/lib_json/CMakeFiles/jsoncpp_lib_static.dir/requires

src/lib_json/CMakeFiles/jsoncpp_lib_static.dir/clean:
	cd /d C:\Users\sebru_000\Desktop\json\include\src\lib_json && $(CMAKE_COMMAND) -P CMakeFiles\jsoncpp_lib_static.dir\cmake_clean.cmake
.PHONY : src/lib_json/CMakeFiles/jsoncpp_lib_static.dir/clean

src/lib_json/CMakeFiles/jsoncpp_lib_static.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\sebru_000\Desktop\json C:\Users\sebru_000\Desktop\json\src\lib_json C:\Users\sebru_000\Desktop\json\include C:\Users\sebru_000\Desktop\json\include\src\lib_json C:\Users\sebru_000\Desktop\json\include\src\lib_json\CMakeFiles\jsoncpp_lib_static.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : src/lib_json/CMakeFiles/jsoncpp_lib_static.dir/depend
