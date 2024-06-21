#include "gpu.h"
#include "common.h"

#if !defined(__OpenBSD__) && !defined(__NetBSD__) && !defined(__FreeBSD__) &&\
    !defined(__linux__) && !defined(__DragonFly__)
#include <unistd.h>
#endif

const char *display_gpu() {
#if defined(__OpenBSD__) || defined(__NetBSD__)
  return run_command_s("dmesg | "
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
      "sed 's/^.* \"//' | "
      "sed 's/\".*$//' | head -1");
#elif defined(__FreeBSD__) || defined(__DragonFly__)
  return run_command_s("pciconf -lv | grep -B 4 -F \"VGA\" | "
                         "grep -F \"device\" | sed 's/^.* device//' | "
                         "sed \"s/^.* '//\" | sed \"s/'//\" | tail -1 | "
                         "sed 's/ Core Processor Integrated Graphics Controller//'");
#elif defined(__sun)
  return run_command_s("prtconf -v | grep -A 30 \"value='display'\" | "
      "grep -A 1 vendor-name | tail -1 | sed 's/^.*value=//' | sed \"s/'//g\" | "
      "sed 's/ Corporation//' && echo \" \" && prtconf -v | "
      "grep -A 30 \"value='display'\" | grep -A 1 device-name | tail -1 | "
      "sed 's/^.*value=//' | sed \"s/'//g\"");
#elif defined(__linux__)
  return run_command_s("lspci | grep VGA | sed 's/^.*: //' | "
                         "sed 's/Corporation //' | sed 's/ (.*$//' | "
                         "sed 's/Advanced Micro Devices//' | "
                         "sed 's/, Inc. //' | sed 's/Navi [0-9]* //' | "
                         "sed 's/\\[//g' | sed 's/\\]//g'");
#else
  if (
      access("/bin/glxinfo", F_OK) == -1 &&
      access("/usr/bin/glxinfo", F_OK) == -1 &&
      access("/usr/local/bin/glxinfo", F_OK) == -1 &&
      access("/usr/X11R6/bin/glxinfo", F_OK) == -1 &&
      access("/usr/X11R7/bin/glxinfo", F_OK) == -1 &&
      access("/usr/pkg/bin/glxinfo", F_OK) == -1
  ) return NULL;
  return run_command_s("glxinfo -B | grep -F 'OpenGL renderer string' | "
                  "sed 's/OpenGL renderer string: //' | sed 's/Mesa //' | "
                  "sed 's/DRI //' | sed 's/(R)//' | sed 's/(.*$//'");
#endif
}
