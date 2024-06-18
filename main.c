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
  display_user_name();
  printf("@");
  display_user_host();
  printf("------------------\n");

  printf("OS: ");
  display_os_name();
  printf(" ");
  display_os_vers();
  printf(" ");
  display_os_arch();
  printf("\n");

#if defined(__linux__)
  printf("Distro: ");
  display_distro();
  printf("\n");
#endif

  printf("Host: ");
  display_host_model();
  printf("\n");

  printf("Uptime: ");
  display_days();
  printf(", ");
  display_time();
  printf("\n");

#if defined(__OpenBSD__)
  printf("Recording: audio = ");
  display_recording_audio();
  printf(", video = ");
  display_recording_video();
  printf("\n");
#endif

  printf("CPU: ");
  display_cpu();
  printf("\n");

  printf("Memory: ");
  display_memory();
  printf("\n");

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
