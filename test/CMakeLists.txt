list(APPEND tests
  posix/dirname
  posix/join
  win/dirname
  win/join
)

foreach(test IN LISTS tests)
  string(REPLACE "/" "_" name ${test})

  add_executable(${name} ${test}.c)

  target_link_libraries(${name} path_shared)

  add_test(
    NAME ${name}
    COMMAND ${name}
    WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
  )
endforeach()
