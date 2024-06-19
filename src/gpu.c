#include "gpu.h"
#include "common.h"

#if !defined(__OpenBSD__) && !defined(__NetBSD__) && !defined(__FreeBSD__) &&\
    !defined(__linux__) && !defined(__DragonFly__)
#include <unistd.h>
#endif

const char *display_gpu() {
#if defined(__OpenBSD__)
  return run_command_s("dmesg | grep -i graphics | sed 's/^.* \"//' | "
                         "sed 's/\".*$//'");
#elif defined(__NetBSD__)
  return run_command_s("dmesg | grep -i graphics | sed 's/^.*: //' | "
                         "sed 's/ (.*$//'");
#elif defined(__FreeBSD__) || defined(__DragonFly__)
  return run_command_s("pciconf -lv | grep -B 4 -F \"VGA\" | "
                         "grep -F \"device\" | sed 's/^.* device//' | "
                         "sed \"s/^.* '//\" | sed \"s/'//\" | tail -1 | "
                         "sed 's/ Core Processor Integrated Graphics Controller//'");
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
