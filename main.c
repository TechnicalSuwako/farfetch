#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "src/user.h"
#include "src/os.h"
#if defined(__linux__)
#include "src/distro.h"
#endif
#include "src/host.h"
#include "src/uptime.h"
#if defined(__OpenBSD__)
#include "src/recording.h"
#endif
#include "src/cpu.h"
#include "src/memory.h"

const char *sofname = "farfetch";
const char *version = "0.0.1";

int main(int argc, char *argv[]) {
  int lc = 0;
  int issmall = 0;
  if (argc == 2 && strncmp(argv[1], "-s", strlen("-s")) == 0) {
    issmall = 1;
  }
#if defined(__OpenBSD__)
#include "src/logo/openbsd.h"
#elif defined(__NetBSD__)
#include "src/logo/netbsd.h"
#elif defined(__FreeBSD__)
#include "src/logo/freebsd.h"
#else
#define COLOR "\e[1;30m"
#define RESET "\e[0m"
  char *LOGO[] = {
"    ⢀⣀⣀⡀⠀⠀⠀⠀⠀⠀⠀⣠⠾⠛⠶⣄⢀⣠⣤⠴⢦⡀⠀⠀⠀⠀",
"⠀⠀⠀⢠⡿⠉⠉⠉⠛⠶⠶⠖⠒⠒⣾⠋⠀⢀⣀⣙⣯⡁⠀⠀⠀⣿⠀⠀⠀⠀",
"⠀⠀⠀⢸⡇⠀⠀⠀⠀⠀⠀⠀⠀⢸⡏⠀⠀⢯⣼⠋⠉⠙⢶⠞⠛⠻⣆⠀⠀⠀",
"⠀⠀⠀⢸⣧⠆⠀⠀⠀⠀⠀⠀⠀⠀⠻⣦⣤⡤⢿⡀⠀⢀⣼⣷⠀⠀⣽⠀⠀⠀",
"⠀⠀⠀⣼⠃⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠉⠙⢏⡉⠁⣠⡾⣇⠀⠀⠀",
"⠀⠀⢰⡏⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠙⠋⠉⠀⢻⡀⠀⠀",
"⣀⣠⣼⣧⣤⠀⠀⠀⣀⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣀⡀⠀⠀⠐⠖⢻⡟⠓⠒",
"⠀⠀⠈⣷⣀⡀⠀⠘⠿⠇⠀⠀⠀⢀⣀⣀⠀⠀⠀⠀⠿⠟⠀⠀⠀⠲⣾⠦⢤⠀",
"⠀⠀⠋⠙⣧⣀⡀⠀⠀⠀⠀⠀⠀⠘⠦⠼⠃⠀⠀⠀⠀⠀⠀⠀⢤⣼⣏⠀⠀⠀",
"⠀⠀⢀⠴⠚⠻⢧⣄⣀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣀⣤⠞⠉⠉⠓⠀⠀",
"⠀⠀⠀⠀⠀⠀⠀⠈⠉⠛⠛⠶⠶⠶⣶⣤⣴⡶⠶⠶⠟⠛⠉⠀⠀⠀⠀⠀⠀⠀"
  };
#endif

  size_t ls = sizeof(LOGO) / sizeof(LOGO[0]);
  if (issmall) {
    size_t ne = sizeof(LOGO_SMALL) / sizeof(LOGO_SMALL[0]);
    for (size_t i = 0; i < ne; i++) {
      LOGO[i] = LOGO_SMALL[i];
    }
    ls = ne;
  }

  printf("%s ", LOGO[lc]);
  printf(COLOR);
  display_user_name();
  printf(RESET);
  printf("@");
  printf(COLOR);
  display_user_host();
  printf(RESET);
  lc++;
  printf("%s ", LOGO[lc]);
  printf("------------------\n");
  lc++;

  printf("%s ", LOGO[lc]);
  printf(COLOR"%s%s"RESET, "OS", ": ");
  display_os_name();
  printf(" ");
  display_os_vers();
  printf(" ");
  display_os_arch();
  printf("\n");
  lc++;

#if defined(__linux__)
  printf("%s ", LOGO[lc]);
  printf(COLOR"%s%s"RESET, "Distro", ": ");
  display_distro();
  printf("\n");
  lc++;
#endif

  printf("%s ", LOGO[lc]);
  printf(COLOR"%s%s"RESET, "Host", ": ");
  display_host_model();
  printf("\n");
  lc++;

  printf("%s ", LOGO[lc]);
  printf(COLOR"%s%s"RESET, "Uptime", ": ");
  display_days();
  printf(", ");
  display_time();
  printf("\n");
  lc++;

#if defined(__OpenBSD__)
  printf("%s ", LOGO[lc]);
  printf(COLOR"%s%s"RESET, "Recording", ": ");
  printf("audio = ");
  display_recording_audio();
  printf(", video = ");
  display_recording_video();
  printf("\n");
  lc++;
#endif

  printf("%s ", LOGO[lc]);
  printf(COLOR"%s%s"RESET, "CPU", ": ");
  display_cpu();
  printf("\n");
  lc++;

  printf("%s ", LOGO[lc]);
  printf(COLOR"%s%s"RESET, "Memory", ": ");
  display_memory();
  printf("\n");
  lc++;

  for (size_t i = lc; i < ls; i++) {
    printf("%s\n", LOGO[i]);
  }

  // TODO:
  // * ロゴ
  // * パッケージ
  // * libc
  // * シェル
  // * 解像度
  // * 端末
  // * GPU
  // * ストレージ
  return 0;
}
