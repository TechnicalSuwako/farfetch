#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#include "config.h"
#include "logo/colors.h"
#if defined(__OpenBSD__)
#include "logo/openbsd.h"
#elif defined(__NetBSD__)
#include "logo/netbsd.h"
#elif defined(__FreeBSD__)
#include "logo/freebsd.h"
#elif defined(__linux__)
#include "logo/linux.h"
#elif defined(__sun)
#include "logo/sunos.h"
#elif defined(__APPLE__)
#include "logo/macos.h"
#elif defined(__HAIKU__)
#include "logo/haiku.h"
#endif

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
bool isbiglogo = false;
bool issmalllogo = false;
int biglogoi = 0;
int smalllogoi = 0;
const char *customcolor;
const char *customtitlecolor;
const char *customlogobig;
const char *customlogosmall;

const char *applycolor(const char *color) {
  if (strncmp(color, "grey", 4) == 0) return GREY;
  else if (strncmp(color, "red", 3) == 0) return RED;
  else if (strncmp(color, "green", 5) == 0) return GREEN;
  else if (strncmp(color, "yellow", 6) == 0) return YELLOW;
  else if (strncmp(color, "blue", 4) == 0) return BLUE;
  else if (strncmp(color, "magenta", 7) == 0) return MAGENTA;
  else if (strncmp(color, "cyan", 4) == 0) return CYAN;
  else if (strncmp(color, "white", 5) == 0) return WHITE;
  return RESET;
}

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

  char line[256];
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

    // 色
    if (strstr(line, "set color") != NULL) {
      char color[10];
      sscanf(line, "set color %s", color);
      customcolor = applycolor(color);
    }
    if (strstr(line, "set titlecolor") != NULL) {
      char color[10];
      sscanf(line, "set titlecolor %s", color);
      customtitlecolor = applycolor(color);
    }

    // カスタムロゴ
    if (strstr(line, "define custom big logo:") != NULL) {
      isbiglogo = true;
    }
    if (strstr(line, "define custom small logo:") != NULL) {
      issmalllogo = true;
    }

    /* if (isbiglogo) { */
    /*   if (strstr(line, "EOL") != NULL) { */
    /*     isbiglogo = false; */
    /*   } else if (biglogoi < logosize) { */
    /*     LOGO[biglogoi] = strdup(line); */
    /*     biglogoi++; */
    /*   } */
    /* } */

    /* if (issmalllogo) { */
    /*   if (strstr(line, "EOL") != NULL) { */
    /*     issmalllogo = false; */
    /*   } else if (smalllogoi < MIN_SIZE) { */
    /*     LOGO_SMALL[smalllogoi] = strdup(line); */
    /*     smalllogoi++; */
    /*   } */
    /* } */
  }

  fclose(file);
  return;
}
