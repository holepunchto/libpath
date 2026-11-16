cmake_minimum_required(VERSION 4.0)

find_package(cmake-prelude REQUIRED PATHS node_modules/cmake-prelude)
find_package(cmake-test REQUIRED PATHS node_modules/cmake-test)

project(path LANGUAGES C VERSION 0.0.0)

add_library_targets(
  path
  HEADERS
    include/path.h
    include/path/posix.h
    include/path/win.h
  FEATURES
    c_std_99
  SOURCES
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

add_test_subdirectory(test)
