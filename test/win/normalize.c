#include <assert.h>
#include <limits.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

#include "../../include/path.h"

#define test_normalize(path, expected) \
  { \
    size_t len = 4096; \
    int err = path_normalize(path, buf, &len, path_behavior_windows); \
    printf("%s -> %s\n", path, buf); \
    assert(err == 0); \
    assert(len == strlen(expected)); \
    assert(strcmp(buf, expected) == 0); \
  }

int
main () {
  char buf[4096];

  test_normalize("foo\\.", "foo");
  test_normalize("foo\\.\\", "foo\\");
  test_normalize("foo\\.\\.", "foo");
  test_normalize("foo\\.\\.\\", "foo\\");

  test_normalize("foo", "foo");
  test_normalize("foo\\bar", "foo\\bar");

  test_normalize("foo\\..", ".");
  test_normalize("foo\\..\\", ".\\");
  test_normalize("foo\\..\\..", "..");
  test_normalize("foo\\..\\..\\", "..\\");
  test_normalize("foo\\..\\..\\..", "..\\..");
  test_normalize("foo\\..\\..\\..\\", "..\\..\\");

  test_normalize("\\foo", "\\foo");
  test_normalize("\\foo\\bar", "\\foo\\bar");

  // test_normalize("\\foo\\..", "\\");
  // test_normalize("\\foo\\..\\", "\\");
  // test_normalize("\\foo\\..\\..", "\\");
  // test_normalize("\\foo\\..\\..\\", "\\");
  // test_normalize("\\foo\\..\\..\\..", "\\");
  // test_normalize("\\foo\\..\\..\\..\\..\\..\\..\\", "\\");

  test_normalize("foo\\bar\\..", "foo");
  test_normalize("foo\\bar\\..\\", "foo\\");
  test_normalize("foo\\bar\\baz\\..", "foo\\bar");
  test_normalize("foo\\bar\\baz\\..\\", "foo\\bar\\");
  test_normalize("foo\\bar\\baz\\..\\..", "foo");
  test_normalize("foo\\bar\\baz\\..\\..\\", "foo\\");

  test_normalize("\\foo\\bar\\..", "\\foo");
  test_normalize("\\foo\\bar\\..\\", "\\foo\\");
  test_normalize("\\foo\\bar\\baz\\..", "\\foo\\bar");
  test_normalize("\\foo\\bar\\baz\\..\\", "\\foo\\bar\\");
  test_normalize("\\foo\\bar\\baz\\..\\..", "\\foo");
  test_normalize("\\foo\\bar\\baz\\..\\..\\", "\\foo\\");

  test_normalize("..", "..");
  test_normalize("..\\", "..\\");
  test_normalize("..\\..", "..\\..");
  test_normalize("..\\..\\", "..\\..\\");
  test_normalize("..\\..\\..", "..\\..\\..");
  test_normalize("..\\..\\..\\", "..\\..\\..\\");

  // test_normalize("\\..", "\\");
  // test_normalize("\\..\\", "\\");
  // test_normalize("\\..\\..", "\\");
  // test_normalize("\\..\\..\\", "\\");
  // test_normalize("\\..\\..\\..", "\\");
  // test_normalize("\\..\\..\\..\\", "\\");

  test_normalize("foo.", "foo.");
  test_normalize("foo..", "foo..");
  test_normalize("foo...", "foo...");

  test_normalize("foo/bar/baz", "foo\\bar\\baz");

  return 0;
}
