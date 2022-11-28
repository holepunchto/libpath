#ifndef PATH_POSIX_IS_ABSOLUTE_H
#define PATH_POSIX_IS_ABSOLUTE_H

#include <stddef.h>
#include <string.h>

#include "../../include/path.h"

static inline bool
path_is_absolute_posix (const char *path) {
  if (!path) return false;

  size_t path_len = strlen(path);

  return path_len > 0 && path_is_posix_separator(path[0]);
}

#endif // PATH_POSIX_IS_ABSOLUTE_H
