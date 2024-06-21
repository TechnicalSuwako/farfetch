#include "wm.h"
#include "common.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

const char *display_wm() {
#if defined(__APPLE__)
  return "Aqua";
#else
  const char *display = run_command_s("echo $DISPLAY");
  if (display == NULL || strlen(display) == 0) return NULL;
  else free((void *)display);

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
