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

static const path_separator_t path_separator_system;

typedef enum {
  path_delimiter_posix = ':',
  path_delimiter_windows = ';',
} path_delimiter_t;

static const path_delimiter_t path_delimiter_system;

#if defined(_WIN32)
#include "path/win.h"
#else
#include "path/posix.h"
#endif

int
path_dirname (const char *path, size_t *len, path_separator_t separator);

int
path_join (const char *fragments[], char *buf, size_t *len, path_separator_t separator);

int
path_normalize (const char *path, char *buf, size_t *len, path_separator_t separator);

bool
path_is_absolute (const char *path, path_separator_t separator);

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