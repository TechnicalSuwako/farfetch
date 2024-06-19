#include "resolution.h"
#include "common.h"

#include <stdio.h>
#include <string.h>

const char *display_resolution() {
  const char *isexist = run_command_s("which xrandr");
  if (
      isexist == NULL ||
      strlen(isexist) == 0 ||
      strncmp(isexist, "xrandr not found", strlen("xrandr not found")) == 0
  ) return NULL;

  return run_command_s("xrandr --nograb --current | "
                       "awk -F 'connected |\\\\+|\\\\(' '/ "
                       "connected.*[0-9]+x[0-9]+\\+/ && $2 {printf $2 "
                       "\", \"}' | sed 's/primary //' | "
                       "sed 's/,\\([^,]*\\)$/\\1/'");
}
