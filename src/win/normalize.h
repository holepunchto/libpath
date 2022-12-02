#ifndef PATH_WIN_NORMALIZE_H
#define PATH_WIN_NORMALIZE_H

#include <string.h>

#include "../../include/path.h"
#include "shared.h"

static inline int
path_normalize_windows (const char *path, char *buf, size_t *len) {
  if (!path || !buf || !len) goto err;

  if (*len < 1) goto err;

  size_t path_len = strlen(path);

  if (path_len == 0) {
    *len = 0;
    return 0;
  }

  bool is_absolute = path_is_absolute_windows(path);

  bool is_above_root = false;

  bool is_first_segment = !is_absolute;

  bool has_trailing_sep = path_is_separator(path[path_len - 1]);

  size_t i = 0, offset = 0;

  if (
    path_len > 2 &&
    is_windows_device_root(path[0]) &&
    path[1] == ':'
  ) {
    int err = path_copy(buf, &offset, *len, path, 2);
    if (err < 0) goto err;

    i += 2;
  }

  if (is_absolute) {
    while (path_is_separator(path[i])) {
      i++;
    }
  }

  while (path[i] != '\0') {
    size_t n = 0;

    while (!path_is_separator(path[i + n]) && path[i + n] != '\0') {
      n++;
    }

    if (n == 0) continue;

    if (n == 1 && strncmp(".", &path[i], 1) == 0) {
      goto skip;
    }

    if (n == 2 && strncmp("..", &path[i], 2) == 0 && !is_above_root) {
      buf[offset] = '\0';

      size_t dirname = offset;
      path_dirname_windows(buf, &dirname);

      if (dirname) {
        buf[offset = dirname - (dirname == 1 ? 0 : 1)] = '\0';
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
      int err = path_copy(buf, &offset, *len, "\\", 1);
      if (err < 0) goto err;
    }

    int err = path_copy(buf, &offset, *len, &path[i], n);
    if (err < 0) goto err;

  skip:
    i += n;

    while (path_is_separator(path[i])) {
      i++;
    }
  }

  if (offset == 0) {
    int err = path_copy(buf, &offset, *len, ".", 1);
    if (err < 0) goto err;
  }

  if (has_trailing_sep && !path_is_separator(buf[offset - 1])) {
    int err = path_copy(buf, &offset, *len, "\\", 1);
    if (err < 0) goto err;
  }

  buf[offset] = '\0';

  *len = offset;

  return 0;

err:
  return -1;
}

#endif // PATH_POSIX_NORMALIZE_H
