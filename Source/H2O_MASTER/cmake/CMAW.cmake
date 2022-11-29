# Copyright 2020 AeroStun <_as@aerostun.dev>
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

include_guard (DIRECTORY)
cmake_policy (SET CMP0007 NEW)

set (CMAW_VERSION "0.1.3")

set (CMAW_ARDUINOCLI_DL_VERSION      "latest" CACHE STRING   "arduino-cli version to use if there is need to download it")
set (CMAW_ARDUINOCLI_BINARY_LOCATION ""       CACHE FILEPATH "Path to an existing arduino-cli binary on disk; empty to autodetect")
set (CMAW_ARDUINOCLI_BINARY_NOSYSTEM OFF      CACHE BOOL     "When enabled, CMAW will skip searching for arduino-cli on the system")
set (CMAW_AUTO_PATH                  ""       CACHE FILEPATH "Directory where CMAW can self-manage an ArduinoCLI installation")
set (CMAW_ARDUINOCLI_CONFIG_FILEPATH ""       CACHE FILEPATH "The custom config file (if not specified the default will be used).")
set (CMAW_ARDUINOCLI_EXTRA_BOARD_URL ""       CACHE STRING   "Additional URLs for the board manager.")

cmake_host_system_information (RESULT CMAW_INTERNAL_HOST_64BIT QUERY IS_64BIT)
if (CMAW_INTERNAL_HOST_64BIT)
  set (CMAW_INTERNAL_HOST_BITNESS 64)
else ()
  set (CMAW_INTERNAL_HOST_BITNESS 32)
endif ()

function (cmaw_internal_build_ardcli_downloadurl ARDCLI_VERSION)
  if (DEFINED CMAW_INTERNAL_ARDCLI_DOWNLOAD_URL)
    return ()
  endif ()

  set (STEM "https://downloads.arduino.cc/arduino-cli/")
  
  if (WIN32)
    set (FILENAME "arduino-cli_${ARDCLI_VERSION}_Windows_${CMAW_INTERNAL_HOST_BITNESS}bit.zip")
  elseif (APPLE)
    if (CMAW_INTERNAL_HOST_BITNESS EQUAL 32)
      message (FATAL_ERROR "Your system appears to be 32bits. arduino-cli does not provide prebuilts for your platform.")
    endif ()
    set (FILENAME "arduino-cli_${ARDCLI_VERSION}_Windows_${CMAW_INTERNAL_HOST_BITNESS}bit.tar.gz")
  elseif (UNIX)
    if (NOT ${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
      message (FATAL_ERROR "arduino-cli does not provide prebuilts for free operating systems other than Linux-based ones")
    endif ()
    
    string (FIND "${CMAKE_HOST_SYSTEM_PROCESSOR}" "x86" IS_X86)
    string (FIND "${CMAKE_HOST_SYSTEM_PROCESSOR}" "arm" IS_ARM)
    
    if (IS_X86)
      set (FILENAME "arduino-cli_${ARDCLI_VERSION}_Linux_${CMAW_INTERNAL_HOST_BITNESS}bit.tar.gz")
    elseif (IS_ARM)
      if (CMAW_INTERNAL_HOST_BITNESS EQUAL 64)
        set (FILENAME "arduino-cli_${ARDCLI_VERSION}_Linux_ARM64.tar.gz")
      else ()
        set (FILENAME "arduino-cli_${ARDCLI_VERSION}_Linux_ARMv7.tar.gz")
      endif ()
    else ()
      message (FATAL_ERROR "Unsupported platform/architecture (found \"${CMAKE_HOST_SYSTEM_PROCESSOR}\", which does not seem to be x86 or ARM)")
    endif ()
  endif ()

  set (CMAW_INTERNAL_ARDCLI_DOWNLOAD_FILENAME "${FILENAME}" PARENT_SCOPE)
  set (CMAW_INTERNAL_ARDCLI_DOWNLOAD_URL "${STEM}${FILENAME}" PARENT_SCOPE)
endfunction ()

macro (cmaw_internal_bootstrap)
  if (CMAW_ARDUINOCLI_BINARY_LOCATION)
    if (NOT EXISTS ${CMAW_ARDUINOCLI_BINARY_LOCATION})
      message (FATAL_ERROR "CMAW_ARDUINOCLI_BINARY_LOCATION set but no such file exists (value was \"${CMAW_ARDUINOCLI_BINARY_LOCATION}\")")
    endif ()
    if (IS_DIRECTORY ${CMAW_ARDUINOCLI_BINARY_LOCATION})
      message (FATAL_ERROR "CMAW_ARDUINOCLI_BINARY_LOCATION set but points to a directory (value was \"${CMAW_ARDUINOCLI_BINARY_LOCATION}\")")
    endif ()
    if (IS_SYMLINK ${CMAW_ARDUINOCLI_BINARY_LOCATION})
      file (READ_SYMLINK ${CMAW_ARDUINOCLI_BINARY_LOCATION} CMAW_ARDUINOCLI_BINARY_LOCATION_DIRECT_ABS) # Warning: does not check nested symlinks
      if (NOT EXISTS ${CMAW_ARDUINOCLI_BINARY_LOCATION_DIRECT_ABS})
        message (FATAL_ERROR "CMAW_ARDUINOCLI_BINARY_LOCATION set to a broken symlink (value was \"${CMAW_ARDUINOCLI_BINARY_LOCATION}\")")
      endif ()
      if (IS_DIRECTORY ${CMAW_ARDUINOCLI_BINARY_LOCATION_DIRECT_ABS})
        message (FATAL_ERROR "CMAW_ARDUINOCLI_BINARY_LOCATION set but points [via a symlink] to a directory (value was \"${CMAW_ARDUINOCLI_BINARY_LOCATION}\")")
      endif ()
    endif ()
    #FIXME check that the binary is valid (by invoking the version subcommand?)
    message ("User-provided binary OK")
    mark_as_advanced (CMAW_ARDUINOCLI_BINARY_LOCATION)
  endif ()

  if (NOT CMAW_ARDUINOCLI_BINARY_NOSYSTEM AND NOT CMAW_ARDUINOCLI_BINARY_LOCATION)
    find_program (ARDUINO_CLI_PATH "arduino-cli")
    if (ARDUINO_CLI_PATH)
      message (STATUS "Found local system installation of arduino-cli")
      message (VERBOSE "(at \"${ARDUINO_CLI_PATH}\")")
      set (CMAW_ARDUINOCLI_BINARY_LOCATION "${ARDUINO_CLI_PATH}")
    endif ()
  endif ()

  if (NOT CMAW_ARDUINOCLI_BINARY_LOCATION)
    if (NOT CMAKE_SCRIPT_MODE_FILE)
      set (CMAW_AUTO_PATH "${CMAKE_BINARY_DIR}")
    elseif (NOT CMAW_AUTO_PATH)
      message (FATAL_ERROR "Error: No download path provided")
    endif ()
    if (EXISTS "${CMAW_AUTO_PATH}/.cmaw/arduino-cli${CMAKE_EXECUTABLE_SUFFIX}")
      set (CMAW_ARDUINOCLI_BINARY_LOCATION "${CMAKE_BINARY_DIR}/.cmaw/arduino-cli${CMAKE_EXECUTABLE_SUFFIX}")
    endif ()
  endif ()
  
  if (NOT CMAW_ARDUINOCLI_BINARY_LOCATION)
    file (MAKE_DIRECTORY "${CMAW_AUTO_PATH}/.cmaw")
    cmaw_internal_build_ardcli_downloadurl ("${CMAW_ARDUINOCLI_DL_VERSION}")
    
    set (CMAW_INTERNAL_ARDCLI_ARK_PATH "${CMAW_AUTO_PATH}/.cmaw/${CMAW_INTERNAL_ARDCLI_DOWNLOAD_FILENAME}")
    file (DOWNLOAD "${CMAW_INTERNAL_ARDCLI_DOWNLOAD_URL}" "${CMAW_INTERNAL_ARDCLI_ARK_PATH}"
          STATUS CMAW_INTERNAL_DOWNLOAD_RESULT
          TLS_VERIFY ON
          SHOW_PROGRESS)
    list (GET CMAW_INTERNAL_DOWNLOAD_RESULT 0 CMAW_INTERNAL_DOWNLOAD_RESULT_STATUS)
    if (NOT CMAW_INTERNAL_DOWNLOAD_RESULT_STATUS EQUAL 0)
      list (GET CMAW_INTERNAL_DOWNLOAD_RESULT 1 CMAW_INTERNAL_DOWNLOAD_RESULT_ERRMSG)
      message (FATAL_ERROR "Error while attempting to download arduino-cli: ${CMAW_INTERNAL_DOWNLOAD_RESULT_ERRMSG}")
    endif ()
    unset (CMAW_INTERNAL_DOWNLOAD_RESULT_STATUS)
    unset (CMAW_INTERNAL_DOWNLOAD_RESULT)
    file (ARCHIVE_EXTRACT INPUT "${CMAW_INTERNAL_ARDCLI_ARK_PATH}" DESTINATION "${CMAW_AUTO_PATH}/.cmaw/")
    set (CMAW_ARDUINOCLI_BINARY_LOCATION "${CMAW_AUTO_PATH}/.cmaw/arduino-cli${CMAKE_EXECUTABLE_SUFFIX}")
    mark_as_advanced (CMAW_ARDUINOCLI_BINARY_LOCATION)
  endif ()

  set (CMAW_INTERNAL_ARDCLI_PATH "${CMAW_ARDUINOCLI_BINARY_LOCATION}")
  #file (REAL_PATH "${CMAW_ARDUINOCLI_BINARY_LOCATION}" CMAW_INTERNAL_ARDCLI_PATH)
endmacro (cmaw_internal_bootstrap)
cmaw_internal_bootstrap ()

macro (cmaw_internal_ardcli_invoke)
  if (CMAW_ARDUINOCLI_CONFIG_FILEPATH)
    set (CMAW_INTERNAL_ARDCLI_CONFIG_ARG "--config-file" "\"${CMAW_ARDUINOCLI_CONFIG_FILEPATH}\"")
  endif ()
  if (CMAW_ARDUINOCLI_EXTRA_BOARD_URL)
    set (CMAW_INTERNAL_ARDCLI_EXTRA_BURL "--additional-urls" "\"${CMAW_ARDUINOCLI_EXTRA_BOARD_URL}\"")
  endif ()
  execute_process (COMMAND "${CMAW_INTERNAL_ARDCLI_PATH}" ${CMAW_INTERNAL_ARDCLI_CONFIG_ARG} ${CMAW_INTERNAL_ARDCLI_EXTRA_BURL} ${ARGV}
                   RESULT_VARIABLE CMAW_INTERNAL_INVOKE_EXITCODE
                   OUTPUT_VARIABLE CMAW_INTERNAL_INVOKE_OUTPUT)
endmacro ()

# Syntax: cmaw_internal_deinterlace_list (INVAR OUTVAR_1 [...OUTVAR_N])
# Note: we assume there are N * M elements in the input list
function (cmaw_internal_deinterlace_list INVAR)
  list (POP_FRONT ARGV)
  list (LENGTH ${INVAR} INPUT_LENGTH)
  math (EXPR RUNS_COUNT "${INPUT_LENGTH} / (${ARGC} - 1)")
  foreach (I RANGE 1 ${RUNS_COUNT})
    foreach(ARG ${ARGV})
      list (POP_FRONT ${INVAR} ELEMENT)
      list (APPEND ${ARG}_OUT "${ELEMENT}")
    endforeach ()
  endforeach ()
  foreach(ARG ${ARGV})
      set (${ARG} "${${ARG}_OUT}" PARENT_SCOPE)
    endforeach ()
endfunction ()

# Syntax: cmaw_internal_parse_table (<tablestr-var> [<colname-str> <out-colvar>]...)
# Note: will ignore columns to the right of the last mentioned one
# Note: supports up to 9 specified columns (limited by CMake regex captures)
function (cmaw_internal_parse_table TABLE)
  list (POP_FRONT ARGV)
  set (VARARGS "${ARGV}")
  cmaw_internal_deinterlace_list (VARARGS COL_NAMES OUT_VARS)
  
  set (HEADER_PATTERN "")
  set (LEADING_SEQ "^")
  foreach (COL_NAME ${COL_NAMES})
    string (APPEND HEADER_PATTERN "${LEADING_SEQ}(${COL_NAME} *)")
    set (LEADING_SEQ " ")
  endforeach ()
  unset (LEADING_SEQ)
  
  if (${TABLE} MATCHES "${HEADER_PATTERN}")
  else ()
    set (CMAW_INTERNAL_ERROR 1)
    return ()
  endif ()
  
  set (COL_OFFSET_ACCUMULATOR 0)
  foreach (I RANGE 1 ${CMAKE_MATCH_COUNT})
    string (LENGTH "${CMAKE_MATCH_${I}}" COL_MAX_LENGTH)
    list (APPEND COL_MAX_LENGTHS ${COL_MAX_LENGTH})
    list (APPEND COL_OFFSETS ${COL_OFFSET_ACCUMULATOR})
    math (EXPR COL_OFFSET_ACCUMULATOR "${COL_OFFSET_ACCUMULATOR} + ${COL_MAX_LENGTH} + 1")
  endforeach ()
  unset (COL_OFFSET_ACCUMULATOR)
  
  string (REGEX REPLACE "\n" ";" ROWS ${${TABLE}})
  list (POP_FRONT ROWS) # Remove header row
  
  list (LENGTH ROWS ROWS_COUNT)
  foreach (ROW ${ROWS})
    set (I 1)
    foreach(OFFSET MAX_LENGTH IN ZIP_LISTS COL_OFFSETS COL_MAX_LENGTHS)
      string (SUBSTRING "${ROW}" ${OFFSET} ${MAX_LENGTH} VALUE)
      string (STRIP "${VALUE}" VALUE)
      list (APPEND OUT_${I} "${VALUE}")
      math (EXPR I "${I} + 1")
    endforeach ()
    unset (I)
  endforeach ()
  
  set (I 1)
  foreach (OUT_VAR ${OUT_VARS})
    set (${OUT_VAR} ${OUT_${I}} PARENT_SCOPE)
    math (EXPR I "${I} + 1")
  endforeach ()
  unset (I)
endfunction ()


function (cmaw_arduinocli_version OUTVAR)
  cmaw_internal_ardcli_invoke ("version")
  if (NOT CMAW_INTERNAL_INVOKE_OUTPUT MATCHES "Version: ([0-9]+.[0-9]+.[0-9]+)")
    message (FATAL_ERROR "Could not parse arduino-cli version output")
  endif ()
  set (${OUTVAR} "${CMAKE_MATCH_1}" PARENT_SCOPE)
endfunction ()

function (cmaw_init_config DESTDIR)
  if (ARGC GREATER 1)
    message (FATAL_ERROR "Too many parameters for call to function cmaw_init_config")
  endif ()
  
  cmaw_internal_ardcli_invoke ("config" "init" "--dest-dir" "${DESTDIR}")
endfunction ()

# Syntax: cmaw_dump_config (<out-var> [JSON])
function (cmaw_dump_config OUTVAR)
  if (ARGC EQUAL 2)
    if (ARGV1 STREQUAL "JSON")
      list (APPEND FORMAT "--format" "json")
    else ()
      message (FATAL_ERROR "Invalid parameters for cmaw_dump_config")
    endif ()
  elseif (ARGC GREATER 2)
    message (FATAL_ERROR "Invalid parameters for cmaw_dump_config")
  endif ()
  cmaw_internal_ardcli_invoke ("config" "dump" ${FORMAT})
  set (${OUTVAR} "${CMAW_INTERNAL_INVOKE_OUTPUT}" PARENT_SCOPE)
endfunction ()


# Usage: cmaw_update_core_index ()
function (cmaw_update_core_index)
  cmaw_internal_ardcli_invoke ("core" "update-index")
endfunction ()

function (cmaw_list_installed_cores OUT_IDS OUT_VERSIONS OUT_LATESTS OUT_NAMES)
  cmaw_internal_ardcli_invoke ("core" "list")
  if (NOT CMAW_INTERNAL_INVOKE_EXITCODE EQUAL 0)
    message (FATAL_ERROR "Unexpected arduino-cli failure")
  endif ()
  
  # We do not handle the empty case as arduino-cli bundles the avr core
  cmaw_internal_parse_table (CMAW_INTERNAL_INVOKE_OUTPUT
                             "ID" IDENTIFIERS
                             "Installed" VERSIONS
                             "Latest" LATESTS
                             "Name" NAMES)
  
  set (${OUT_IDS} "${IDENTIFIERS}" PARENT_SCOPE)
  set (${OUT_VERSIONS} "${VERSIONS}" PARENT_SCOPE)
  set (${OUT_LATESTS} "${LATESTS}" PARENT_SCOPE)
  set (${OUT_NAMES} "${NAMES}" PARENT_SCOPE)
endfunction ()

# Usage: cmaw_install_cores (<packager>:<arch>[@<version>]...)
function (cmaw_install_cores)
  cmaw_internal_ardcli_invoke (core install ${ARGV})
endfunction ()

# Usage: cmaw_uninstall_cores (<packager>:<arch>...)
function (cmaw_uninstall_cores)
  cmaw_internal_ardcli_invoke (core uninstall ${ARGV})
endfunction ()

# Usage: cmaw_upgrade_cores (<packager>:<arch>...)
# Alt:   cmaw_upgrade_cores (ALL)
function (cmaw_upgrade_cores ARG)
  if (ARG STREQUAL ALL)
    if (ARGC GREATER 1)
      message (FATAL_ERROR "cmaw_upgrade_cores: ALL must stand alone in the arguments if present")
    endif ()
    set (ARGV "")
  endif ()
  cmaw_internal_ardcli_invoke (core upgrade ${ARGV})
endfunction ()

function (cmaw_list_known_boards OUT_NAMES OUT_FQBNS)
  cmaw_internal_ardcli_invoke ("board" "listall")
  # We do not handle the empty case, because arduino-cli bundles arduino boards' definitions
  if (NOT CMAW_INTERNAL_INVOKE_EXITCODE EQUAL 0)
    message (FATAL_ERROR "Unexpected arduino-cli failure")
  endif ()
  
  cmaw_internal_parse_table (CMAW_INTERNAL_INVOKE_OUTPUT
                             "Board Name" NAMES
                             "FQBN" FQBNS)
  
  list (LENGTH NAMES NAME_LISTS)
  
  set (${OUT_NAMES} "${NAMES}" PARENT_SCOPE)
  set (${OUT_FQBNS} "${FQBNS}" PARENT_SCOPE)
endfunction ()

function (cmaw_list_connected_boards OUT_PORTS OUT_TYPES OUT_EVENTS OUT_NAMES OUT_FQBNS OUT_CORES)
  cmaw_internal_ardcli_invoke ("board" "list")
  if (NOT CMAW_INTERNAL_INVOKE_EXITCODE EQUAL 0)
    message (FATAL_ERROR "Unexpected arduino-cli failure")
  endif ()
  if (CMAW_INTERNAL_INVOKE_OUTPUT MATCHES "No boards found.")
    set (${OUT_PORTS} "" PARENT_SCOPE)
    set (${OUT_TYPES} "" PARENT_SCOPE)
    set (${OUT_EVENTS} "" PARENT_SCOPE)
    set (${OUT_NAMES} "" PARENT_SCOPE)
    set (${OUT_FQBNS} "" PARENT_SCOPE)
    set (${OUT_CORES} "" PARENT_SCOPE)
  endif ()

  cmaw_internal_parse_table (CMAW_INTERNAL_INVOKE_OUTPUT
                             "Port" PORTS
                             "Type" TYPES
                             "Event" EVENTS
                             "Board Name" NAMES
                             "FQBN" FQBNS
                             "Core" CORES)
  
  set (${OUT_PORTS} "${PORTS}" PARENT_SCOPE)
  set (${OUT_TYPES} "${TYPES}" PARENT_SCOPE)
  set (${OUT_EVENTS} "${EVENTS}" PARENT_SCOPE)
  set (${OUT_NAMES} "${NAMES}" PARENT_SCOPE)
  set (${OUT_FQBNS} "${FQBNS}" PARENT_SCOPE)
  set (${OUT_CORES} "${CORES}" PARENT_SCOPE)
endfunction ()

function (cmaw_list_installed_libraries OUT_NAMES OUT_VERSIONS OUT_AVAILS OUT_LOCS)
  cmaw_internal_ardcli_invoke ("lib" "list")
  if (NOT CMAW_INTERNAL_INVOKE_EXITCODE EQUAL 0)
    message (FATAL_ERROR "Unexpected arduino-cli failure")
  endif ()
  
  # FIXME handle the empty case
  cmaw_internal_parse_table (CMAW_INTERNAL_INVOKE_OUTPUT
                             "Name" NAMES
                             "Installed" VERSIONS
                             "Available" AVAILS
                             "Location" LOCS)
  
  set (${OUT_NAMES} "${NAMES}" PARENT_SCOPE)
  set (${OUT_VERSIONS} "${VERSIONS}" PARENT_SCOPE)
  set (${OUT_AVAILS} "${AVAILS}" PARENT_SCOPE)
  set (${OUT_LOCS} "${LOCS}" PARENT_SCOPE)
endfunction ()

# Usage: cmaw_update_library_index ()
function (cmaw_update_library_index)
  if (ARGC GREATER 0)
    message (FATAL_ERROR "Too many parameters for call to function cmaw_init_config")
  endif ()

  cmaw_internal_ardcli_invoke ("lib" "update-index")
endfunction ()

# Usage: cmaw_install_libraries (<name>[@<version>]... [NO_DEPS])
function (cmaw_install_libraries)
  set (BACK_ARG "")
  if (ARGC GREATER_EQUAL 1)
    list (POP_BACK ARGV BACK_ARG)
  endif ()
  
  if (BACK_ARG STREQUAL "NO_DEPS")
    set (BACK_ARG "--no-deps")
  endif ()
  
  cmaw_internal_ardcli_invoke (lib install ${ARGV} ${BACK_ARG})
endfunction ()

# Usage: cmaw_uninstall_libraries (<lib-name>...)
function (cmaw_uninstall_libraries)
  cmaw_internal_ardcli_invoke (lib uninstall ${ARGV})
endfunction ()

# Usage: cmaw_upgrade_libraries (<lib-name>...)
# Alt:   cmaw_upgrade_libraries (ALL)
function (cmaw_upgrade_libraries ARG)
  if (ARG STREQUAL ALL)
    if (ARGC GREATER 1)
      message (FATAL_ERROR "cmaw_upgrade_libraries: ALL must stand alone in the arguments if present")
    endif ()
    set (ARGV "")
  endif ()
  cmaw_internal_ardcli_invoke (lib upgrade ${ARGV})
endfunction ()

# Usage: cmaw_clean_arduino_cache ()
function (cmaw_clean_arduino_cache)
  if (ARGC GREATER 0)
    message (FATAL_ERROR "Too many parameters for call to function cmaw_init_config")
  endif ()
  
  cmaw_internal_ardcli_invoke ("cache" "clean")
  
  if (NOT CMAW_INTERNAL_INVOKE_EXITCODE EQUAL 0)
    message (FATAL_ERROR "Unexpected arduino-cli failure")
  endif ()
endfunction ()

function (cmaw_create_sketch NAME)
  if (ARGC GREATER 1)
    message (FATAL_ERROR "Too many parameters for call to function cmaw_init_config")
  endif ()
  
  cmaw_internal_ardcli_invoke ("sketch" "new" "${NAME}")
endfunction ()

function (cmaw_preprocess OUTVAR FQBN SKETCH_PATH)
  if (ARGC GREATER 3)
    message (FATAL_ERROR "Too many parameters for call to function cmaw_preprocess")
  endif ()
  
  if (FQBN STREQUAL "")
    message (FATAL_ERROR "cmaw_preprocess: Board argument may not be an empty string")
  endif ()
  
  cmaw_internal_ardcli_invoke ("compile" "--preprocess" "--fqbn" "${FQBN}" "${SKETCH_PATH}")
  string (REGEX REPLACE "^[^#]*#include <Arduino.h>\n#line 1" "#include <Arduino.h>\n#line 1" CMAW_INTERNAL_INVOKE_OUTPUT "${CMAW_INTERNAL_INVOKE_OUTPUT}")
  set (${OUTVAR} "${CMAW_INTERNAL_INVOKE_OUTPUT}" PARENT_SCOPE)
endfunction ()

# Usage: add_arduino_sketch (<target-name> <fqbn> [EXCLUDE_FROM_ALL] <sketch-source-path>)
function (add_arduino_sketch TARGET FQBN)
  set (ALL "ALL")
  if (ARGC EQUAL 3)
    if (ARGV2 STREQUAL "EXCLUDE_FROM_ALL")
      message (FATAL_ERROR "add_arduino_sketch: sketch path is required")
    endif ()
    set (SRC_PATH "${ARGV2}")
  elseif (ARGC EQUAL 4)
    if (NOT ARGV2 STREQUAL "EXCLUDE_FROM_ALL")
      message (FATAL_ERROR "add_arduino_sketch: Malformed call")
    endif ()
    set (SRC_PATH "${ARGV3}")
    set (ALL "")
  else ()
    message (FATAL_ERROR "Incorrect parameter count for call to function add_arduino_sketch")
  endif ()

  set (DEP_FILE "some/path") # FIXME
  add_custom_target ("${TARGET}" ${ALL}
                     DEPENDS "${SRC_PATH}" "${DEP_FILE}")
  set (TEMP_SCRIPT_PATH "${CMAKE_CURRENT_BINARY_DIR}/CMAWproxy.cmake")
  
  # TODO Add support for custom libs
  file(GENERATE OUTPUT "${TEMP_SCRIPT_PATH}" CONTENT
    "# THIS IS A TEMPORARY, GENERATED FILE; DO NOT EDIT                       \
    set (DEFINITIONS_IN \"$<TARGET_PROPERTY:${TARGET},COMPILE_DEFINITIONS>\") \
    set (OPTIONS_IN \"$<TARGET_PROPERTY:${TARGET},COMPILE_OPTIONS>\")         \
    set (INCLDIRS_IN \"$<TARGET_PROPERTY:${TARGET},INCLUDE_DIRECTORIES>\")    \
                                                                              \
    set (BUILD_PROPERTIES \"\") #FIXME Initialize with boards.txt's build.extra_flags value \
    foreach (DEFINITION DEFINITIONS_IN)                                       \
      string (APPEND BUILD_PROPERTIES \"-D${DEFINITION} \")                   \
    endforeach ()                                                             \
    foreach (OPTION OPTIONS_IN)                                               \
      string (APPEND BUILD_PROPERTIES \"${OPTION} \")                         \
    endforeach ()                                                             \
    foreach (INCLDIR INCLDIRS_IN)                                             \
      string (APPEND BUILD_PROPERTIES \"-I \\\"${INCLDIR}\\\" \")             \
    endforeach ()                                                             \
                                                                              \
    execute_process (COMMAND \"${CMAW_INTERNAL_ARDCLI_PATH}\"                 \
                             \"compile\" \"--fqbn\" \"${FQBN}\"               \
                             \"--build-property\" \"build.extra_flags=\\\"${BUILD_PROPERTIES}\\\"\" \
                             \"${SRC_PATH}\")                                 \
    ")
  add_custom_command (OUTPUT "${CMAKE_COMMAND}" "-P" "${TEMP_SCRIPT_PATH}"
                      COMMAND "compile" "--fqbn" "${FQBN}" "${SRC_PATH}"
                      MAIN_DEPENDENCY "${SRC_PATH}")
endfunction ()
