#include "libc.h"
#include "common.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

const char *display_libc() {
#if defined(__linux__)
  const char *musl = run_command_s("ldd $(which ls) | grep libc | grep musl");
  if (musl != NULL && strlen(musl) != 0) {
    free((void *)musl);
    return "musl";
  }

  const char *glibc = run_command_s("ldd $(which ls) | grep libc | grep gnu");
  if (glibc != NULL && strlen(glibc) != 0) {
    free((void *)glibc);
    return "glibc";
  }
#endif

  return NULL;
}
