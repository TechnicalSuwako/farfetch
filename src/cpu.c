#include "cpu.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void run_cpu_command(const char *command) {
  char buf[128];

  FILE *p = popen(command, "r");
  if (!p) {
    fprintf(stderr, "ホストコマンドを実効に失敗: %s", command);
    return;
  }

  while (fgets(buf, sizeof(buf), p) != NULL) {
    buf[strcspn(buf, "\n")] = '\0';
    printf("%s", buf);
  }

  pclose(p);
}

void display_cpu() {
#if defined(__NetBSD__)
  run_cpu_command("sysctl -n machdep.cpu_brand | sed 's/(R)//' | "
                  "sed 's/(TM)//' | sed 's/CPU //'");
  run_cpu_command("echo \" (\" && sysctl -n hw.ncpu && echo \" core)\"");
#elif defined(__FreeBSD__) || defined(__OpenBSD__)
  run_cpu_command("sysctl -n hw.model | sed 's/(R)//' | "
                  "sed 's/(TM)//' | sed 's/CPU //'");
  run_cpu_command("echo \" (\" && sysctl -n hw.ncpu && echo \" core)\"");
#elif defined(__linux__)
#endif
}
