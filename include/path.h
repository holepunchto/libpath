#ifndef PATH_H
#define PATH_H

#include <stdbool.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef bool (*path_separator_predicate)(char code);

typedef enum {
  path_separator_posix = '/',
  path_separator_windows = '\\',
} path_separator_t;

typedef enum {
  path_delimiter_posix = ':',
  path_delimiter_windows = ';',
} path_delimiter_t;

typedef enum {
  path_behavior_posix,
  path_behavior_windows
} path_behavior_t;

#if defined(_WIN32)
#include "path/win.h"
#else
#include "path/posix.h"
#endif

int
path_dirname (const char *path, size_t *len, path_behavior_t behavior);

int
path_join (const char *fragments[], char *buf, size_t *len, path_behavior_t behavior);

int
path_normalize (const char *path, char *buf, size_t *len, path_behavior_t behavior);

bool
path_is_absolute (const char *path, path_behavior_t behavior);

inline bool
path_is_relative (const char *path, path_behavior_t behavior) {
  return !path_is_absolute(path, behavior);
}

inline bool
path_is_separator (char code) {
  return code == path_separator_posix || code == path_separator_windows;
}

inline bool
path_is_posix_separator (char code) {
  return code == path_separator_posix;
}

inline bool
path_is_windows_separator (char code) {
  return code == path_separator_windows;
}

#ifdef __cplusplus
}
#endif

#endif // PATH_H
