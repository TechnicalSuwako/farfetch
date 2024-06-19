#include "uptime.h"
#include "common.h"

#include <stdio.h>

void display_days() {
  printf("%s", run_command_s("uptime | awk '{print $3}' && echo \" days\""));
}

void display_time() {
  printf("%s", run_command_s("uptime | awk '{print $5}' | sed 's/,//' | "
                             "sed 's/:/ hours, /' && echo \" mins\""));
}
