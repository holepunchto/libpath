#ifndef PATH_SHARED_H
#define PATH_SHARED_H

#include <stddef.h>

#include "../include/path.h"

static inline int
path_copy (char *target, size_t *target_offset, size_t target_len, const char *source, size_t len) {
  size_t end = *target_offset + len;

  if (end > target_len) return -1;

  for (size_t i = 0, j = *target_offset; i < len; i++, j++) {
    target[j] = source[i];
  }

  *target_offset += len;

  return 0;
}

#endif // PATH_SHARED_H
