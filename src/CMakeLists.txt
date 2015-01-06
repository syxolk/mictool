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

add_executable(mictool
  main/main
  cli/cli
  mpr/mpr
  util/util
  reader/v4/v4
  writer/html/html
  writer/latex/latex
  writer/debug/debug
)
