#ifndef PATH_WIN_SHARED_H
#define PATH_WIN_SHARED_H

#include "../../include/path.h"

static inline bool
is_windows_device_root (char c) {
  return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

#endif // PATH_WIN_SHARED_H
