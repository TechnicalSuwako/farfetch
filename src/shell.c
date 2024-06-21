#include "shell.h"
#include "common.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

const char *display_shell() {
  char *shell = (char *)malloc(64 * sizeof(char));
  if (shell == NULL) {
    return NULL;
  }

  const char *ver;
  const char *name = run_command_s("echo ${SHELL##*/}");

  if (strncmp(name, "bash", strlen("bash")) == 0) {
    ver = run_command_s("echo $BASH_VERSION");
  } else if (strncmp(name, "ksh", strlen("ksh")) == 0) {
    ver = run_command_s("echo $KSH_VERSION | sed 's/^.*v//' | sed 's/ .*$//'");
  } else if (strncmp(name, "zsh", strlen("zsh")) == 0) {
    ver = run_command_s("zsh --version | sed 's/ (.*$//' | sed 's/zsh //'");
  } else if (strncmp(name, "yash", strlen("yash")) == 0) {
    ver = run_command_s("LC_ALL=C yash --version | head -1 | "
        "sed 's/Yet another shell, version //'");
  } else if (strncmp(name, "tsch", strlen("tsch")) == 0) {
    ver = run_command_s("tcsh --version | sed 's/tcsh //' | sed 's/ .*$//'");
  } else {
    ver = NULL;
  }

  if (ver != NULL) {
    snprintf(shell, sizeof(shell), "%s %s", name, ver);
  } else {
    snprintf(shell, sizeof(shell), "%s", name);
  }

  free((void *)name);
  if (ver != NULL) free((void *)ver);

  return shell;
}
