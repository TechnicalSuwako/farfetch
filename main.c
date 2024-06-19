#include <stdio.h>
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
#include "src/packages.h"
#include "src/resolution.h"
#include "src/cpu.h"
#include "src/gpu.h"
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
  getOS();
#elif defined(__NetBSD__)
#include "src/logo/netbsd.h"
  getOS();
#elif defined(__FreeBSD__)
#include "src/logo/freebsd.h"
  getOS();
#elif defined(__linux__)
  get_distro();
#include "src/logo/linux.h"
  getDistro(distroname);
#else
const char *color = MAGENTA;
const char *titlecolor = MAGENTA;
size_t logosize = 11;
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
  char *LOGO_SMALL[] = {
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

  const char *reset = RESET;
  size_t ls = logosize <= MIN_SIZE ? MIN_SIZE : logosize;
  if (issmall) {
    size_t ne = sizeof(LOGO_SMALL) / sizeof(LOGO_SMALL[0]);
    for (size_t i = 0; i < ne; i++) {
      LOGO[i] = LOGO_SMALL[i];
    }
    ls = ne >= MIN_SIZE ? MIN_SIZE : ne;
  }

  printf("%s ", LOGO[lc]);
  if (display_user_name() || display_user_host()) {
    printf(
        "%s%s%s@%s%s%s\n",
        titlecolor, display_user_name(), reset,
        titlecolor, display_user_host(), reset
    );
    lc++;
  }

  printf("%s ", LOGO[lc]);
  printf("------------------\n");
  lc++;

  printf("%s ", LOGO[lc]);
  if (display_os()) {
    printf("%sOS%s: %s\n", color, reset, display_os());
    lc++;
  }

#if defined(__linux__)
  printf("%s ", LOGO[lc]);
  if (display_distro()) {
    printf("%sDistro%s: %s\n", color, reset, display_distro());
    lc++;
  }
#endif

  printf("%s ", LOGO[lc]);
  printf("%s%s%s%s", color, "Host", reset, ": ");
  display_host_model();
  printf("\n");
  lc++;

  printf("%s ", LOGO[lc]);
  printf("%s%s%s%s", color, "Uptime", reset, ": ");
  display_days();
  printf(", ");
  display_time();
  printf("\n");
  lc++;

#if defined(__OpenBSD__)
  printf("%s ", LOGO[lc]);
  if (display_recording_audio() || display_recording_video()) {
    printf("%sRecording%s: ", color, reset);
    if (display_recording_audio()) {
      printf("audio = %s", display_recording_audio());
      if (display_recording_video()) printf(", ");
    }
    if (display_recording_video()) {
      printf("video = %s", display_recording_video());
    }
    printf("\n");
    lc++;
  }
#endif

  printf("%s ", LOGO[lc]);
  if (display_packages()) {
    printf("%sPackages%s: %s\n", color, reset, display_packages());
    lc++;
  }

  printf("%s ", LOGO[lc]);
  if (display_resolution()) {
    printf("%sResolution%s: %s\n", color, reset, display_resolution());
    lc++;
  }

  printf("%s ", LOGO[lc]);
  if (display_cpu()) {
    printf("%sCPU%s: %s\n", color, reset, display_cpu());
    lc++;
  }

  printf("%s ", LOGO[lc]);
  if (display_gpu()) {
    printf("%sGPU%s: %s\n", color, reset, display_gpu());
    lc++;
  }

  printf("%s ", LOGO[lc]);
  printf("%s%s%s%s", color, "Memory", reset, ": ");
  display_memory();
  printf("\n");
  lc++;

  for (size_t i = lc; i < ls; i++) {
    printf("%s\n", LOGO[i]);
  }

  // TODO:
  // * libc
  // * シェル
  // * 端末
  // * ストレージ

  return 0;
}
