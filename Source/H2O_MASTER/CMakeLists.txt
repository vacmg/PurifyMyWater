cmake_minimum_required(VERSION 3.0.0)

#[[ project(H2O_MASTER)

# CONFIG

set(CMAKE_TOOLCHAIN_FILE ${CMAKE_SOURCE_DIR}/cmake/ArduinoToolchain.cmake)
set(CMAKE_CXX_STANDARD 11)
set(PROJECT_NAME H2O_MASTER)

set(arduino_board_vendor arduino)
set(arduino_board_arch avr)
set(arduino_board mega)
set(arduino_board_cpu cpu=atmega2560)

#END CONFIG

# INSTALL CMAW IF REQUIRED
set (CMAW_URL "https://github.com/AeroStun/CMAW/raw/v0.1.3/CMAW.cmake")
set (CMAW_RUNDIR "${CMAKE_BINARY_DIR}/runmodules")
set (CMAW_RUNLOC "${CMAW_RUNDIR}/CMAW.cmake")
if (NOT EXISTS "${CMAW_RUNLOC}")
    file (MAKE_DIRECTORY "${CMAW_RUNDIR}")
    file (DOWNLOAD "${CMAW_URL}" "${CMAW_RUNLOC}")
    list (APPEND CMAKE_MODULE_PATH "${CMAW_RUNDIR}")
endif ()

list (APPEND CMAKE_MODULE_PATH "${CMAW_RUNDIR}")
list (REMOVE_DUPLICATES CMAKE_MODULE_PATH)

include(CMAW) #]]

# END INSTALL CMAW IF REQUIRED

#[[ INSTALL/UPDATE ARDUINO_CORE
cmaw_arduinocli_version (version_cmaw)
message("Using Arduino_CLI ${version_cmaw}")
message("Updating core index...")
cmaw_update_core_index ()

message("Installing/Updating '${arduino_board_vendor}:${arduino_board_arch}' core...")
cmaw_install_cores (${arduino_board_vendor}:${arduino_board_arch})
cmaw_upgrade_cores (ALL)

# END INSTALL/UPDATE ARDUINO_CORE #]]

# DEFINE INCLUDE MACROS
#[[
MACRO(SOURCE_FILES sources_dir_list sources_return_list)
    MESSAGE("Processing Source Files")
    SET(sources_list "")
    FOREACH(dir ${${sources_dir_list}})
        MESSAGE("Processing source directory: " ${dir})
        SET(new_list "")
        FILE(GLOB_RECURSE new_list ${dir}/*.cpp)
        SET(sources_list ${sources_list} ${new_list})
    ENDFOREACH()
    SET(${sources_return_list} ${sources_list})
    MESSAGE("DONE")
ENDMACRO()

MACRO(HEADER_DIRECTORIES header_dir_list header_return_list)
    MESSAGE("Processing Header Files")
    SET(headers_list "")
    FOREACH(dir ${${header_dir_list}})
        MESSAGE("Processing header directory: " ${dir})
        SET(new_list "")
        FILE(GLOB_RECURSE new_list ${dir}/*.h)
        FOREACH(file_path ${new_list})
            GET_FILENAME_COMPONENT(dir_path ${file_path} PATH)
            SET(headers_list ${headers_list} ${dir_path})
        ENDFOREACH()
        LIST(REMOVE_DUPLICATES headers_list)
    ENDFOREACH()
    SET(${header_return_list} ${headers_list})
    MESSAGE("DONE\n")
ENDMACRO()

# END DEFINE INCLUDE MACROS

# SET SDK PATH

if(UNIX)
    set(arduino_main_path $ENV{HOME}/.arduino15)
    message("Using UNIX arduino path: ${arduino_main_path}")
elseif(WIN32)
    set(arduino_main_path $ENV{LOCALAPPDATA}\\Arduino15)
    message("Using WIN32 arduino path: ${arduino_main_path}")
endif()

FILE(TO_CMAKE_PATH ${arduino_main_path} arduino_main_path)
set(usr_libs ${arduino_main_path}/libraries)

set(include_files_dir_list "")
LIST(APPEND include_files_dir_list ${usr_libs})

if(${arduino_board_arch} STREQUAL avr)
    LIST(APPEND include_files_dir_list ${arduino_main_path}/packages/arduino/tools/avr-gcc ${arduino_main_path}//packages/arduino/hardware/avr)
    message("include_files_dir_list: ${include_files_dir_list}")
elseif(TRUE)
    message(FATAL_ERROR "ARCH '${arduino_board_arch}' NOT SUPPORTED YET")
endif() #]]

# END SET SDK PATH

# Define CMake's minimum version (must-do) and the project's name and supported languages
cmake_minimum_required(VERSION 3.8.2)
set(CMAKE_TOOLCHAIN_FILE ${CMAKE_SOURCE_DIR}/cmake/Arduino-Toolchain.cmake)
include(cmake/Arduino-Toolchain.cmake)
project(H2O_MASTER)

# Call a framework utility function, passing it information about the hardware board that will be used - This function returns a structure known only to the framework
get_board_id(board_id mega atmega2560)

# Create an executable suitable for Arduino using CMake-style target-creation
add_arduino_executable(Hello_World ${board_id} helloWorld.cpp)
# Upload the created target through a connected Serial Port (Where your board is connected to)
# upload_arduino_target(Hello_World "${board_id}" COM3)

#TODO mirar aqui: ./cmake/Platform/Other/ArduinoSDKSeeker.cmake
