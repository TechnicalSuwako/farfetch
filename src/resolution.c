#include "resolution.h"
#include "common.h"

const char *display_resolution() {
  return run_command_s("xrandr --nograb --current | "
                       "awk -F 'connected |\\\\+|\\\\(' '/ "
                       "connected.*[0-9]+x[0-9]+\\+/ && $2 {printf $2 "
                       "\", \"}' | sed 's/primary //' | "
                       "sed 's/,\\([^,]*\\)$/\\1/'");
}
