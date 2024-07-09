#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

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
#include "src/wm.h"
#include "src/shell.h"
#include "src/libc.h"
#include "src/cpu.h"
#include "src/gpu.h"
#include "src/memory.h"
#include "src/storage.h"

const char *sofname = "farfetch";
const char *version = "0.2.0";
#if defined(__linux__) || defined(__sun)
const char *avalopt = "ls";
#else
const char *avalopt = "s";
#endif

int opt;
#if defined(__linux__) || defined(__sun)
int islogo = 0;
#endif
int issmall = 0;
int iserr = 0;

void usage() {
#if defined(__linux__) || defined(__sun)
  printf("%s-%s\nusage: %s [-s] [-l distro]\n", sofname, version, sofname);
#else
  printf("%s-%s\nusage: %s [-%s]\n", sofname, version, sofname, avalopt);
#endif
}

void flags(int opt) {
  switch (opt) {
#if defined(__linux__) || defined(__sunos)
    case 'l':
      islogo = 1;
      break;
#endif
    case 's':
      issmall = 1;
      break;
    default:
      iserr = 1;
      usage();
      break;
  }
}

int main(int argc, char *argv[]) {
  int lc = 0;
  while ((opt = getopt(argc, argv, avalopt)) != -1) {
    flags(opt);
  }

  if (iserr == 1) {
    return 1;
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
#elif defined(__APPLE__)
#include "src/logo/macos.h"
  getOS();
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
  const char *winman = display_wm();
  if (!winman) minsize--;
#if !defined(__APPLE__)
  else free((void *)winman);
#endif
  const char *clang = display_libc();
  if (clang) minsize++;
  const char *store = display_storage();
  if (!store) minsize--;
  else free((void *)store);
  const char *graph = display_gpu();
  if (!graph) minsize--;
  else free((void *)graph);

  const char *reset = RESET;
  size_t ls = logosize <= (size_t)minsize ? (size_t)minsize : logosize;
#if defined(__linux__) || defined(__sun)
  if (islogo) {
    logoname = argv[2];
    getDistro(logoname);
  }
#endif

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

  const char *wm = display_wm();
  if (wm) {
    printf("%s ", LOGO[lc]);
    printf("%sWM%s: %s\n", color, reset, wm);
#if !defined(__APPLE__)
    free((void *)wm);
#endif
    lc++;
  }

  const char *shell = display_shell();
  if (shell) {
    printf("%s ", LOGO[lc]);
    printf("%sShell%s: %s\n", color, reset, shell);
    free((void *)shell);
    lc++;
  }

  const char *libc = display_libc();
  if (libc) {
    printf("%s ", LOGO[lc]);
    printf("%slibc%s: %s\n", color, reset, libc);
    lc++;
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

  const char *storage = display_storage();
  if (storage) {
    printf("%s ", LOGO[lc]);
    printf("%sStorage%s: %s\n", color, reset, storage);
    lc++;
    free((void *)storage);
  }

  for (size_t i = lc; i < ls; i++) {
    printf("%s\n", LOGO[i]);
  }

  return 0;
}
