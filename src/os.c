#include "os.h"
#include "common.h"

#include <stdio.h>
#include <stdlib.h>

const char *display_os() {
  const char *osname = NULL;
  const char *osversion = NULL;
  const char *osarch = NULL;
  char *cmd;

#if defined(__APPLE__)
  if (!from_cache("/tmp/farfetch/os")) {
    osname = run_command_s("sw_vers | grep \"ProductName\" | awk '{print $2}'");
    osversion = run_command_s("sw_vers | grep \"ProductVersion\" | awk '{print $2}'");
    osarch = run_command_s("uname -m");

    cmd = (char *)malloc(128 * sizeof(char));
    if (!cmd) {
      perror("malloc");
      free((void *)osname);
      free((void *)osversion);
      free((void *)osarch);
      return NULL;
    }
    snprintf(cmd, 128, "%s %s %s", osname, osversion, osarch);

    to_cache("/tmp/farfetch/os", cmd);
  } else {
    cmd = (char *)from_cache("/tmp/farfetch/os");
  }
#elif defined(__HAIKU__)
  osname = run_command_s("uname -s");
  osversion = run_command_s("uname -r");
  osarch = run_command_s("uname -m");

  cmd = (char *)malloc(128 * sizeof(char));
  if (!cmd) {
    perror("malloc");
    free((void *)osname);
    free((void *)osversion);
    free((void *)osarch);
    return NULL;
  }
  snprintf(cmd, 128, "%s %s %s", osname, osversion, osarch);
#else
  if (!from_cache("/tmp/farfetch/os")) {
    osname = run_command_s("uname -s");
    osversion = run_command_s("uname -r");
    osarch = run_command_s("uname -m");

    cmd = (char *)malloc(128 * sizeof(char));
    if (!cmd) {
      perror("malloc");
      free((void *)osname);
      free((void *)osversion);
      free((void *)osarch);
      return NULL;
    }
    snprintf(cmd, 128, "%s %s %s", osname, osversion, osarch);

    to_cache("/tmp/farfetch/os", cmd);
  } else {
    cmd = (char *)from_cache("/tmp/farfetch/os");
  }
#endif

  free((void *)osname);
  free((void *)osversion);
  free((void *)osarch);

  return cmd;
}
