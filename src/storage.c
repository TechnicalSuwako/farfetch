#include "storage.h"
#include "common.h"

#if defined(__HAIKU__)
#include <stdio.h>
#endif
#include <string.h>
#include <stdlib.h>

const char *display_storage() {
  const char *excode = run_command_s("zpool list 2>/dev/null || echo $?");
  if (excode != NULL && (strncmp(excode, "127", strlen("127")) == 0)) {
    free((void *)excode);
#if defined(__HAIKU__)
    long long int usedstore = 0;
    long long int totalstore = run_command_lld("df -h | "
        "awk '/^\\/boot / {printf \"%s\", $3}'");
    long long int freestore = run_command_lld("df -h | "
        "awk '/^\\/boot / {printf \"%s\", $5}'");
    const char *totunit = run_command_s("df -h | "
        "awk '/^\\/boot / {printf \"%s\", $4}'");
    const char *freunit = run_command_s("df -h | "
        "awk '/^\\/boot / {printf \"%s\", $6}'");
    char tu[2] = {'\0'};
    char uu[2] = {'\0'};

    if (strncmp(totunit, "TiB", 3) == 0) tu[0] = 'T';
    else if (strncmp(totunit, "GiB", 3) == 0) tu[0] = 'G';
    else if (strncmp(totunit, "MiB", 3) == 0) tu[0] = 'M';
    else if (strncmp(totunit, "KiB", 3) == 0) tu[0] = 'K';
    else tu[0] = 'B';
    tu[1] = '\0';

    if (strncmp(freunit, "TiB", 3) == 0) uu[0] = 'T';
    else if (strncmp(freunit, "GiB", 3) == 0) uu[0] = 'G';
    else if (strncmp(freunit, "MiB", 3) == 0) uu[0] = 'M';
    else if (strncmp(freunit, "KiB", 3) == 0) uu[0] = 'K';
    else uu[0] = 'B';
    uu[1] = '\0';

    if (strncmp(totunit, freunit, 3) != 0) {
      if (strncmp(totunit, "TiB", 3) == 0 && strncmp(freunit, "GiB", 3) == 0)
        usedstore = (totalstore - (freestore / 1024));
      else if (strncmp(totunit, "GiB", 3) == 0 && strncmp(freunit, "MiB", 3) == 0)
        usedstore = (totalstore - (freestore / 1024));
      else if (strncmp(totunit, "MiB", 3) == 0 && strncmp(freunit, "KiB", 3) == 0)
        usedstore = (totalstore - (freestore / 1024));
      else if (strncmp(totunit, "KiB", 3) == 0 && strncmp(freunit, "B", 3) == 0)
        usedstore = (totalstore - (freestore / 1024));
      else if (strncmp(totunit, "TiB", 3) == 0 && strncmp(freunit, "MiB", 3) == 0)
        usedstore = (totalstore - (freestore / 1024 / 1024));
      else if (strncmp(totunit, "GiB", 3) == 0 && strncmp(freunit, "KiB", 3) == 0)
        usedstore = (totalstore - (freestore / 1024 / 1024));
      else if (strncmp(totunit, "MiB", 3) == 0 && strncmp(freunit, "B", 3) == 0)
        usedstore = (totalstore - (freestore / 1024 / 1024));
      else if (strncmp(totunit, "TiB", 3) == 0 && strncmp(freunit, "KiB", 3) == 0)
        usedstore = (totalstore - (freestore / 1024 / 1024 / 1024));
      else if (strncmp(totunit, "GiB", 3) == 0 && strncmp(freunit, "B", 3) == 0)
        usedstore = (totalstore - (freestore / 1024 / 1024 / 1024));
      else if (strncmp(totunit, "TiB", 3) == 0 && strncmp(freunit, "B", 3) == 0)
        usedstore = (totalstore - (freestore / 1024 / 1024 / 1024 / 1024));
    } else {
      usedstore = (totalstore - freestore);
    }

    char *cmd = (char *)malloc(128 * sizeof(char));
    if (!cmd) {
      return NULL;
    }

    snprintf(cmd, 128, "/boot: %lld%s / %lld%s", usedstore, uu, totalstore, tu);

    return cmd;
#else
    return run_command_s("df -h | "
        "awk '/^\\/dev\\// {printf \"%s: %s / %s, \", $1, $3, $2}' | "
        "awk '{sub(/, $/, \"\"); print}'");
#endif
  }

  free((void *)excode);
  const char *test = run_command_s("zpool list 2>/dev/null || echo $?");
  if (strncmp(test, "1", strlen("1")) == 0) {
    free((void *)test);
    return NULL;
  }

  free((void *)test);
  return run_command_s("zpool list | "
      "awk 'NR>1 {printf \"%s: %s / %s, \", $1, $3, $2}' | "
      "awk '{sub(/, $/, \"\"); print}'");
}
