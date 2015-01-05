cmake_minimum_required (VERSION 2.6)
project (mictool)

set (PROJECT_SOURCE_DIR src)
set (PROJECT_BINARY_DIR bin)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")

# The version number.
set (mictool_VERSION_MAJOR 1)
set (mictool_VERSION_MINOR 0)

# configure a header file to pass some of the CMake settings
# to the source code
configure_file (
  "${PROJECT_SOURCE_DIR}/MictoolConfig.h.in"
  "${PROJECT_BINARY_DIR}/MictoolConfig.h"
  )

# add the binary tree to the search path for include files
# so that we will find MictoolConfig.h
include_directories("${PROJECT_BINARY_DIR}")

add_subdirectory (src) 
