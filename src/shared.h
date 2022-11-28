#ifndef PATH_SHARED_H
#define PATH_SHARED_H

#include "../include/path.h"

static inline int
path_copy (char *target, size_t *target_offset, size_t target_len, const char *source, size_t len) {
  size_t end = *target_offset + len;

  if (end > target_len) return -1;

  memcpy(&target[*target_offset], source, len);

  *target_offset += len;

  return 0;
}

#endif // PATH_SHARED_H
