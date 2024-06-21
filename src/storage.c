#include "storage.h"
#include "common.h"

#include <string.h>

const char *display_storage() {
  const char *iszfs = run_command_s("LC_ALL=C zpool list 2>&1");
    if (
      strncmp(
        iszfs,
        "sh: command not found: zpool",
        strlen("sh: command not found: zpool")
      ) == 0 ||
      strncmp(
        iszfs,
        "internal error: failed to initialize ZFS library",
        strlen("internal error: failed to initialize ZFS library")
      ) == 0 ||
      strncmp(iszfs, "sh: zpool: not found", strlen("sh: zpool: not found")
    ) == 0) {
        return run_command_s("df -h | "
            "awk '/^\\/dev\\// {printf \"%s: %s / %s, \", $1, $3, $2}' | "
            "awk '{sub(/, $/, \"\"); print}'");
    }

    return run_command_s("zpool list | "
        "awk 'NR>1 {printf \"%s: %s / %s, \", $1, $3, $2}' | "
        "awk '{sub(/, $/, \"\"); print}'");
}
