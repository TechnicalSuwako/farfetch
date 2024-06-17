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
  const char *filename;
#ifdef __OpenBSD__
  filename = "/etc/myname";
#else
  filename = "/etc/hostname";
#endif
  FILE *f = fopen(filename, "r");
  if (!f) {
    snprintf(buf, sizeof(buf), "「%s」を見つけられません。", filename);
    perror(buf);
    return;
  }

  while (fgets(buf, sizeof(buf), f) != NULL) {
    printf("%s", buf);
  }

  /* char hostname[128]; */
  /* int cnt = 0; */
  /* for (int i = 0; i < 128; i++) { */
  /*   unsigned char key; */
  /*   fread(&key, sizeof(key), 1, f); */
  /*   hostname[i] = key; */
  /*   cnt += 1; */
  /* } */

  /* hostname[cnt] = '\0'; */
  fclose(f);
}
