#include "gpu.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

const char *run_res_command(const char *command) {
  char buf[128];
  char *out = NULL;
  size_t outsize = 0;

  FILE *p = popen(command, "r");
  if (!p) {
    fprintf(stderr, "解像度コマンドを実効に失敗: %s", command);
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

const char *display_resolution() {
  return run_res_command("xrandr --nograb --current | "
                         "awk -F 'connected |\\\\+|\\\\(' '/ "
                         "connected.*[0-9]+x[0-9]+\\+/ && $2 {printf $2 "
                         "\", \"}' | sed 's/primary //' | sed 's/,//'");
}
