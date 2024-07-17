#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

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

bool containvocab(const char *line, const char *word) {
  const char *p = line;
  size_t len = strlen(word);
  while ((p = strstr(p, word)) != NULL) {
    if (
      (p == line || !isalnum((unsigned char)p[-1])) &&
      !isalnum((unsigned char)p[len])
    ) return true;

    p += len;
  }

  return false;
}

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
      if (containvocab(line, "os")) isos = false;
      if (containvocab(line, "host")) ishost = false;
#if defined(__linux__) || defined(__sunos)
      if (containvocab(line, "distro")) isdistro = false;
#endif
      if (containvocab(line, "uptime")) isuptime = false;
#if defined (__OpenBSD__)
      if (containvocab(line, "recording")) isrecording = false;
#endif
      if (containvocab(line, "packages")) ispackages = false;
      if (containvocab(line, "libc")) islibc = false;
      if (containvocab(line, "resolution")) isresolution = false;
      if (containvocab(line, "wm")) iswm = false;
      if (containvocab(line, "shell")) isshell = false;
      if (containvocab(line, "cpu")) iscpu = false;
      if (containvocab(line, "gpu")) isgpu = false;
      if (containvocab(line, "memory")) ismemory = false;
      if (containvocab(line, "storage")) isstorage = false;
    }
  }

  fclose(file);
  return;
}
