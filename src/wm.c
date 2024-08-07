#include "wm.h"
#include "common.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

const char *display_wm() {
#if defined(__APPLE__)
  return "Aqua";
#elif defined(__HAIKU__)
  return "Stack & Tile";
#else
  const char *display = run_command_s("echo $DISPLAY");
  if (display == NULL || strlen(display) == 0) return NULL;
  else free((void *)display);

  const char *xproptest = run_command_s("xprop -root -notype _NET_SUPPORTING_WM_CHECK");
  if (
      strncmp(
        xproptest,
        "xprop: error: Invalid window id format: -notype.",
        strlen("xprop: error: Invalid window id format: -notype.")
      )
    ) return NULL;
  else free((void *)xproptest);

  char cmd[512];
  const char *id = run_command_s("xprop -root -notype _NET_SUPPORTING_WM_CHECK | "
      "awk '{print $5}'");

  snprintf(
    cmd,
    sizeof(cmd),
    "%s%s%s",
    "xprop -id ",
    id,
    " -notype -len 100 -f _NET_WM_NAME 8t | awk '{print $3}' | head -1 | "
    "sed 's/\"//g'"
  );

  free((void *)id);

  const char *wm = run_command_s(cmd);

  return wm;
#endif
  return NULL;
}
