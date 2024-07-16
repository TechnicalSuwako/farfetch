#include "resolution.h"
#include "common.h"

#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

const char *display_resolution() {
#if defined(__HAIKU__)
  return run_command_s("screenmode | sed 's/Resolution: //' | sed 's/,.*$//' | "
                       "sed 's/ /x/'");
#elif defined(__APPLE__)
  return run_command_s("system_profiler SPDisplaysDataType | grep Resolution | "
                       "sed 's/^.*: //' | sed 's/ Retina//' | sed 's/ //g'");
#else
  const char *display = run_command_s("echo $DISPLAY");
  if (display == NULL || strlen(display) == 0) return NULL;
  else free((void *)display);

  const char *isexist = run_command_s("which xrandr");
  if (
      isexist == NULL ||
      strlen(isexist) == 0 ||
      strncmp(isexist, "xrandr not found", strlen("xrandr not found")) == 0 ||
      strstr(isexist, "which: no xrandr in")
  ) {
    if (isexist) free((void *)isexist);
    return NULL;
  }
  free((void *)isexist);

  return run_command_s("xrandr --nograb --current | "
                       "awk -F 'connected |\\\\+|\\\\(' '/ "
                       "connected.*[0-9]+x[0-9]+\\+/ && $2 {printf $2 "
                       "\", \"}' | sed 's/primary //' | "
                       "sed 's/,\\([^,]*\\)$/\\1/'");
#endif
}
