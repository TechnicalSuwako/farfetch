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

bool islogob = true;
bool islogos = false;
bool islogod = true;
bool islogocustom = false;
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
bool mkbiglogo = false;
bool mksmalllogo = false;
size_t biglogoi = 0;
size_t smalllogoi = 0;
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

char *colrep(const char *str, const char *old, const char *new) {
  char *res;
  int i, count = 0;
  int nlen = strlen(new);
  int olen = strlen(old);

  for (i = 0; str[i] != '\0'; i++) {
    if (strstr(&str[i], old) == &str[i]) {
      count++;
      i += olen - 1;
    }
  }

  res = (char *)malloc(i + count * (nlen - olen) + 1);
  if (!res) {
    return NULL;
  }

  i = 0;
  while (*str) {
    if (strstr(str, old) == str) {
      memcpy(&res[i], new, strlen(new));
      i += nlen;
      str += olen;
    } else {
      res[i++] = *str++;
    }
  }

  res[i] = '\0';
  return res;
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
      if (containvocab(line, "logo")) islogod = false;
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

    // デフォルトは大きいロゴ
    if (strstr(line, "show logo") != NULL) {
      puts("show logo");
      if (containvocab(line, "small")) {
        puts("small");
        islogob = false;
        islogos = true;
      } else {
        puts("big");
        islogob = true;
        islogos = false;
      }

      if (containvocab(line, "custom")) {
        puts("custom");
        islogocustom = true;
      }
    }

    // カスタムロゴ
    if (strstr(line, "define custom big logo:") != NULL) {
      mkbiglogo = true;
    }
    if (strstr(line, "define custom small logo:") != NULL) {
      mksmalllogo = true;
    }

    if (mkbiglogo && islogocustom && islogob) {
      isbiglogo = true;
      if (strstr(line, "define custom big logo:") != NULL) {
        continue;
      } else if (strstr(line, "EOL") != NULL) {
        mkbiglogo = false;
      } else if (biglogoi < logosize) {
        LOGO[biglogoi] = strdup(line);
        LOGO[biglogoi] = colrep(LOGO[biglogoi], "[GREY]", GREY);
        LOGO[biglogoi] = colrep(LOGO[biglogoi], "[RED]", RED);
        LOGO[biglogoi] = colrep(LOGO[biglogoi], "[GREEN]", GREEN);
        LOGO[biglogoi] = colrep(LOGO[biglogoi], "[YELLOW]", YELLOW);
        LOGO[biglogoi] = colrep(LOGO[biglogoi], "[BLUE]", BLUE);
        LOGO[biglogoi] = colrep(LOGO[biglogoi], "[MAGENTA]", MAGENTA);
        LOGO[biglogoi] = colrep(LOGO[biglogoi], "[CYAN]", CYAN);
        LOGO[biglogoi] = colrep(LOGO[biglogoi], "[WHITE]", WHITE);
        LOGO[biglogoi] = colrep(LOGO[biglogoi], "[RESET]", RESET);
        size_t len = strlen(LOGO[biglogoi]);
        if (len > 0 && LOGO[biglogoi][len - 1] == '\n') {
          LOGO[biglogoi][len - 1] = '\0';
        }
        biglogoi++;
      }
    }

    if (mksmalllogo && islogocustom && islogos) {
      issmalllogo = true;
      if (strstr(line, "define custom small logo:") != NULL) {
        continue;
      } else if (strstr(line, "EOL") != NULL) {
        mksmalllogo = false;
      } else if (smalllogoi < MIN_SIZE) {
        LOGO_SMALL[smalllogoi] = strdup(line);
        LOGO_SMALL[smalllogoi] = colrep(LOGO_SMALL[smalllogoi], "[GREY]", GREY);
        LOGO_SMALL[smalllogoi] = colrep(LOGO_SMALL[smalllogoi], "[RED]", RED);
        LOGO_SMALL[smalllogoi] = colrep(LOGO_SMALL[smalllogoi], "[GREEN]", GREEN);
        LOGO_SMALL[smalllogoi] = colrep(LOGO_SMALL[smalllogoi], "[YELLOW]", YELLOW);
        LOGO_SMALL[smalllogoi] = colrep(LOGO_SMALL[smalllogoi], "[BLUE]", BLUE);
        LOGO_SMALL[smalllogoi] = colrep(LOGO_SMALL[smalllogoi], "[MAGENTA]", MAGENTA);
        LOGO_SMALL[smalllogoi] = colrep(LOGO_SMALL[smalllogoi], "[CYAN]", CYAN);
        LOGO_SMALL[smalllogoi] = colrep(LOGO_SMALL[smalllogoi], "[WHITE]", WHITE);
        LOGO_SMALL[smalllogoi] = colrep(LOGO_SMALL[smalllogoi], "[RESET]", RESET);
        size_t len = strlen(LOGO_SMALL[smalllogoi]);
        if (len > 0 && LOGO_SMALL[smalllogoi][len - 1] == '\n') {
          LOGO_SMALL[smalllogoi][len - 1] = '\0';
        }
        smalllogoi++;
      }
    }
  }

  fclose(file);
  return;
}
