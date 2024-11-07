#include <assert.h>
#include <limits.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

#include "../../include/path.h"

#define test_join(expected, ...) \
  { \
    size_t len = 4096; \
    int err = path_join((const char *[]) {__VA_ARGS__}, buf, &len, path_behavior_windows); \
    printf("\"%s\"\n", buf); \
    assert(err == 0); \
    assert(len == strlen(expected)); \
    assert(strcmp(buf, expected) == 0); \
  }

int
main () {
  char buf[4096];

  test_join("", NULL);
  test_join("a", "a", NULL);
  test_join("a\\b", "a", "b", NULL);
  test_join("a\\b\\c", "a", "b", "c", NULL);

  return 0;
}
