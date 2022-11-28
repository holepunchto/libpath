#ifndef PATH_POSIX_NORMALIZE_H
#define PATH_POSIX_NORMALIZE_H

#include <string.h>

#include "../../include/path.h"

static inline int
path_normalize_posix (const char *path, char *buf, size_t *len) {
  if (!path || !buf || !len) goto err;

  size_t path_len = strlen(path);

  if (path_len == 0) {
    *len = 0;
    return 0;
  }

  bool is_absolute = path_is_absolute_posix(path);

  bool is_above_root = false;

  bool is_first_segment = !is_absolute;

  bool has_trailing_sep = path_is_posix_separator(path[path_len - 1]);

  size_t i = 0, offset = 0;

  if (is_absolute) {
    while (path_is_posix_separator(path[i])) {
      i++;
    }
  }

  while (path[i] != '\0') {
    size_t len = 0;

    while (!path_is_posix_separator(path[i + len]) && path[i + len] != '\0') {
      len++;
    }

    if (len == 0) continue;

    if (len == 1 && strncmp(".", &path[i], 1) == 0) {
      goto skip;
    }

    if (len == 2 && strncmp("..", &path[i], 2) == 0 && !is_above_root) {
      buf[offset] = '\0';

      size_t dirname = offset;
      path_dirname_posix(buf, &dirname);

      if (dirname) {
        buf[offset = dirname - (is_absolute ? 0 : 1)] = '\0';
        goto skip;
      } else {
        is_above_root = true;
        is_first_segment = !is_absolute;

        if (offset) {
          buf[offset = 0] = '\0';
          goto skip;
        }
      }
    }

    if (is_first_segment) is_first_segment = false;
    else {
      strcpy(buf + offset, "/");
      offset += 1;
    }

    strncpy(buf + offset, &path[i], len);
    offset += len;

  skip:
    i += len;

    while (path_is_posix_separator(path[i])) {
      i++;
    }
  }

  if (offset == 0) {
    strcpy(buf, ".");
    offset += 1;
  }

  if (has_trailing_sep && !path_is_posix_separator(buf[offset - 1])) {
    strcpy(buf + offset, "/");
    offset += 1;
  }

  buf[offset] = '\0';

  *len = offset;

  return 0;

err:
  return -1;
}

#endif // PATH_POSIX_NORMALIZE_H
