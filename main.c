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

int main() {
#if defined(__OpenBSD__)
#include "src/logo/openbsd.h"
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

  printf("%s ", LOGO[0]);
  printf(COLOR);
  display_user_name();
  printf(RESET);
  printf("@");
  printf(COLOR);
  display_user_host();
  printf(RESET);
  printf("%s ", LOGO[1]);
  printf("------------------\n");

  printf("%s ", LOGO[2]);
  printf(COLOR"%s%s"RESET, "OS", ": ");
  display_os_name();
  printf(" ");
  display_os_vers();
  printf(" ");
  display_os_arch();
  printf("\n");

#if defined(__linux__)
  printf(COLOR"%s%s"RESET, "Distro", ": ");
  display_distro();
  printf("\n");
#endif

  printf("%s ", LOGO[3]);
  printf(COLOR"%s%s"RESET, "Host", ": ");
  display_host_model();
  printf("\n");

  printf("%s ", LOGO[4]);
  printf(COLOR"%s%s"RESET, "Uptime", ": ");
  display_days();
  printf(", ");
  display_time();
  printf("\n");

#if defined(__OpenBSD__)
  printf("%s ", LOGO[5]);
  printf(COLOR"%s%s"RESET, "Recording", ": ");
  printf("audio = ");
  display_recording_audio();
  printf(", video = ");
  display_recording_video();
  printf("\n");
#endif

  printf("%s ", LOGO[6]);
  printf(COLOR"%s%s"RESET, "CPU", ": ");
  display_cpu();
  printf("\n");

  printf("%s ", LOGO[7]);
  printf(COLOR"%s%s"RESET, "Memory", ": ");
  display_memory();
  printf("\n");

  for (size_t i = 8; i < sizeof(LOGO) / sizeof(LOGO[0]); i++) {
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
