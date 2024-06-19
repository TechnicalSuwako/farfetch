#include "user.h"
#include "common.h"

const char *display_user_name() {
  return run_command_s("whoami");
}

const char *display_user_host() {
#if defined(__OpenBSD__)
  return run_command_s("cat /etc/myname");
#elif defined(__NetBSD__)
  return run_command_s("hostname");
#elif defined(__FreeBSD__)
  return run_command_s("sysctl -n kern.hostname");
#else
  return run_command_s("cat /etc/hostname");
#endif
}
