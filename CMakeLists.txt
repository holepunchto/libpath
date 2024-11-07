cmake_minimum_required(VERSION 3.22)

project(path C)

add_library(path OBJECT)

set_target_properties(
  path
  PROPERTIES
  C_STANDARD 99
  POSITION_INDEPENDENT_CODE ON
)

target_sources(
  path
  INTERFACE
    include/path.h
    include/path/posix.h
    include/path/win.h
  PRIVATE
    src/path.c
    src/posix/dirname.h
    src/posix/is-absolute.h
    src/posix/join.h
    src/posix/normalize.h
    src/win/dirname.h
    src/win/is-absolute.h
    src/win/join.h
    src/win/normalize.h
    src/win/shared.h
)

target_include_directories(
  path
  PUBLIC
    include
)

add_library(path_shared SHARED)

set_target_properties(
  path_shared
  PROPERTIES
  OUTPUT_NAME path
  WINDOWS_EXPORT_ALL_SYMBOLS ON
)

target_link_libraries(
  path_shared
  PUBLIC
    path
)

add_library(path_static STATIC)

set_target_properties(
  path_static
  PROPERTIES
  OUTPUT_NAME path
  PREFIX lib
)

target_link_libraries(
  path_static
  PUBLIC
    path
)

install(TARGETS path_shared path_static)

install(FILES include/path.h DESTINATION include)

if(PROJECT_IS_TOP_LEVEL)
  enable_testing()

  add_subdirectory(test)
endif()
