#include "resolution.h"
#include "common.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

const char *usingxrandr() {
  return run_command_s("xrandr --nograb --current | "
                       "awk -F 'connected |\\\\+|\\\\(' '/ "
                       "connected.*[0-9]+x[0-9]+\\+/ && $2 {printf $2 "
                       "\", \"}' | sed 's/primary //' | "
                       "sed 's/,\\([^,]*\\)$/\\1/'");
}

const char *usingxwininfo() {
  return run_command_s("xwininfo -root | awk '/Width/ {width=$2} /Height/ "
                       "{height=$2} END {printf \"%dx%d\\n\", width, height}'");
}

const char *usingxdpyinfo() {
  return run_command_s("xdpyinfo | awk '/dimensions:/ {printf $2}'");
}

const char *usingdrm() {
  return run_command_s("for dev in /sys/class/drm/card*-*/status; do "
                       "if grep -q \"connected\" \"$dev\"; then "
                       "dir=$(dirname \"$dev\"); "
                       "modefile=\"$dir/modes\"; "
                       "dis=$(echo \"$dir\" | sed -e 's/^.*drm\\///'); "
                       "if [ -f \"$modefile\" ]; then "
                       "mode=$(head -n 1 \"$modefile\"); "
                       "if [ -n \"$mode\" ]; then "
                       "echo \"$mode, \"; "
                       "fi "
                       "fi "
                       "fi "
                       "done | sed '$s/,//'");
}

const char *display_resolution() {
#if defined(__HAIKU__)
  return run_command_s("screenmode | sed 's/Resolution: //' | sed 's/,.*$//' | "
                       "sed 's/ /x/'");
#elif defined(__APPLE__)
  return run_command_s("system_profiler SPDisplaysDataType | grep Resolution | "
                       "sed 's/^.*: //' | sed 's/ Retina//' | sed 's/ //g'");
#else
  if (access("/sys/class/drm", F_OK) == 0) {
    return usingdrm();
  }

  const char *display = run_command_s("echo $DISPLAY");
  if (display == NULL || strlen(display) == 0) return NULL;
  else free((void *)display);

  const char *isxrandr = run_command_s("which xrandr");
  if (
      isxrandr != NULL &&
      strlen(isxrandr) != 0 &&
      strncmp(isxrandr, "xrandr not found", strlen("xrandr not found")) != 0 &&
      !strstr(isxrandr, "which: no xrandr in")
  ) {
    free((void *)isxrandr);
    return usingxrandr();
  }
  free((void *)isxrandr);

  const char *isxwininfo = run_command_s("which xwininfo");
  if (
      isxwininfo != NULL &&
      strlen(isxwininfo) != 0 &&
      strncmp(isxwininfo, "xwininfo not found", strlen("xwininfo not found")) != 0 &&
      !strstr(isxwininfo, "which: no xwininfo in")
  ) {
    free((void *)isxwininfo);
    return usingxwininfo();
  }
  free((void *)isxwininfo);

  const char *isxdpyinfo = run_command_s("which xdpyinfo");
  if (
      isxdpyinfo != NULL &&
      strlen(isxdpyinfo) != 0 &&
      strncmp(isxdpyinfo, "xdpyinfo not found", strlen("xdpyinfo not found")) != 0 &&
      !strstr(isxdpyinfo, "which: no xdpyinfo in")
  ) {
    free((void *)isxdpyinfo);
    return usingxdpyinfo();
  }
  free((void *)isxdpyinfo);

  return NULL;
#endif
}
