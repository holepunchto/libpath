#ifndef PATH_WIN_DIRNAME_H
#define PATH_WIN_DIRNAME_H

#include <stdbool.h>
#include <stddef.h>
#include <string.h>

#include "../../include/path.h"

static inline int
path_dirname_windows (const char *path, size_t *len) {
  if (!path || !len) return -1;

  size_t path_len = strlen(path);

  if (path_len == 0) {
    *len = 0;
    return 0;
  }

  bool found_separator = true;

  size_t end = 0;

  for (size_t i = path_len - 1; i >= 1; i--) {
    char c = path[i];

    if (path_is_separator(c)) {
      if (!found_separator) {
        end = i;
        break;
      }
    } else {
      found_separator = false;
    }
  }

  if (end == 0) *len = 0;
  else *len = end + 1;

  return 0;
}

#endif // PATH_WIN_DIRNAME_H
