#if defined(__linux__) || defined(__sun)
#include "distro.h"
#include "common.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

const char *distroname;

bool is_distro(const char *buf) {
#if defined(__sunos)
  if (strncmp(buf, "openindiana") == 0) return 1;
  else if (strncmp(buf, "omnios") == 0) return 1;
  else if (strncmp(buf, "solaris") == 0) return 1;
#else
  if (strncmp(buf, "alpine", sizeof("alpine")) == 0) return 1;
  else if (strncmp(buf, "arch", sizeof("arch")) == 0) return 1;
  else if (strncmp(buf, "arco", sizeof("arco")) == 0) return 1;
  else if (strncmp(buf, "artix", sizeof("artix")) == 0) return 1;
  else if (strncmp(buf, "centos", sizeof("centos")) == 0) return 1;
  else if (strncmp(buf, "crux", sizeof("crux")) == 0) return 1;
  else if (strncmp(buf, "debian", sizeof("debian")) == 0) return 1;
  else if (strncmp(buf, "devuan", sizeof("devuan")) == 0) return 1;
  else if (strncmp(buf, "fedora", sizeof("fedora")) == 0) return 1;
  else if (strncmp(buf, "gentoo", sizeof("gentoo")) == 0) return 1;
  else if (strncmp(buf, "hyperbola", sizeof("hyperbola")) == 0) return 1;
  else if (strncmp(buf, "linuxmint", sizeof("linuxmint")) == 0) return 1;
  else if (strncmp(buf, "manjaro", sizeof("manjaro")) == 0) return 1;
  else if (strncmp(buf, "opensuse", sizeof("opensuse")) == 0) return 1;
  else if (strncmp(buf, "parabola", sizeof("parabola")) == 0) return 1;
  else if (strncmp(buf, "popos", sizeof("popos")) == 0) return 1;
  else if (strncmp(buf, "postmarketos", sizeof("postmarketos")) == 0) return 1;
  else if (strncmp(buf, "redhat", sizeof("redhat")) == 0) return 1;
  else if (strncmp(buf, "rocky", sizeof("rocky")) == 0) return 1;
  else if (strncmp(buf, "ubuntu", sizeof("ubuntu")) == 0) return 1;
  else if (strncmp(buf, "void", sizeof("void")) == 0) return 1;
  else if (strncmp(buf, "linux", sizeof("linux"))) return 1;
#endif

  return 0;
}

const char *display_distro() {
  char buf[1288];
  char *out = NULL;
  size_t outsize = 0;

  const char *cmd = from_cache("/tmp/farfetch/distro");

  if (cmd) {
    return cmd;
  }

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
    cmd = "if grep -q \"^PRETTY_NAME=\" /etc/os-release; then "
          "grep '^PRETTY_NAME=' /etc/os-release | cut -d \"=\" -f2 | tr -d '\"'; "
          "else "
          "grep '^NAME=' /etc/os-release | cut -d \"=\" -f2 | tr -d '\"'; "
          "fi";
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

  to_cache("/tmp/farfetch/distro", out);
  pclose(p);

  return out;
}

void get_distro() {
  const char *buf = display_distro();
  if (!buf) {
#if defined(__sunos)
    distroname = "solaris";
#else
    distroname = "linux";
#endif
    return;
  }

  if (strstr(buf, "Alpine") != NULL) distroname = "alpine";
  else if (strstr(buf, "Arch Linux") != NULL) distroname = "arch";
  else if (strstr(buf, "ArcoLinux") != NULL) distroname = "arco";
  else if (strstr(buf, "Artix Linux") != NULL) distroname = "artix";
  else if (strstr(buf, "CentOS") != NULL) distroname = "centos";
  else if (strstr(buf, "CRUX") != NULL) distroname = "crux";
  else if (strstr(buf, "Debian") != NULL) distroname = "debian";
  else if (strstr(buf, "Devuan") != NULL) distroname = "devuan";
  else if (strstr(buf, "Fedora") != NULL) distroname = "fedora";
  else if (strstr(buf, "Gentoo") != NULL) distroname = "gentoo";
  else if (strstr(buf, "Hyperbola") != NULL) distroname = "hyperbola";
  else if (strstr(buf, "Linux Mint") != NULL) distroname = "linuxmint";
  else if (strstr(buf, "Manjaro") != NULL) distroname = "manjaro";
  else if (strstr(buf, "OpenIndiana") != NULL) distroname = "openindiana";
  else if (strstr(buf, "openSUSE") != NULL) distroname = "opensuse";
  else if (strstr(buf, "OmniOS") != NULL) distroname = "omnios";
  else if (strstr(buf, "Parabola") != NULL) distroname = "parabola";
  else if (strstr(buf, "Pop!_OS") != NULL) distroname = "popos";
  else if (strstr(buf, "postmarketOS") != NULL) distroname = "postmarketos";
  else if (strstr(buf, "Red Hat") != NULL) distroname = "redhat";
  else if (strstr(buf, "Rocky") != NULL) distroname = "rocky";
  else if (strstr(buf, "Ubuntu") != NULL) distroname = "ubuntu";
  else if (strstr(buf, "Void Linux") != NULL) distroname = "void";
#if defined(__sunos)
  else distroname = "solaris";
#else
  else distroname = "linux";
#endif

  if (strncmp(distroname, "ubuntu", strlen("ubuntu")) == 0) {
    const char *desktop = run_command_s("echo $XDG_CURRENT_DESKTOP");
    if (strncmp(desktop, "KDE", strlen("KDE")) == 0) distroname = "kubuntu";
    else if (strncmp(desktop, "XFCE", strlen("XFCE")) == 0) distroname = "xubuntu";
    else if (strncmp(desktop, "LXQt", strlen("LXQt")) == 0) distroname = "lubuntu";
    else if (strncmp(desktop, "MATE", strlen("MATE")) == 0) distroname = "ubuntumate";
    else if (strncmp(desktop, "X-Cinnamon", strlen("X-Cinnamon")) == 0)
      distroname = "ubuntucinnamon";
    else if (strncmp(desktop, "Budgie:GNOME", strlen("Budgie:GNOME")) == 0)
      distroname = "ubuntubudgie";
    else if (strncmp(desktop, "Lomiri", strlen("Lomiri")) == 0)
      distroname = "ubuntulomiri";
    else if (strncmp(
          desktop,
          "Unity:Unity7:ubuntu",
          strlen("Unity:Unity7:ubuntu")
    ) == 0)
      distroname = "ubuntuunity";
  }
}
#endif
