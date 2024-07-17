#include "user.h"
#include "common.h"

const char *display_user_name() {
  return run_command_s("whoami");
}

const char *display_user_host() {
  return run_command_s("command -v hostname >/dev/null 2>&1 && hostname || "
                       "cat /etc/hostname");
}
