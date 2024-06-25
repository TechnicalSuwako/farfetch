#include "storage.h"
#include "common.h"

#include <string.h>
#include <stdlib.h>

const char *display_storage() {
  const char *excode = run_command_s("zpool list 2>/dev/null || echo $?");
  if ( excode != NULL && (strncmp(excode, "127", strlen("127")) == 0)) {
    free((void *)excode);
    return run_command_s("df -h | "
        "awk '/^\\/dev\\// {printf \"%s: %s / %s, \", $1, $3, $2}' | "
        "awk '{sub(/, $/, \"\"); print}'");
  } 

  free((void *)excode);
  return run_command_s("zpool list | "
      "awk 'NR>1 {printf \"%s: %s / %s, \", $1, $3, $2}' | "
      "awk '{sub(/, $/, \"\"); print}'");
}
