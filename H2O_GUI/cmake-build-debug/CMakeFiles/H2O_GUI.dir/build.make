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
CMAKE_SOURCE_DIR = E:\Victor\Documentos\Proyectos\PurifyMyWater\H2O_GUI

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = E:\Victor\Documentos\Proyectos\PurifyMyWater\H2O_GUI\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/H2O_GUI.dir/depend.make
# Include the progress variables for this target.
include CMakeFiles/H2O_GUI.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/H2O_GUI.dir/flags.make

H2O_GUI_h2o_gui.ino.cpp: ../H2O_GUI.ino
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=E:\Victor\Documentos\Proyectos\PurifyMyWater\H2O_GUI\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Regnerating H2O_GUI.ino Sketch"
	"C:\Program Files\JetBrains\CLion 2021.2.1\bin\cmake\win\bin\cmake.exe" E:/Victor/Documentos/Proyectos/PurifyMyWater/H2O_GUI

CMakeFiles/H2O_GUI.dir/H2O_GUI_h2o_gui.ino.cpp.obj: CMakeFiles/H2O_GUI.dir/flags.make
CMakeFiles/H2O_GUI.dir/H2O_GUI_h2o_gui.ino.cpp.obj: H2O_GUI_h2o_gui.ino.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=E:\Victor\Documentos\Proyectos\PurifyMyWater\H2O_GUI\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/H2O_GUI.dir/H2O_GUI_h2o_gui.ino.cpp.obj"
	C:\PROGRA~2\Arduino\hardware\tools\avr\bin\AVR-G_~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\H2O_GUI.dir\H2O_GUI_h2o_gui.ino.cpp.obj -c E:\Victor\Documentos\Proyectos\PurifyMyWater\H2O_GUI\cmake-build-debug\H2O_GUI_h2o_gui.ino.cpp

CMakeFiles/H2O_GUI.dir/H2O_GUI_h2o_gui.ino.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/H2O_GUI.dir/H2O_GUI_h2o_gui.ino.cpp.i"
	C:\PROGRA~2\Arduino\hardware\tools\avr\bin\AVR-G_~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E E:\Victor\Documentos\Proyectos\PurifyMyWater\H2O_GUI\cmake-build-debug\H2O_GUI_h2o_gui.ino.cpp > CMakeFiles\H2O_GUI.dir\H2O_GUI_h2o_gui.ino.cpp.i

CMakeFiles/H2O_GUI.dir/H2O_GUI_h2o_gui.ino.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/H2O_GUI.dir/H2O_GUI_h2o_gui.ino.cpp.s"
	C:\PROGRA~2\Arduino\hardware\tools\avr\bin\AVR-G_~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S E:\Victor\Documentos\Proyectos\PurifyMyWater\H2O_GUI\cmake-build-debug\H2O_GUI_h2o_gui.ino.cpp -o CMakeFiles\H2O_GUI.dir\H2O_GUI_h2o_gui.ino.cpp.s

# Object files for target H2O_GUI
H2O_GUI_OBJECTS = \
"CMakeFiles/H2O_GUI.dir/H2O_GUI_h2o_gui.ino.cpp.obj"

# External object files for target H2O_GUI
H2O_GUI_EXTERNAL_OBJECTS =

H2O_GUI.elf: CMakeFiles/H2O_GUI.dir/H2O_GUI_h2o_gui.ino.cpp.obj
H2O_GUI.elf: CMakeFiles/H2O_GUI.dir/build.make
H2O_GUI.elf: libuno_TouchScreen.a
H2O_GUI.elf: libuno_CORE.a
H2O_GUI.elf: CMakeFiles/H2O_GUI.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=E:\Victor\Documentos\Proyectos\PurifyMyWater\H2O_GUI\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable H2O_GUI.elf"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\H2O_GUI.dir\link.txt --verbose=$(VERBOSE)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold "Generating EEP image"
	"C:\Program Files (x86)\Arduino\hardware\tools\avr\bin\avr-objcopy.exe" -O ihex -j .eeprom --set-section-flags=.eeprom=alloc,load --no-change-warnings --change-section-lma .eeprom=0 E:/Victor/Documentos/Proyectos/PurifyMyWater/H2O_GUI/cmake-build-debug/H2O_GUI.elf E:/Victor/Documentos/Proyectos/PurifyMyWater/H2O_GUI/cmake-build-debug/H2O_GUI.eep
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold "Generating HEX image"
	"C:\Program Files (x86)\Arduino\hardware\tools\avr\bin\avr-objcopy.exe" -O ihex -R .eeprom E:/Victor/Documentos/Proyectos/PurifyMyWater/H2O_GUI/cmake-build-debug/H2O_GUI.elf E:/Victor/Documentos/Proyectos/PurifyMyWater/H2O_GUI/cmake-build-debug/H2O_GUI.hex
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold "Calculating image size"
	"C:\Program Files\JetBrains\CLion 2021.2.1\bin\cmake\win\bin\cmake.exe" -DFIRMWARE_IMAGE=E:/Victor/Documentos/Proyectos/PurifyMyWater/H2O_GUI/cmake-build-debug/H2O_GUI.elf -DMCU=atmega328p -DEEPROM_IMAGE=E:/Victor/Documentos/Proyectos/PurifyMyWater/H2O_GUI/cmake-build-debug/H2O_GUI.eep -P E:/Victor/Documentos/Proyectos/PurifyMyWater/H2O_GUI/cmake-build-debug/CMakeFiles/FirmwareSize.cmake

# Rule to build all files generated by this target.
CMakeFiles/H2O_GUI.dir/build: H2O_GUI.elf
.PHONY : CMakeFiles/H2O_GUI.dir/build

CMakeFiles/H2O_GUI.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\H2O_GUI.dir\cmake_clean.cmake
.PHONY : CMakeFiles/H2O_GUI.dir/clean

CMakeFiles/H2O_GUI.dir/depend: H2O_GUI_h2o_gui.ino.cpp
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" E:\Victor\Documentos\Proyectos\PurifyMyWater\H2O_GUI E:\Victor\Documentos\Proyectos\PurifyMyWater\H2O_GUI E:\Victor\Documentos\Proyectos\PurifyMyWater\H2O_GUI\cmake-build-debug E:\Victor\Documentos\Proyectos\PurifyMyWater\H2O_GUI\cmake-build-debug E:\Victor\Documentos\Proyectos\PurifyMyWater\H2O_GUI\cmake-build-debug\CMakeFiles\H2O_GUI.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/H2O_GUI.dir/depend

