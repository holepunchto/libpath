#ifndef PATH_POSIX_JOIN_H
#define PATH_POSIX_JOIN_H

#include <stddef.h>
#include <string.h>

#include "../../include/path.h"
#include "normalize.h"

static inline int
path_join_posix (const char *fragments[], char *buf, size_t *len) {
  if (!fragments || !buf) goto err;

  if (*len < 1) goto err;

  size_t offset = 0;

  for (size_t i = 0;; i++) {
    const char *fragment = fragments[i];
    if (fragment == NULL) break;

    size_t fragment_len = strlen(fragment);
    if (fragment_len == 0) continue;

    if (i > 0) {
      if (*len - 1 <= offset) goto err;

      buf[offset++] = path_separator_posix;
    }

    if (*len - 1 <= offset + fragment_len) goto err;

    strcpy(&buf[offset], fragment);

    offset += fragment_len;
  }

  buf[offset] = '\0';

  *len = offset;

  return path_normalize_posix(buf, buf, len);

err:
  return -1;
}

#endif // PATH_POSIX_JOIN_H
