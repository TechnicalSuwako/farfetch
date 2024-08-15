#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>

#include "common.h"

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

#if !defined(__HAIKU__)
const char *from_cache(const char *file) {
  struct stat st;
  if (stat(file, &st) != 0) {
    return NULL;
  }

  FILE *f = fopen(file, "r");
  if (!f) {
    return NULL;
  }

  char *cmd = (char *)malloc(128 * sizeof(char));
  if (!cmd) {
    fclose(f);
    return NULL;
  }

  if (fgets(cmd, 128, f) == NULL) {
    free(cmd);
    fclose(f);
    return NULL;
  }

  fclose(f);

  cmd[strcspn(cmd, "\n")] = '\0';
  return cmd;
}

int to_cache(const char *file, const char *res) {
  char dir[256];
  snprintf(dir, sizeof(dir), "%s", "/tmp/farfetch");

  struct stat st;

  if (stat(dir, &st) != 0) {
    if (mkdir(dir, 0755) != 0 && errno != EEXIST) return -1;
  }

  FILE *f = fopen(file, "w");
  if (!f) return -1;

  fprintf(f, "%s", res);
  fclose(f);

  return 0;
}

void delete_cache() {
  struct stat st;

  if (stat("/tmp/farfetch/os", &st) == 0) remove("/tmp/farfetch/os");
  if (stat("/tmp/farfetch/host", &st) == 0) remove("/tmp/farfetch/host");
#if defined(__linux__) || defined(__sunos)
  if (stat("/tmp/farfetch/distro", &st) == 0) remove("/tmp/farfetch/distro");
#endif
  if (stat("/tmp/farfetch/cpu", &st) == 0) remove("/tmp/farfetch/cpu");
  if (stat("/tmp/farfetch/gpu", &st) == 0) remove("/tmp/farfetch/gpu");
}
#endif
