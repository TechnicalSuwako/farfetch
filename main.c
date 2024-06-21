#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "src/user.h"
#include "src/os.h"
#if defined(__linux__) || defined(__sun)
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
#elif defined(__sun)
  get_distro();
#include "src/logo/sunos.h"
  getDistro(distroname);
#else
#include "src/logo/colors.h"
  const char *color = MAGENTA;
  const char *titlecolor = MAGENTA;
  size_t logosize = 11;
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

  int minsize = MIN_SIZE;

  const char *res = display_resolution();
  if (!res) minsize--;
  else free((void *)res);

  const char *reset = RESET;
  size_t ls = logosize <= (size_t)minsize ? (size_t)minsize : logosize;
  if (issmall) {
    size_t ne = sizeof(LOGO_SMALL) / sizeof(LOGO_SMALL[0]);
    for (size_t i = 0; i < ne; i++) {
      LOGO[i] = LOGO_SMALL[i];
    }
    ls = ne >= (size_t)minsize ? (size_t)minsize : ne;
  }

  const char *name = display_user_name();
  const char *host = display_user_host();
  if (name || host) {
    printf("%s ", LOGO[lc]);
    if (name) printf("%s%s%s",titlecolor, name, reset);
    if (name && host) printf("@");
    if (host) printf("%s%s%s", titlecolor, host, reset);
    printf("\n");
    if (name) free((void *)name);
    if (host) free((void *)host);
    lc++;
  }

  printf("%s ", LOGO[lc]);
  printf("------------------\n");
  lc++;

  const char *os = display_os();
  if (os) {
    printf("%s ", LOGO[lc]);
    printf("%sOS%s: %s\n", color, reset, os);
    free((void *)os);
    lc++;
  }

#if defined(__linux__) || defined(__sun)
  const char *distroo = display_distro();
  if (distroo) {
    printf("%s ", LOGO[lc]);
    printf("%sDistro%s: %s\n", color, reset, distroo);
    lc++;
    free((void *)distroo);
  }
#endif

  printf("%s ", LOGO[lc]);
  printf("%s%s%s%s", color, "Host", reset, ": ");
  display_host_model();
  printf("\n");
  lc++;

  const char *days = display_days();
  const char *time = display_time();
  if (days || time) {
    printf("%s ", LOGO[lc]);
    printf("%s%s%s%s", color, "Uptime", reset, ": ");
    if (days) {
      printf("%s", days);
      if (time) printf(" ");
    }
    if (time) {
      printf("%s", time);
    }
    printf("\n");
    if (days) free((void *)days);
    if (time) free((void *)time);
    lc++;
  }

#if defined(__OpenBSD__)
  const char *audio = display_recording_audio();
  const char *video = display_recording_video();
  if (audio || video) {
    printf("%s ", LOGO[lc]);
    printf("%sRecording%s: ", color, reset);
    if (audio) {
      printf("audio = %s", audio);
      if (video) printf(", ");
    }
    if (video) {
      printf("video = %s", video);
    }
    printf("\n");
    if (audio) free((void *)audio);
    if (video) free((void *)video);
    lc++;
  }
#endif

  const char *packages = display_packages();
  if (packages) {
    printf("%s ", LOGO[lc]);
    printf("%sPackages%s: %s\n", color, reset, packages);
    lc++;
    free((void *)packages);
  }

  const char *resolution = display_resolution();
  if (resolution) {
    printf("%s ", LOGO[lc]);
    printf("%sResolution%s: %s\n", color, reset, resolution);
    lc++;
    free((void *)resolution);
  }

  const char *cpu = display_cpu();
  if (cpu) {
    printf("%s ", LOGO[lc]);
    printf("%sCPU%s: %s\n", color, reset, cpu);
    lc++;
    free((void *)cpu);
  }

  const char *gpu = display_gpu();
  if (gpu) {
    printf("%s ", LOGO[lc]);
    printf("%sGPU%s: %s\n", color, reset, gpu);
    lc++;
    free((void *)gpu);
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
