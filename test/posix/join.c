#include <assert.h>
#include <limits.h>
#include <stddef.h>
#include <string.h>

#include "../../include/path.h"

static path_separator_t sep = path_separator_posix;

int
main () {
  int e;
  char buf[PATH_MAX];

  {
    size_t len = PATH_MAX;
    e = path_join((const char *[]){NULL}, buf, &len, sep);
    assert(e == 0);
    assert(len == 0);
    assert(strcmp(buf, "") == 0);
  }
  {
    size_t len = PATH_MAX;
    e = path_join((const char *[]){"a", NULL}, buf, &len, sep);
    assert(e == 0);
    assert(len == 1);
    assert(strcmp(buf, "a") == 0);
  }
  {
    size_t len = PATH_MAX;
    e = path_join((const char *[]){"a", "b", "c", NULL}, buf, &len, sep);
    assert(e == 0);
    assert(len == 5);
    assert(strcmp(buf, "a/b/c") == 0);
  }

  return 0;
}
