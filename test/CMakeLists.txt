if(TARGET path_shared)
  set(library path::shared)
else()
  set(library path::static)
endif()

add_test_executables(
  posix/dirname.c
  posix/join.c
  posix/normalize.c
  win/dirname.c
  win/join.c
  win/normalize.c
  LINK
    ${library}
)
