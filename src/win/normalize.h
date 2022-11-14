#ifndef PATH_WIN_NORMALIZE_H
#define PATH_WIN_NORMALIZE_H

#include <stddef.h>

#include "../../include/path.h"

static inline int
path_normalize_windows (const char *path, char *buf, size_t *len) {
  if (!path || !buf || !len) goto err;

  if (*len < 1) goto err;

  size_t offset = 0;

  for (size_t i = 0;; i++) {
    char c = path[i];
    if (c == '\0') break;

    if (*len - 1 <= offset) goto err;

    buf[i] = c;

    offset += 1;
  }

  buf[offset] = '\0';

  *len = offset;

  return 0;

err:
  return -1;
}

#endif // PATH_WIN_NORMALIZE_H
