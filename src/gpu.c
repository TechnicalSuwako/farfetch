#include "gpu.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

const char *run_gpu_command(const char *command) {
  char buf[128];
  char *out = NULL;
  size_t outsize = 0;

  FILE *p = popen(command, "r");
  if (!p) {
    fprintf(stderr, "GPUコマンドを実効に失敗: %s", command);
    return NULL;
  }

  while (fgets(buf, sizeof(buf), p) != NULL) {
    buf[strcspn(buf, "\n")] = '\0';

    size_t len = strlen(buf);
    char *nout = realloc(out, outsize + len + 1);
    if (nout == NULL) {
      perror("メモリの役割に失敗");
      free(out);
      pclose(p);
      return NULL;
    }

    out = nout;

    memccpy(out + outsize, buf, sizeof(buf), len);
    outsize += len;
    out[outsize] = '\0';
  }

  pclose(p);

  return out;
}

const char *display_gpu() {
#if defined(__OpenBSD__)
  return run_gpu_command("dmesg | grep -i graphics | sed 's/^.* \"//' | "
                         "sed 's/\".*$//'");
#elif defined(__FreeBSD__) || defined(__DragonFly__)
  return run_gpu_command("pciconf -lv | grep -B 4 -F \"VGA\" | "
                         "grep -F \"device\" | sed 's/^.* device//' | "
                         "sed \"s/^.* '//\" | sed \"s/'//\" | tail -1 | "
                         "sed 's/ Core Processor Integrated Graphics Controller//'");
#else
  if (
      access("/bin/glxinfo", F_OK) == -1 &&
      access("/usr/bin/glxinfo", F_OK) == -1 &&
      access("/usr/local/bin/glxinfo", F_OK) == -1 &&
      access("/usr/X11R6/bin/glxinfo", F_OK) == -1 &&
      access("/usr/X11R7/bin/glxinfo", F_OK) == -1 &&
      access("/usr/pkg/bin/glxinfo", F_OK) == -1
  ) return NULL;
  return run_gpu_command("glxinfo -B | grep -F 'OpenGL renderer string' | "
                  "sed 's/OpenGL renderer string: //' | sed 's/Mesa //' | "
                  "sed 's/DRI //' | sed 's/(R)//' | sed 's/(.*$//'");
#endif
}
