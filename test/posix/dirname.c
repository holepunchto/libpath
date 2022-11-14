#include <assert.h>
#include <stddef.h>
#include <string.h>

#include "../../include/path.h"

static path_separator_t sep = path_separator_posix;

int
main () {
  int e;

  {
    size_t len;
    e = path_dirname("a/b/c", &len, sep);
    assert(e == 0);
    assert(len == 4);
  }

  return 0;
}
