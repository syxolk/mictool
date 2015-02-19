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
  test/ram_cell_test
  test/writer_html_test
)
target_link_libraries(mictool_test mic ${GTEST_BOTH_LIBRARIES} pthread)
#target_link_libraries(mictool_test mic gtest gtest_main)

if ( CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX )
    # This is tested
    set_property( TARGET mic APPEND_STRING PROPERTY COMPILE_FLAGS "-W -Wall -Werror -Wextra")
endif ()

