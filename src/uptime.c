#include "uptime.h"
#include "common.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char *display_days() {
  const char *days = run_command_s("uptime | awk '{for (i=1; i<=NF; i++) "
                                   "if ($i ~ /day/) print $(i-1), $i}'");

  if (days == NULL || strlen(days) == 0) {
    return strndup("0 days,", 7);
  }

  return days;
}

const char *display_time() {
  const char *uptime = run_command_s("uptime");
  if (uptime == NULL) {
    return NULL;
  }

  char *days = strstr(uptime, "day");
  int nodays = 0;
  if (days == NULL) {
    nodays = 1;
    days = strstr(uptime, "days");
  }

  free((void *)uptime);

  if (nodays) {
    return run_command_s("uptime | awk '{print $3}' | sed 's/,//' | "
                         "sed 's/:/ hours, /' && echo \" mins\"");
  }

  return run_command_s("uptime | awk '{print $5}' | sed 's/,//' | "
                         "sed 's/:/ hours, /' && echo \" mins\"");
}
