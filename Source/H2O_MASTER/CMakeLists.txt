cmake_minimum_required(VERSION 3.0.0)

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
list(REMOVE_DUPLICATES CMAKE_MODULE_PATH)

include(CMAW)

# END INSTALL CMAW IF REQUIRED
cmaw_arduinocli_version (version_cmaw)
message("Using CMAW ${version_cmaw}")
message("Updating core index...")
cmaw_update_core_index ()

message("Installing/Updating 'arduino:avr' core...")
cmaw_install_cores (arduino:avr)
cmaw_upgrade_cores (ALL)
message("x")

# TODO encontrar la forma de expandir %localappdata%/Arduino15/

message("localappdata: $ENV{LOCALAPPDATA}\\Arduino15")



set(CMAKE_TOOLCHAIN_FILE ${CMAKE_SOURCE_DIR}/cmake/ArduinoToolchain.cmake)
set(CMAKE_CXX_STANDARD 11)
set(PROJECT_NAME H2O_MASTER)
