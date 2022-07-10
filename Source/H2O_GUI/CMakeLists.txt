cmake_minimum_required(VERSION 2.8.4)
set(CMAKE_TOOLCHAIN_FILE ${CMAKE_SOURCE_DIR}/cmake/ArduinoToolchain.cmake)
set(CMAKE_CXX_STANDARD 11)
set(PROJECT_NAME H2O_GUI)

set(${PROJECT_NAME}_BOARD mega)
set(ARDUINO_CPU atmega2560)
project(${PROJECT_NAME})

# Define additional source and header files or default arduino sketch files
# set(${PROJECT_NAME}_SRCS)
# set(${PROJECT_NAME}_HDRS)

### Additional static libraries to include in the target.
# set(${PROJECT_NAME}_LIBS)

### Main sketch file
set(${PROJECT_NAME}_SKETCH H2O_GUI.ino)

### Add project directories into the build
# add_subdirectory()

include_directories(Libraries/LCDWIKI_KBV)
include_directories(Libraries/LCDWIKI_GUI)
include_directories(Libraries/TouchScreen)
include_directories(Libraries/SimpleLCDTouchScreen)
include_directories(Shared)
include_directories(UI)
include_directories(UI/Core)
include_directories(UI/Screens)
include_directories(UI/Screens/Menu)
include_directories(UI/Screens/Menu/Settings)
include_directories(UI/Screens/Menu/ExtraFunctions)


### Additional settings to add non-standard or your own Arduino libraries.
# For this example (Libraries will contain additional arduino libraries)
# An Arduino library my_lib will contain files in Libraries/my_lib/: my_lib.h, my_lib.cpp + any other cpp files
# link_directories(${CMAKE_CURRENT_SOURCE_DIR}/)

# For nested library sources replace ${LIB_NAME} with library name for each library
set(_RECURSE true)

#### Additional settings for programmer. From programmers.txt
set(${PROJECT_NAME}_PROGRAMMER avrisp)
# set(${PROJECT_NAME}_PORT /dev/cu.usbserial-00000000)
# set(mega.upload.speed 9600)

## Verbose build process
set(${PROJECT_NAME}_AFLAGS -v)

generate_arduino_firmware(${PROJECT_NAME})


print_board_list()
print_programmer_list()
