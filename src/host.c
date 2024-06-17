#include "host.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if defined(__linux__)
#include <unistd.h>

int skip = 0;
#endif

const char *run_host_command(const char *command) {
  char buf[64];
  char *out = NULL;
  size_t outsize = 0;

  FILE *p = popen(command, "r");
  if (!p) {
    fprintf(stderr, "ホストコマンドを実効に失敗: %s", command);
    return NULL;
  }

  while (fgets(buf, sizeof(buf), p) != NULL) {
    buf[strcspn(buf, "\n")] = '\0';
#if defined(__linux__)
    if (
        strstr(buf, "To be filled by O.E.M.") != NULL ||
        strstr(buf, "To Be Filled By O.E.M.") != NULL ||
        strstr(buf, "OEM") != NULL ||
        strstr(buf, "Not Applicable") != NULL ||
        strstr(buf, "System Product Name") != NULL ||
        strstr(buf, "System Version") != NULL ||
        strstr(buf, "Undefined") != NULL ||
        strstr(buf, "Default string") != NULL ||
        strstr(buf, "Not Specified") != NULL ||
        strstr(buf, "Type1ProductConfigId") != NULL ||
        strstr(buf, "INVALID") != NULL ||
        strstr(buf, "All Series") != NULL
    ) {
      skip = 1;
      break;
    }
#endif

    size_t len = strlen(buf);
    char *nout = realloc(out, outsize + len + 1);
    if (nout == NULL) {
      perror("メモリの役割に失敗");
      free(out);
      pclose(p);
      return NULL;
    }

    out = nout;

    memcpy(out + outsize, buf, len);
    outsize += len;
    out[outsize] = '\0';
  }

  pclose(p);

  return out;
}

void display_host_model() {
#if defined(__OpenBSD__)
  printf("%s", run_host_command("sysctl -n hw.vendor && echo \" \" && "
              "sysctl -n hw.version && echo \" \" &&"
              "sysctl -n hw.product"));
#elif defined(__FreeBSD__)
  const char *family = run_host_command("kenv | grep smbios.system.family | "
        "sed 's/\"//g' | sed 's/smbios.system.family=//'");
  if (strncmp(family, " ", strlen(family)) == 0) {
    family = run_host_command("kenv | grep smbios.system.version | "
        "sed 's/\"//g' | sed 's/smbios.system.version=//'");
  }
  const char *product = run_host_command("kenv | grep smbios.system.product | "
        "sed 's/\"//g' | sed 's/smbios.system.product=//'");
  const char *maker = run_host_command("kenv | grep smbios.system.maker | "
        "sed 's/\"//g' | sed 's/smbios.system.maker=//'");
  printf("%s %s %s", maker, family, product);
#elif defined(__NetBSD__)
  printf("%s", run_host_command("sysctl -n machdep.dmi.system-vendor && "
              "echo \" \" && sysctl -n machdep.dmi.system-version && "
              "echo \" \" && sysctl -n machdep.dmi.system-product"));
#elif defined(__sun)
  printf("%s", run_host_command("prtconf -b | awk -F':' '/banner-name/ {printf $2}'"));
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
    printf("%s", run_host_command(cmd1));
  }

  if (cmd2) {
    const char *model = run_host_command(cmd2);
    if (!skip) printf(" %s", model);
  }
#elif defined(__APPLE__)
  printf("%s", run_host_command("sysctl -n hw.model"));

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
