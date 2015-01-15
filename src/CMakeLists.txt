set(HEADERS_SHARED
  "${CMAKE_CURRENT_SOURCE_DIR}/reader/mpr_reader.h"
  "${CMAKE_CURRENT_SOURCE_DIR}/writer/mpr_writer.h"
  "${CMAKE_CURRENT_SOURCE_DIR}/util/util.h")

#add_subdirectory(cli)
#add_subdirectory(mpr)
#add_subdirectory(util)
#add_subdirectory(reader)
#add_subdirectory(writer)
#add_subdirectory(main)

add_library(mic STATIC
  cli/cli
  mpr/mpr
  util/util
  reader/v4/v4
  writer/html/html
  writer/latex/latex
  writer/debug/debug
)

add_executable(mictool
  main/main
)
target_link_libraries(mictool mic)

add_executable(mictool_test
  test/util_test
  test/reader_v4_test
  test/micro_line_test
)
target_link_libraries(mictool_test mic gtest gtest_main)

if ( CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX )
    # This is tested
    set_property( TARGET mic APPEND_STRING PROPERTY COMPILE_FLAGS "-W -Wall -Werror -Wextra")
endif ()
