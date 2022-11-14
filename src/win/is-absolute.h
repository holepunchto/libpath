#ifndef PATH_WIN_IS_ABSOLUTE_H
#define PATH_WIN_IS_ABSOLUTE_H

#include <stddef.h>
#include <string.h>

#include "../../include/path.h"
#include "shared.h"

static inline bool
path_is_absolute_windows (const char *path) {
  if (!path) return false;

  size_t path_len = strlen(path);

  if (path_len == 0) return false;

  if (path[0] == path_separator_windows) return true;

  return (
    path_len > 2 &&
    is_windows_device_root(path[0]) &&
    path[1] == ':' &&
    path[2] == path_separator_windows
  );
}

#endif // PATH_WIN_IS_ABSOLUTE_H
