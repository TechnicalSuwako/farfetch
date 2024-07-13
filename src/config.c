#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "config.h"

bool isos = true;
bool ishost = true;
#if defined(__linux__) || defined(__sunos)
bool isdistro = true;
#endif
bool isuptime = true;
#if defined(__OpenBSD__)
bool isrecording = true;
#endif
bool ispackages = true;
bool islibc = true;
bool isresolution = true;
bool iswm = true;
bool isshell = true;
bool iscpu = true;
bool isgpu = true;
bool ismemory = true;
bool isstorage = true;

void getconf() {
  char *homedir = getenv("HOME");
  if (homedir == NULL) {
    perror("ホームディレクトリを受取に失敗");
    return;
  }

#if defined(__HAIKU__)
  char *basedir = "/config/settings/";
#else
  char *basedir = "/.config/";
#endif

  int alllen = snprintf(NULL, 0, "%s%s%s", homedir, basedir, "farfetch.conf") + 1;
  char *cnfpath = malloc(alllen);
  if (cnfpath == NULL) {
    perror("メモリを割当に失敗");
    return;
  }

  snprintf(cnfpath, alllen, "%s%s%s", homedir, basedir, "farfetch.conf");

  if (access(cnfpath, F_OK) != 0) {
    free(cnfpath);
    return;
  }

  FILE *file = fopen(cnfpath, "r");
  free(cnfpath);
  if (!file) {
    return;
  }

  char line[20];
  while (fgets(line, sizeof(line), file)) {
    if (line[0] == '#' || line[0] == '\n') continue;
    if (strstr(line, "hide ") != NULL) {
      if (strstr(line, "os") != NULL) isos = false;
      if (strstr(line, "host") != NULL) ishost = false;
#if defined(__linux__) || defined(__sunos)
      if (strstr(line, "distro") != NULL) isdistro = false;
#endif
      if (strstr(line, "uptime") != NULL) isuptime = false;
#if defined (__OpenBSD__)
      if (strstr(line, "recording") != NULL) isrecording = false;
#endif
      if (strstr(line, "packages") != NULL) ispackages = false;
      if (strstr(line, "libc") != NULL) islibc = false;
      if (strstr(line, "resolution") != NULL) isresolution = false;
      if (strstr(line, "wm") != NULL) iswm = false;
      if (strstr(line, "shell") != NULL) isshell = false;
      if (strstr(line, "cpu") != NULL) iscpu = false;
      if (strstr(line, "gpu") != NULL) isgpu = false;
      if (strstr(line, "memory") != NULL) ismemory = false;
      if (strstr(line, "storage") != NULL) isstorage = false;
    }
  }

  fclose(file);
  return;
}
