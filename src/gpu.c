#include "gpu.h"
#include "common.h"
#include <stdio.h>
#include <stdlib.h>

#if !defined(__OpenBSD__) && !defined(__NetBSD__) && !defined(__FreeBSD__) &&\
    !defined(__linux__) && !defined(__DragonFly__) && !defined(__APPLE__) &&\
    !defined(__HAIKU__)
#include <unistd.h>
#endif

#if defined(__FreeBSD__) || defined(__Dragonfly__) || defined(__HAIKU__)
#include <string.h>
#endif

const char *display_gpu() {
#if !defined(__HAIKU__)
  const char *out = from_cache("/tmp/farfetch/gpu");
  if (out) return out;
#else
  const char *out = NULL;
#endif
  char *cmd = NULL;

#if defined(__OpenBSD__) || defined(__NetBSD__)
  cmd = malloc(2048);
  if (!cmd) return NULL;
  snprintf(cmd, 2048, "dmesg | "
      "if [ \"$(dmesg | grep \"radeondrm.* at pci.*\")\" ]; "
        "then grep -i \"radeondrm.* at pci.*\"; "
      "elif [ \"$(dmesg | grep \"inteldrm.* at pci.*\")\" ]; "
        "then grep -i \"inteldrm.* at pci.*\"; "
      "elif [ \"$(dmesg | grep \"amdgpu.* at pci.*\")\" ]; "
        "then grep -i \"amdgpu.* at pci.*\"; "
      "elif [ \"$(dmesg | grep \"agp.* at intagp.*\")\" ]; "
        "then grep -i \"agp.* at intagp.*\"; "
      "elif [ \"$(dmesg | grep \"intagp.* at inteldrm.*\")\" ]; "
        "then grep -i \"intagp.* at inteldrm.*\"; "
      "elif [ \"$(dmesg | grep \"drm.* at inteldrm.*\")\" ]; "
        "then grep -i \"drm.* at inteldrm.*\"; "
      "elif [ \"$(dmesg | grep \"drm.* at radeondrm.*\")\" ]; "
        "then grep -i \"drm.* at radeondrm.*\"; "
      "elif [ \"$(dmesg | grep \"drm.* at amdgpu.*\")\" ]; "
        "then grep -i \"drm.* at amdgpu.*\"; "
      "elif [ \"$(dmesg | grep \"wsdisplay.* at amdgpu.*\")\" ]; "
        "then grep -i \"wsdisplay.* at amdgpu.*\"; "
      "elif [ \"$(dmesg | grep \"i915drmkms.* at pci.*\")\" ]; "
        "then grep -i \"i915drmkms.* at pci.*\"; "
      "elif [ \"$(dmesg | grep \"nouveau.* at pci.*\")\" ]; "
        "then grep -i \"nouveau.* at pci.*\"; "
      "elif [ \"$(dmesg | grep \"radeon.* at pci.*\")\" ]; "
        "then grep -i \"radeon.* at pci.*\"; "
      "elif [ \"$(dmesg | grep \"rkdrm.* at fdt.*\")\" ]; "
        "then grep -i \"rkdrm.* at fdt.*\"; "
      "elif [ \"$(dmesg | grep \"sunxidrm.* at fdt.*\")\" ]; "
        "then grep -i \"sunxidrm.* at fdt.*\"; "
      "elif [ \"$(dmesg | grep \"tegradrm.* at fdt.*\")\" ]; "
        "then grep -i \"tegradrm.* at fdt.*\"; "
      "elif [ \"$(dmesg | grep \"viadrmums.* at drm.*\")\" ]; "
        "then grep -i \"viadrmums.* at drm.*\"; "
      "else grep -i \"graphics\"; fi | "
      "sed 's/^.*: //' | "
      "sed 's/^.* \"//' | "
      "sed 's/\".*$//' | head -1");
#elif defined(__FreeBSD__) || defined(__DragonFly__)
  const char *test = run_command_s("pciconf -lv | grep -B 4 -F \"VGA\" | head -1");
  if (!strstr(test, "vgapci")) {
    free((void *)test);
    return NULL;
  }

  free((void *)test);

  cmd = malloc(256);
  if (!cmd) return NULL;
  snprintf(cmd, 256, "pciconf -lv | grep -B 4 -F \"VGA\" | "
                      "grep -F \"device\" | sed 's/^.* device//' | "
                      "sed \"s/^.* '//\" | sed \"s/'//\" | tail -1 | "
                      "sed 's/ Core Processor Integrated Graphics Controller//'");
#elif defined(__sun)
  cmd = malloc(512);
  if (!cmd) return NULL;
  snprintf(cmd, 512, "prtconf -v | grep -A 30 \"value='display'\" | "
      "grep -A 1 vendor-name | tail -1 | sed 's/^.*value=//' | sed \"s/'//g\" | "
      "sed 's/ Corporation//' && echo \" \" && prtconf -v | "
      "grep -A 30 \"value='display'\" | grep -A 1 device-name | tail -1 | "
      "sed 's/^.*value=//' | sed \"s/'//g\"");
#elif defined(__linux__)
  cmd = malloc(256);
  if (!cmd) return NULL;
  snprintf(cmd, 256, "lspci | grep VGA | sed 's/^.*: //' | "
                         "sed 's/Corporation //' | sed 's/ (.*$//' | "
                         "sed 's/Advanced Micro Devices//' | "
                         "sed 's/, Inc. //' | sed 's/Navi [0-9]* //' | "
                         "sed 's/\\[//g' | sed 's/\\]//g'");
#elif defined(__APPLE__)
  cmd = malloc(128);
  if (!cmd) return NULL;
  snprintf(cmd, 128, "system_profiler SPDisplaysDataType | "
      "awk -F': ' '/^ *Chipset Model:/ {printf $2 \", \"}'");
#elif defined(__HAIKU__)
  const char *vendor = run_command_s("listdev | grep -A1 \"device Display\" | "
        "tail -1 | sed 's/^.*: //' | sed 's/ Corporation//'");
  const char *device = run_command_s("listdev | grep -A2 \"device Display\" | "
        "tail -1 | sed 's/^.*: //'");

  char *cmd = (char *)malloc(128 * sizeof(char));
  if (!cmd) return NULL;

  if (strncmp(vendor, device, strlen(device)) == 0) {
    snprintf(cmd, 128, "%s", device);
    free((void *)device);
  } else {
    snprintf(cmd, 128, "%s %s", device, vendor);
    free((void *)device);
    free((void *)vendor);
  }
#else
  if (
      access("/bin/glxinfo", F_OK) == -1 &&
      access("/usr/bin/glxinfo", F_OK) == -1 &&
      access("/usr/local/bin/glxinfo", F_OK) == -1 &&
      access("/usr/X11R6/bin/glxinfo", F_OK) == -1 &&
      access("/usr/X11R7/bin/glxinfo", F_OK) == -1 &&
      access("/usr/pkg/bin/glxinfo", F_OK) == -1
  ) return NULL;

  cmd = malloc(256);
  if (!cmd) return NULL;
  snprintf(cmd, 256, "glxinfo -B | grep -F 'OpenGL renderer string' | "
                  "sed 's/OpenGL renderer string: //' | sed 's/Mesa //' | "
                  "sed 's/DRI //' | sed 's/(R)//' | sed 's/(.*$//'");
#endif

  if (!cmd) return NULL;
  out = run_command_s(cmd);
  free((void *)cmd);
#if !defined(__HAIKU__)
  if (out) to_cache("/tmp/farfetch/gpu", out);
#endif

  return out;
}
