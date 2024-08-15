#include "host.h"
#include "common.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if defined(__linux__)
#include <unistd.h>
#endif

const char *display_host() {
#if !defined(__HAIKU__)
  char *out = (char *)from_cache("/tmp/farfetch/host");
  if (out) return out;
#else
  char *out = NULL;
#endif
  const char *cmd = NULL;

#if defined(__OpenBSD__)
  cmd = "sysctl -n hw.vendor && echo \" \" && "
        "if [ \"$(sysctl -n hw.version 2>&1)\" != "
        "\"sysctl: hw.version: value is not available\" ]; then "
        "sysctl -n hw.version && echo \" \"; fi && "
        "sysctl -n hw.product";
#elif defined(__FreeBSD__)
  cmd = "kenv | grep smbios.system.family | sed 's/\"//g' | "
          "sed 's/smbios.system.family=//' && "
        "kenv | grep smbios.system.version | sed 's/\"//g' | "
          "sed 's/smbios.system.version=//' && "
        "kenv | grep smbios.system.product | sed 's/\"//g' | "
          "sed 's/smbios.system.product=//' && "
        "kenv | grep smbios.system.maker | sed 's/\"//g' | "
        "sed 's/smbios.system.maker=//'";
#elif defined(__NetBSD__)
  cmd = "sysctl -n machdep.dmi.system-vendor && "
        "echo \" \" && sysctl -n machdep.dmi.system-version && "
        "echo \" \" && sysctl -n machdep.dmi.system-product";
#elif defined(__sun)
  cmd = "smbios | grep \"Product\" | "
        "sed 's/ Product: //' | awk '{$1=$1};1' | head -1";
#elif defined(__linux__)
  const char *pre_cmd = NULL;

  if (access("/system/app/", F_OK) != -1) {
    pre_cmd = "getprop ro.product.brand && echo \" \" && getprop ro.product.model";
  } else if (
      access("/sys/devices/virtual/dmi/id/product_name", F_OK) != -1 &&
      access("/sys/devices/virtual/dmi/id/product_version", F_OK) != 1
  ) {
    pre_cmd = "cat /sys/devices/virtual/dmi/id/product_name && echo \" \" && "
          "cat /sys/devices/virtual/dmi/id/product_version";
  } else if (access("/sys/firmware/devicetree/base/model", F_OK) != -1) {
    pre_cmd = "cat /sys/firmware/devicetree/base/model";
  } else if (access("/tmp/sysinfo/model", F_OK) != 1) {
    pre_cmd = "cat /tmp/sysinfo/model";
  } else {
    return "Unknown";
  }

  size_t cmdlen = 1024;
  cmd = malloc(cmdlen);
  if (!cmd) return "Unknown";

  snprintf((char *)cmd, cmdlen, "%s | sed '/To be filled by O.E.M./d; "
      "/To Be Filled By O.E.M./d; /OEM/d; /Not Applicable/d; "
      "/System Product Name/d; /System Version/d; /Undefined/d; /Default string/d; "
      "/Not Specified/d; /Type1ProductConfigId/d; /INVALID/d; "
      "/All Series/d' ", pre_cmd);
#elif defined(__APPLE__)
  cmd = "sysctl -n hw.model";
#endif

  if (!cmd) return "Unknown";

  out = (char *)run_command_s(cmd);
#if defined(__linux__)
  free((void *)cmd);
#endif
#if !defined(__HAIKU__)
  to_cache("/tmp/farfetch/host", out);
#endif

  return out;
}
