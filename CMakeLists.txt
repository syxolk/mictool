cmake_minimum_required (VERSION 2.6)
project (mictool)

include(CheckIncludeFiles)
check_include_files(getopt.h HAVE_GETOPT_H)

if(HAVE_GETOPT_H)
  message(STATUS "Found header <getopt.h>")
else()
  message(SEND_ERROR "Could not find heaer file getopt.h. Do you have a unix environment?")
endif()

#find_package(GTest REQUIRED)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")

# The version number.
set (Mictool_VERSION_MAJOR 1)
set (Mictool_VERSION_MINOR 0)

# configure a header file to pass some of the CMake settings
# to the source code

# TODO build MictoolConfig.h not in source
configure_file (
  "${PROJECT_SOURCE_DIR}/src/MictoolConfig.h.in"
  "${PROJECT_BINARY_DIR}/generated/MictoolConfig.h"
)

#add_subdirectory (${GTEST_ROOT})
enable_testing()
find_package(GTest REQUIRED)

# add the binary tree to the search path for include files
# so that we will find MictoolConfig.h
include_directories("${PROJECT_BINARY_DIR}/generated")
include_directories("${PROJECT_SOURCE_DIR}/src")
#include_directories("${PROJECT_SOURCE_DIR}/ext/gtest")
#include_directories("${PROJECT_SOURCE_DIR}/ext/gtest/include")
include_directories(${GTEST_INCLUDE_DIRS})

add_subdirectory (src)

# TODO use add_custom_command instead
add_custom_target( doc
  WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
  COMMAND echo 'Mictool {\#mainpage}' > mainpage.md
  COMMAND tail -n +2 README.md >> mainpage.md
  COMMAND doxygen Doxyfile
)

add_test (
  NAME mictool_test
  COMMAND mictool_test
)

add_test(
  NAME memcheck
  WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
  COMMAND valgrind --tool=memcheck --leak-check=yes --error-exitcode=1 ${CMAKE_BINARY_DIR}/mictool test/implementierung.mpr -o test/implementierung.html
)

