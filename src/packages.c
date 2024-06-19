#include "packages.h"
#include "common.h"

#if defined(__linux__)
#include <unistd.h>

#include "distro.h"
#endif

const char *display_packages() {
#if defined(__OpenBSD__) || defined(__NetBSD__)
  return run_command_s("pkg_info -a | wc -l | sed \"s/ //g\"");
#elif defined(__FreeBSD__) || defined(__DragonFly__)
  return run_command_s("pkg info -a | wc -l | sed \"s/ //g\"");
#elif defined(__linux__)
  if (access("/bin/xbps-query", F_OK) != -1) {
    return run_command_s("xbps-query -l | wc -l | sed \"s/ //g\"");
  } else if (access("/usr/bin/dpkg-query", F_OK) != -1) {
    return run_command_s("dpkg-query -f '.\n' -W | wc -l | sed \"s/ //g\"");
  }
#endif
}
