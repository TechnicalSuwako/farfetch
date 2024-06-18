#include "gpu.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void run_gpu_command(const char *command) {
  char buf[128];

  FILE *p = popen(command, "r");
  if (!p) {
    fprintf(stderr, "GPUコマンドを実効に失敗: %s", command);
    return;
  }

  while (fgets(buf, sizeof(buf), p) != NULL) {
    buf[strcspn(buf, "\n")] = '\0';
    printf("%s", buf);
  }

  pclose(p);
}

void display_gpu() {
  run_gpu_command("glxinfo -B | grep -F 'OpenGL renderer string' | "
                  "sed 's/OpenGL renderer string: //' | sed 's/Mesa //' | "
                  "sed 's/DRI //' | sed 's/(R)//' | sed 's/(.*$//'");
}
