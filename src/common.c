#include "common.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

long long int run_command_lld(const char *command) {
  char buf[128];
  long long int res = 0;

  FILE *p = popen(command, "r");
  if (!p) {
    fprintf(stderr, "コマンドを実効に失敗: %s", command);
    return 0;
  }

  while (fgets(buf, sizeof(buf), p) != NULL) {
    buf[strcspn(buf, "\n")] = '\0';
  }

  res = atoll(buf);
  pclose(p);

  return res;
}

const char *run_command_s(const char *command) {
  char buf[128];
  char *out = NULL;
  size_t outsize = 0;

  FILE *p = popen(command, "r");
  if (!p) {
    fprintf(stderr, "コマンドを実効に失敗: %s", command);
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
