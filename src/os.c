#include "os.h"
#include "common.h"

const char *display_os() {
  return run_command_s("uname -s && echo \" \" && uname -r && "
                       "echo \" \" && uname -m");
}
