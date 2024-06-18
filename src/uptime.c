#include "uptime.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void run_uptime_command(const char *command) {
  char buf[128];

  FILE *p = popen(command, "r");
  if (!p) {
    fprintf(stderr, "起動時間コマンドを実効に失敗: %s", command);
    return;
  }

  while (fgets(buf, sizeof(buf), p) != NULL) {
    buf[strcspn(buf, "\n")] = '\0';
    printf("%s", buf);
  }

  pclose(p);
}

#ifndef __NetBSD__
void display_days() {
  run_uptime_command("uptime | awk '{print $3}' && echo \" days\"");
}
#endif

void display_time() {
#if defined(__NetBSD__)
  run_uptime_command("uptime | awk '{print $3}' | sed 's/,//' | "
                     "sed 's/:/ hours, /' && echo \" mins\"");
#else
  run_uptime_command("uptime | awk '{print $5}' | sed 's/,//' | "
                     "sed 's/:/ hours, /' && echo \" mins\"");
#endif
}
