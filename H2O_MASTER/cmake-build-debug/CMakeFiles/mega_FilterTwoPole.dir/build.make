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
CMAKE_COMMAND = "C:\Program Files\JetBrains\CLion 2021.2.1\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\JetBrains\CLion 2021.2.1\bin\cmake\win\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = E:\Victor\Documentos\Proyectos\PurifyMyWater\H2O_MASTER

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = E:\Victor\Documentos\Proyectos\PurifyMyWater\H2O_MASTER\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/mega_FilterTwoPole.dir/depend.make
# Include the progress variables for this target.
include CMakeFiles/mega_FilterTwoPole.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/mega_FilterTwoPole.dir/flags.make

CMakeFiles/mega_FilterTwoPole.dir/libs/Filters/FilterDerivative.cpp.obj: CMakeFiles/mega_FilterTwoPole.dir/flags.make
CMakeFiles/mega_FilterTwoPole.dir/libs/Filters/FilterDerivative.cpp.obj: ../libs/Filters/FilterDerivative.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=E:\Victor\Documentos\Proyectos\PurifyMyWater\H2O_MASTER\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/mega_FilterTwoPole.dir/libs/Filters/FilterDerivative.cpp.obj"
	C:\PROGRA~2\Arduino\hardware\tools\avr\bin\AVR-G_~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\mega_FilterTwoPole.dir\libs\Filters\FilterDerivative.cpp.obj -c E:\Victor\Documentos\Proyectos\PurifyMyWater\H2O_MASTER\libs\Filters\FilterDerivative.cpp

CMakeFiles/mega_FilterTwoPole.dir/libs/Filters/FilterDerivative.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/mega_FilterTwoPole.dir/libs/Filters/FilterDerivative.cpp.i"
	C:\PROGRA~2\Arduino\hardware\tools\avr\bin\AVR-G_~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E E:\Victor\Documentos\Proyectos\PurifyMyWater\H2O_MASTER\libs\Filters\FilterDerivative.cpp > CMakeFiles\mega_FilterTwoPole.dir\libs\Filters\FilterDerivative.cpp.i

CMakeFiles/mega_FilterTwoPole.dir/libs/Filters/FilterDerivative.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/mega_FilterTwoPole.dir/libs/Filters/FilterDerivative.cpp.s"
	C:\PROGRA~2\Arduino\hardware\tools\avr\bin\AVR-G_~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S E:\Victor\Documentos\Proyectos\PurifyMyWater\H2O_MASTER\libs\Filters\FilterDerivative.cpp -o CMakeFiles\mega_FilterTwoPole.dir\libs\Filters\FilterDerivative.cpp.s

CMakeFiles/mega_FilterTwoPole.dir/libs/Filters/FilterOnePole.cpp.obj: CMakeFiles/mega_FilterTwoPole.dir/flags.make
CMakeFiles/mega_FilterTwoPole.dir/libs/Filters/FilterOnePole.cpp.obj: ../libs/Filters/FilterOnePole.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=E:\Victor\Documentos\Proyectos\PurifyMyWater\H2O_MASTER\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/mega_FilterTwoPole.dir/libs/Filters/FilterOnePole.cpp.obj"
	C:\PROGRA~2\Arduino\hardware\tools\avr\bin\AVR-G_~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\mega_FilterTwoPole.dir\libs\Filters\FilterOnePole.cpp.obj -c E:\Victor\Documentos\Proyectos\PurifyMyWater\H2O_MASTER\libs\Filters\FilterOnePole.cpp

CMakeFiles/mega_FilterTwoPole.dir/libs/Filters/FilterOnePole.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/mega_FilterTwoPole.dir/libs/Filters/FilterOnePole.cpp.i"
	C:\PROGRA~2\Arduino\hardware\tools\avr\bin\AVR-G_~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E E:\Victor\Documentos\Proyectos\PurifyMyWater\H2O_MASTER\libs\Filters\FilterOnePole.cpp > CMakeFiles\mega_FilterTwoPole.dir\libs\Filters\FilterOnePole.cpp.i

CMakeFiles/mega_FilterTwoPole.dir/libs/Filters/FilterOnePole.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/mega_FilterTwoPole.dir/libs/Filters/FilterOnePole.cpp.s"
	C:\PROGRA~2\Arduino\hardware\tools\avr\bin\AVR-G_~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S E:\Victor\Documentos\Proyectos\PurifyMyWater\H2O_MASTER\libs\Filters\FilterOnePole.cpp -o CMakeFiles\mega_FilterTwoPole.dir\libs\Filters\FilterOnePole.cpp.s

CMakeFiles/mega_FilterTwoPole.dir/libs/Filters/FilterTwoPole.cpp.obj: CMakeFiles/mega_FilterTwoPole.dir/flags.make
CMakeFiles/mega_FilterTwoPole.dir/libs/Filters/FilterTwoPole.cpp.obj: ../libs/Filters/FilterTwoPole.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=E:\Victor\Documentos\Proyectos\PurifyMyWater\H2O_MASTER\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/mega_FilterTwoPole.dir/libs/Filters/FilterTwoPole.cpp.obj"
	C:\PROGRA~2\Arduino\hardware\tools\avr\bin\AVR-G_~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\mega_FilterTwoPole.dir\libs\Filters\FilterTwoPole.cpp.obj -c E:\Victor\Documentos\Proyectos\PurifyMyWater\H2O_MASTER\libs\Filters\FilterTwoPole.cpp

CMakeFiles/mega_FilterTwoPole.dir/libs/Filters/FilterTwoPole.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/mega_FilterTwoPole.dir/libs/Filters/FilterTwoPole.cpp.i"
	C:\PROGRA~2\Arduino\hardware\tools\avr\bin\AVR-G_~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E E:\Victor\Documentos\Proyectos\PurifyMyWater\H2O_MASTER\libs\Filters\FilterTwoPole.cpp > CMakeFiles\mega_FilterTwoPole.dir\libs\Filters\FilterTwoPole.cpp.i

CMakeFiles/mega_FilterTwoPole.dir/libs/Filters/FilterTwoPole.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/mega_FilterTwoPole.dir/libs/Filters/FilterTwoPole.cpp.s"
	C:\PROGRA~2\Arduino\hardware\tools\avr\bin\AVR-G_~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S E:\Victor\Documentos\Proyectos\PurifyMyWater\H2O_MASTER\libs\Filters\FilterTwoPole.cpp -o CMakeFiles\mega_FilterTwoPole.dir\libs\Filters\FilterTwoPole.cpp.s

CMakeFiles/mega_FilterTwoPole.dir/libs/Filters/RunningStatistics.cpp.obj: CMakeFiles/mega_FilterTwoPole.dir/flags.make
CMakeFiles/mega_FilterTwoPole.dir/libs/Filters/RunningStatistics.cpp.obj: ../libs/Filters/RunningStatistics.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=E:\Victor\Documentos\Proyectos\PurifyMyWater\H2O_MASTER\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/mega_FilterTwoPole.dir/libs/Filters/RunningStatistics.cpp.obj"
	C:\PROGRA~2\Arduino\hardware\tools\avr\bin\AVR-G_~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\mega_FilterTwoPole.dir\libs\Filters\RunningStatistics.cpp.obj -c E:\Victor\Documentos\Proyectos\PurifyMyWater\H2O_MASTER\libs\Filters\RunningStatistics.cpp

CMakeFiles/mega_FilterTwoPole.dir/libs/Filters/RunningStatistics.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/mega_FilterTwoPole.dir/libs/Filters/RunningStatistics.cpp.i"
	C:\PROGRA~2\Arduino\hardware\tools\avr\bin\AVR-G_~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E E:\Victor\Documentos\Proyectos\PurifyMyWater\H2O_MASTER\libs\Filters\RunningStatistics.cpp > CMakeFiles\mega_FilterTwoPole.dir\libs\Filters\RunningStatistics.cpp.i

CMakeFiles/mega_FilterTwoPole.dir/libs/Filters/RunningStatistics.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/mega_FilterTwoPole.dir/libs/Filters/RunningStatistics.cpp.s"
	C:\PROGRA~2\Arduino\hardware\tools\avr\bin\AVR-G_~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S E:\Victor\Documentos\Proyectos\PurifyMyWater\H2O_MASTER\libs\Filters\RunningStatistics.cpp -o CMakeFiles\mega_FilterTwoPole.dir\libs\Filters\RunningStatistics.cpp.s

# Object files for target mega_FilterTwoPole
mega_FilterTwoPole_OBJECTS = \
"CMakeFiles/mega_FilterTwoPole.dir/libs/Filters/FilterDerivative.cpp.obj" \
"CMakeFiles/mega_FilterTwoPole.dir/libs/Filters/FilterOnePole.cpp.obj" \
"CMakeFiles/mega_FilterTwoPole.dir/libs/Filters/FilterTwoPole.cpp.obj" \
"CMakeFiles/mega_FilterTwoPole.dir/libs/Filters/RunningStatistics.cpp.obj"

# External object files for target mega_FilterTwoPole
mega_FilterTwoPole_EXTERNAL_OBJECTS =

libmega_FilterTwoPole.a: CMakeFiles/mega_FilterTwoPole.dir/libs/Filters/FilterDerivative.cpp.obj
libmega_FilterTwoPole.a: CMakeFiles/mega_FilterTwoPole.dir/libs/Filters/FilterOnePole.cpp.obj
libmega_FilterTwoPole.a: CMakeFiles/mega_FilterTwoPole.dir/libs/Filters/FilterTwoPole.cpp.obj
libmega_FilterTwoPole.a: CMakeFiles/mega_FilterTwoPole.dir/libs/Filters/RunningStatistics.cpp.obj
libmega_FilterTwoPole.a: CMakeFiles/mega_FilterTwoPole.dir/build.make
libmega_FilterTwoPole.a: CMakeFiles/mega_FilterTwoPole.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=E:\Victor\Documentos\Proyectos\PurifyMyWater\H2O_MASTER\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Linking CXX static library libmega_FilterTwoPole.a"
	$(CMAKE_COMMAND) -P CMakeFiles\mega_FilterTwoPole.dir\cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\mega_FilterTwoPole.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/mega_FilterTwoPole.dir/build: libmega_FilterTwoPole.a
.PHONY : CMakeFiles/mega_FilterTwoPole.dir/build

CMakeFiles/mega_FilterTwoPole.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\mega_FilterTwoPole.dir\cmake_clean.cmake
.PHONY : CMakeFiles/mega_FilterTwoPole.dir/clean

CMakeFiles/mega_FilterTwoPole.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" E:\Victor\Documentos\Proyectos\PurifyMyWater\H2O_MASTER E:\Victor\Documentos\Proyectos\PurifyMyWater\H2O_MASTER E:\Victor\Documentos\Proyectos\PurifyMyWater\H2O_MASTER\cmake-build-debug E:\Victor\Documentos\Proyectos\PurifyMyWater\H2O_MASTER\cmake-build-debug E:\Victor\Documentos\Proyectos\PurifyMyWater\H2O_MASTER\cmake-build-debug\CMakeFiles\mega_FilterTwoPole.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/mega_FilterTwoPole.dir/depend

