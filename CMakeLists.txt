cmake_minimum_required (VERSION 2.6)
project (mictool)

include(CheckIncludeFiles)
check_include_files(getopt.h HAVE_GETOPT_H)

if(HAVE_GETOPT_H)
  message(STATUS "Found header <getopt.h>")
else()
  message(SEND_ERROR "Could not find heaer file getopt.h. Do you have a unix environment?")
endif()

#set (PROJECT_SOURCE_DIR src)
#set (PROJECT_BINARY_DIR bin)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")

# The version number.
set (Mictool_VERSION_MAJOR 1)
set (Mictool_VERSION_MINOR 0)

# configure a header file to pass some of the CMake settings
# to the source code
configure_file (
  "${PROJECT_SOURCE_DIR}/src/MictoolConfig.h.in"
  "${PROJECT_SOURCE_DIR}/src/MictoolConfig.h"
)

# add the binary tree to the search path for include files
# so that we will find MictoolConfig.h
include_directories(src)

add_subdirectory (src)

add_custom_target( doc
  COMMAND echo 'Mictool {\#mainpage}' > mainpage.md
  COMMAND tail -n +2 README.md >> mainpage.md
  COMMAND doxygen Doxyfile
)
