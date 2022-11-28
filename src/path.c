#include "../include/path.h"

#include "posix/dirname.h"
#include "posix/is-absolute.h"
#include "posix/join.h"
#include "posix/normalize.h"

#include "win/dirname.h"
#include "win/is-absolute.h"
#include "win/join.h"
#include "win/normalize.h"

int
path_dirname (const char *path, size_t *len, path_behavior_t behavior) {
  switch (behavior) {
  case path_behavior_posix:
    return path_dirname_posix(path, len);
  case path_behavior_windows:
    return path_dirname_windows(path, len);
  }
}

int
path_join (const char *fragments[], char *buf, size_t *len, path_behavior_t behavior) {
  switch (behavior) {
  case path_behavior_posix:
    return path_join_posix(fragments, buf, len);
  case path_behavior_windows:
    return path_join_windows(fragments, buf, len);
  }
}

int
path_normalize (const char *path, char *buf, size_t *len, path_behavior_t behavior) {
  switch (behavior) {
  case path_behavior_posix:
    return path_normalize_posix(path, buf, len);
  case path_behavior_windows:
    return path_normalize_windows(path, buf, len);
  }
}

bool
path_is_absolute (const char *path, path_behavior_t behavior) {
  switch (behavior) {
  case path_behavior_posix:
    return path_is_absolute_posix(path);
  case path_behavior_windows:
    return path_is_absolute_windows(path);
  }
}

extern bool
path_is_relative (const char *path, path_behavior_t behavior);

extern bool
path_is_separator (char code);

extern bool
path_is_posix_separator (char code);

extern bool
path_is_windows_separator (char code);
