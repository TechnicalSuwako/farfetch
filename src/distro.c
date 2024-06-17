#if defined(__linux__)
#include "distro.h"

#include <stdio.h>
#include <string.h>

#include <unistd.h>

void display_distro() {
  char buf[64];
  const char *cmd;

  if (access("/bedrock/etc/bedrock-release", F_OK) != -1) {
    cmd = "cat /bedrock/etc/bedrock-release";
  } else if (access("/etc/redstar-release", F_OK) != -1) {
    cmd = "echo \"Red Star OS\" && cat /etc/redstar-release | awk -F'[^0-9]' '$0=$2'";
  } else if (access("/etc/siduction-version", F_OK) != -1) {
    cmd = "echo \"Siduction\" && lsb_release -sic";
  } else if (access("/etc/mcst_version", F_OK) != -1) {
    cmd = "echo \"OS Elbrus\" && cat /etc/mcst_version";
  } else if (access("/etc/GoboLinuxVersion", F_OK) != -1) {
    cmd = "echo \"GoboLinux\" && cat /etc/GoboLinuxVersion";
  } else if (access("/etc/os-release", F_OK) != -1) {
    cmd = "cat /etc/os-release";
  } else if (access("/usr/lib/os-release", F_OK) != -1) {
    cmd = "cat /usr/lib/os-release";
  } else if (access("/etc/openwrt_release", F_OK) != -1) {
    cmd = "cat /etc/openwrt_release";
  } else if (access("/etc/lsb-release", F_OK) != -1) {
    cmd = "cat /etc/lsb-release";
  } else {
    perror("不明なディストリビューション。");
  }

  FILE *p = popen(cmd, "r");
  if (!p) {
    fprintf(stderr, "ディストロを見つけられるコマンドを実効に失敗: %s", cmd);
    return;
  }

  while (fgets(buf, sizeof(buf), p) != NULL) {
    buf[strcspn(buf, "\n")] = '\0';
    printf("%s", buf);
  }

  pclose(p);
}
#endif
