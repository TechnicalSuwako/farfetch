#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "src/user.h"
#include "src/os.h"
#include "src/host.h"
#if defined(__linux__)
#include "src/distro.h"
#endif
#include "src/memory.h"

const char *sofname = "farfetch";
const char *version = "0.0.1";

int main() {
  display_user_name();
  printf("@");
  display_user_host();
  printf("\n------------------\n");

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

  printf("Memory: ");
  display_memory();
  printf("\n");

  // TODO:
  // * ロゴ
  // * カーネル(LinuxとIllumosのみ)
  // * 起動時間
  // * パッケージ
  // * libc
  // * シェル
  // * 解像度
  // * 端末
  // * CPU
  // * GPU
  // * ストレージ
  return 0;
}
