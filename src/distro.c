#if defined(__linux__)
#include "distro.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

const char *distroname;

const char *display_distro() {
  char buf[1288];
  char *out = NULL;
  size_t outsize = 0;

  const char *cmd = NULL;

  if (access("/bedrock/etc/bedrock-release", F_OK) != -1) {
    cmd = "cat /bedrock/etc/bedrock-release | grep '^PRETTY_NAME' | "
          "cut -d '=' -f2 | tr -d '\"'";
  } else if (access("/etc/redstar-release", F_OK) != -1) {
    cmd = "echo \"Red Star OS\" && cat /etc/redstar-release | "
          "awk -F'[^0-9]' '$0=$2'";
  } else if (access("/etc/siduction-version", F_OK) != -1) {
    cmd = "echo \"Siduction\" && lsb_release -sic | "
          "grep '^PRETTY_NAME' | cut -d '=' -f2 | tr -d '\"'";
  } else if (access("/etc/mcst_version", F_OK) != -1) {
    cmd = "echo \"OS Elbrus\" && cat /etc/mcst_version | "
          "grep '^PRETTY_NAME' | cut -d '=' -f2 | tr -d '\"'";
  } else if (access("/etc/GoboLinuxVersion", F_OK) != -1) {
    cmd = "echo \"GoboLinux\" && cat /etc/GoboLinuxVersion | "
          "grep '^PRETTY_NAME' | cut -d '=' -f2 | tr -d '\"'";
  } else if (access("/etc/os-release", F_OK) != -1) {
    cmd = "cat /etc/os-release | "
          "grep '^PRETTY_NAME' | cut -d '=' -f2 | tr -d '\"'";
  } else if (access("/usr/lib/os-release", F_OK) != -1) {
    cmd = "cat /usr/lib/os-release | "
          "grep '^PRETTY_NAME' | cut -d '=' -f2 | tr -d '\"'";
  } else if (access("/etc/openwrt_release", F_OK) != -1) {
    cmd = "cat /etc/openwrt_release | "
          "grep '^PRETTY_NAME' | cut -d '=' -f2 | tr -d '\"'";
  } else if (access("/etc/lsb-release", F_OK) != -1) {
    cmd = "cat /etc/lsb-release | "
          "grep '^DISTRIB_DESCRIPTION' | cut -d '=' -f2 | tr -d '\"'";
  } else {
    perror("不明なディストリビューション。");
  }

  FILE *p = popen(cmd, "r");
  if (!p) {
    fprintf(stderr, "ディストロを見つけられるコマンドを実効に失敗: %s", cmd);
    return NULL;
  }

  while (fgets(buf, sizeof(buf), p) != NULL) {
    buf[strcspn(buf, "\n")] = '\0';

    size_t len = strlen(buf);
    char *nout = realloc(out, outsize + len + 1);
    if (nout == NULL) {
      perror("メモリの役割に失敗");
      free(out);
      pclose(p);
      return NULL;
    }

    out = nout;

    memccpy(out + outsize, buf, sizeof(buf), len);
    outsize += len;
    out[outsize] = '\0';
  }

  pclose(p);

  return out;
}

void get_distro() {
  const char *buf = display_distro();

  if (strstr(buf, "Devuan") != NULL) distroname = "devuan";
  else if (strstr(buf, "Void Linux") != NULL) distroname = "void";
  else if (strstr(buf, "Debian") != NULL) distroname = "debian";
  else if (strstr(buf, "Arch Linux") != NULL) distroname = "arch";
  else if (strstr(buf, "Artix Linux") != NULL) distroname = "artix";
  else if (strstr(buf, "CRUX") != NULL) distroname = "crux";
  else distroname = "linux";
}
#endif
