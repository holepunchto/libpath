#ifndef PATH_H
#define PATH_H

#include <stdbool.h>
#include <stddef.h>

#if defined(_WIN32)
#if defined(PATH_BUILDING)
#define PATH_EXPORT __declspec(dllexport)
#elif defined(PATH_SHARED)
#define PATH_EXPORT __declspec(dllimport)
#else
#define PATH_EXPORT
#endif
#elif defined(__GNUC__)
#define PATH_EXPORT __attribute__((visibility("default")))
#else
#define PATH_EXPORT
#endif

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

PATH_EXPORT int
path_dirname(const char *path, size_t *len, path_behavior_t behavior);

PATH_EXPORT int
path_join(const char *fragments[], char *buf, size_t *len, path_behavior_t behavior);

PATH_EXPORT int
path_normalize(const char *path, char *buf, size_t *len, path_behavior_t behavior);

PATH_EXPORT bool
path_is_absolute(const char *path, path_behavior_t behavior);

PATH_EXPORT inline bool
path_is_relative(const char *path, path_behavior_t behavior) {
  return !path_is_absolute(path, behavior);
}

PATH_EXPORT inline bool
path_is_separator(char code) {
  return code == path_separator_posix || code == path_separator_windows;
}

PATH_EXPORT inline bool
path_is_posix_separator(char code) {
  return code == path_separator_posix;
}

PATH_EXPORT inline bool
path_is_windows_separator(char code) {
  return code == path_separator_windows;
}

#ifdef __cplusplus
}
#endif

#endif // PATH_H
