#include "storage.h"
#include "common.h"

#include <string.h>

const char *display_storage() {
  const char *iszfs = run_command_s("LC_ALL=C zpool list 2>&1");
  if (strstr(iszfs, "command not found: zpool")) {
    return run_command_s("zpool list | awk 'NR>1 {print $1 \": \" $3 \" / \" $2}' | "
        "sed ':a;N;$!ba;s//, /g'");
  }

  return run_command_s("df -h | awk 'NR>1 {print $1 \": \" $3 \" / \" $2}' | "
      "sed ':a;N;$!ba;s/\\n/, /g'");
}
