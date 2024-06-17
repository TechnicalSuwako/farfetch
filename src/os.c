#include "os.h"

#include <stdio.h>
#include <string.h>

void display_os_name() {
  char buf[64];
  FILE *p = popen("uname -s", "r");
  if (!p) {
    fprintf(stderr, "「uname」コマンドを実効に失敗");
    return;
  }

  while (fgets(buf, sizeof(buf), p) != NULL) {
    buf[strcspn(buf, "\n")] = '\0';
    printf("%s", buf);
  }

  pclose(p);
}

void display_os_vers() {
  char buf[16];
  FILE *p = popen("uname -r", "r");
  if (!p) {
    fprintf(stderr, "「uname」コマンドを実効に失敗");
    return;
  }

  while (fgets(buf, sizeof(buf), p) != NULL) {
    buf[strcspn(buf, "\n")] = '\0';
    printf("%s", buf);
  }

  pclose(p);
}

void display_os_arch() {
  char buf[16];
  FILE *p = popen("uname -m", "r");
  if (!p) {
    fprintf(stderr, "「uname」コマンドを実効に失敗");
    return;
  }

  while (fgets(buf, sizeof(buf), p) != NULL) {
    buf[strcspn(buf, "\n")] = '\0';
    printf("%s", buf);
  }

  pclose(p);
}
