#include "host.h"

#include <stdio.h>
#include <string.h>

#if defined(__linux__)
#include <unistd.h>
#elif defined(__APPLE__)
#include <stdlib.h>
#endif

void run_command(const char *command) {
  char buf[64];

  FILE *p = popen(command, "r");
  if (!p) {
    fprintf(stderr, "ホストコマンドを実効に失敗: %s", command);
    return;
  }

  while (fgets(buf, sizeof(buf), p) != NULL) {
    buf[strcspn(buf, "\n")] = '\0';
    printf("%s", buf);
  }

  pclose(p);
}

void display_host_model() {
#if defined(__OpenBSD__) || defined(__FreeBSD__) || \
  defined(__DragonFly__)
  run_command("sysctl -n hw.vendor && echo \" \" && "
              "sysctl -n hw.version && echo \" \" &&"
              "sysctl -n hw.product");
#elif defined(__NetBSD__)
  run_command("sysctl -n machdep.dmi.system-vendor && "
              "echo \" \" && sysctl -n machdep.dmi.system-version && "
              "echo \" \" && sysctl -n machdep.dmi.system-product");
#elif defined(__sun)
  run_command("prtconf -b | awk -F':' '/banner-name/ {printf $2}'");
#elif defined(__linux__)
  const char *cmd1 = NULL;
  const char *cmd2 = NULL;
  if (access("/system/app/", F_OK) != -1) {
    cmd1 = "getprop ro.product.brand";
    cmd2 = "getprop ro.product.model";
  } else if (
      access("/sys/devices/virtual/dmi/id/product_name", F_OK) != -1 ||
      access("/sys/devices/virtual/dmi/id/product_version", F_OK) != 1
  ) {
    cmd1 = "cat /sys/devices/virtual/dmi/id/product_name";
    cmd2 = "cat /sys/devices/virtual/dmi/id/product_version";
  } else if (access("/sys/firmware/base/model", F_OK) != -1) {
    cmd1 = "cat /sys/firmware/devicetree/base/model";
  } else if (access("/tmp/sysinfo/model", F_OK) != 1) {
    cmd1 = "cat /tmp/sysinfo/model";
  }

  if (!cmd1) {
    printf("Unknown");
  } else {
    run_command(cmd1);
  }

  if (cmd2) {
    printf(" ");
    run_command(cmd2);
  }
#elif defined(__APPLE__)
  run_command("sysctl -n hw.model");

  FILE *p = popen("kextstat | grep -F -e \"FakeSMC\" -e \"VirtualSMC\"", "r");
  if (!p) {
    fprintf(stderr, "ホストコマンドを実効に失敗");
    return;
  }

  while (fgets(buf, sizeof(buf), p) != NULL) {
    buf[strcspn(buf, "\n")] = '\0';
    printf("%s", buf);
  }

  pclose(p);
#endif
}
