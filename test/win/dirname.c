#include <assert.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

#include "../../include/path.h"

#define test_dirname(path, expected) \
  { \
    size_t len; \
    int err = path_dirname(path, &len, path_separator_windows); \
    printf("%s -> %.*s\n", path, (int) len, path); \
    assert(err == 0); \
    assert(len == expected); \
  }

int
main () {
  test_dirname("", 0);
  test_dirname("a", 0);
  test_dirname("a\\b", 2);
  test_dirname("a\\b\\c", 4);

  test_dirname("\\", 1);
  test_dirname("\\a", 1);
  test_dirname("\\a\\b", 3);
  test_dirname("\\a\\b\\c", 5);

  test_dirname("..", 0);
  test_dirname("..\\..", 3);

  return 0;
}
