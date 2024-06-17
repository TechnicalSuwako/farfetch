#include "user.h"

#include <stdio.h>
#include <string.h>

void display_user_name() {
  char buf[128];
  FILE *p = popen("whoami", "r");
  if (!p) {
    fprintf(stderr, "「whoami」コマンドを実効に失敗");
    return;
  }

  while (fgets(buf, sizeof(buf), p) != NULL) {
    buf[strcspn(buf, "\n")] = '\0';
    printf("%s", buf);
  }

  pclose(p);
}

void display_user_host() {
  char buf[64];
#ifdef __NetBSD__
  FILE *p = popen("hostname", "r");
  if (!p) {
    perror("hostnameコマンドを見つけられません。");
    return;
  }

  while (fgets(buf, sizeof(buf), p) != NULL) {
    buf[strcspn(buf, "\n")] = '\0';
    printf("%s", buf);
  }

  pclose(p);
#else
  const char *filename;
#ifdef __OpenBSD__
  filename = "/etc/myname";
#else
  filename = "/etc/hostname";
#endif
  FILE *f = fopen(filename, "r");
  if (!f) {
    snprintf(buf, sizeof(buf), "「%s」ファイルを見つけられません。", filename);
    perror(buf);
    return;
  }

  while (fgets(buf, sizeof(buf), f) != NULL) {
    printf("%s", buf);
  }

  fclose(f);
#endif
}
