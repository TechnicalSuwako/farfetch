#include "storage.h"
#include "common.h"

#include <string.h>

const char *display_storage() {
    const char *excode = run_command_s("LC_ALL=C zpool list 2>/dev/null || echo $?");

    if (excode != NULL && strcmp(excode, "127") == 0) {
        return run_command_s("df -h | "
                             "awk '/^\\/dev\\// {printf \"%s: %s / %s, \", $1, $3, $2}' | "
                             "awk '{sub(/, $/, \"\"); print}'");
    } else {
        const char *iszfs = run_command_s("LC_ALL=C zpool list 2>&1");
        if (
            strncmp(iszfs, "sh: zpool: not found", strlen("sh: zpool: not found")) == 0 ||
            strncmp(iszfs, "sh: 1: zpool: not found", strlen("sh: 1: zpool: not found")) == 0
        ) {
            return run_command_s("df -h | "
                                 "awk '/^\\/dev\\// {printf \"%s: %s / %s, \", $1, $3, $2}' | "
                                 "awk '{sub(/, $/, \"\"); print}'");
        } else {
            return run_command_s("zpool list | "
                                 "awk 'NR>1 {printf \"%s: %s / %s, \", $1, $3, $2}' | "
                                 "awk '{sub(/, $/, \"\"); print}'");
        }
    }
}

