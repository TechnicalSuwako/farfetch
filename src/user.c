#include "user.h"

#include <stdio.h>
#include <string.h>

void run_user_command(const char *command) {
  char buf[64];
#if defined(__NetBSD__) || defined(__FreeBSD__)
  FILE *p = popen(command, "r");
  if (!p) {
    snprintf(buf, sizeof(buf), "「%s」コマンドを見つけられません。", command);
    perror(buf);
    return;
  }

  while (fgets(buf, sizeof(buf), p) != NULL) {
    printf("%s", buf);
  }

  pclose(p);
  // 
#else
  FILE *f = fopen(command, "r");
  if (!f) {
    snprintf(buf, sizeof(buf), "「%s」ファイルを見つけられません。", command);
    perror(buf);
    return;
  }

  while (fgets(buf, sizeof(buf), f) != NULL) {
    printf("%s", buf);
  }

  fclose(f);
#endif
}

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
#if defined(__OpenBSD__)
  run_user_command("/etc/myname");
#elif defined(__NetBSD__)
  run_user_command("hostname");
#elif defined(__FreeBSD__)
  run_user_command("sysctl -n kern.hostname");
#else
  run_user_command("/etc/hostname");
#endif
}
