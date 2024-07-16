#include "os.h"
#include "common.h"

#include <stdio.h>
#include <stdlib.h>

const char *display_os() {
  const char *osname = NULL;
  const char *osversion = NULL;
  const char *osarch = NULL;

#if defined(__APPLE__)
  osname = run_command_s("sw_vers | grep \"ProductName\" | awk '{print $2}'");
  osversion = run_command_s("sw_vers | grep \"ProductVersion\" | awk '{print $2}'");
#else
  osname = run_command_s("uname -s");
  osversion = run_command_s("uname -r");
#endif
  osarch = run_command_s("uname -m");

  char *cmd = (char *)malloc(128 * sizeof(char));
  snprintf(cmd, 128, "%s %s %s", osname, osversion, osarch);
  free((void *)osname);
  free((void *)osversion);
  free((void *)osarch);

  return cmd;
}
