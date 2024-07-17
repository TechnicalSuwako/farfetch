#include "cpu.h"
#include "common.h"

#include <stdio.h>
#if defined(__linux__) || defined(__HAIKU__)
#include <stdlib.h>
#endif

const char *display_cpu() {
#if defined(__NetBSD__)
  return run_command_s("sysctl -n machdep.cpu_brand | sed 's/(R)//' | "
                  "sed 's/(TM)//' | sed 's/CPU //' | sed 's/Processor//' && "
                  "echo \" (\" && sysctl -n hw.ncpu && echo \" core)\"");
#elif defined(__FreeBSD__) || defined(__OpenBSD__)
  return run_command_s("sysctl -n hw.model | sed 's/(R)//' | "
                  "sed 's/(TM)//' | sed 's/CPU //' | sed 's/ Processor//' && "
                  "echo \" (\" && sysctl -n hw.ncpu && echo \" core)\"");
#elif defined(__sun)
  return run_command_s("psrinfo -pv | tail -1 | "
      "sed 's/(r)//g; s/ CPU//; s/^ *//; s/ $//' | awk '{$1=$1};1' && "
      "echo \" (\" && psrinfo -p && echo \" core)\"");
#elif defined(__linux__)
  return run_command_s("cat /proc/cpuinfo | awk -F '\\\\s*: | @' "
      "'/model name|Hardware|Processor|^cpu model|chip type|^cpu type/ { "
      "cpu=$2; if ($1 == \"Hardware\") exit } END { print cpu }' | "
      "sed 's/(R)//' | sed 's/(TM)//' | sed 's/CPU //' | sed 's/ Processor//' | "
      "sed 's/ [0-9]-Core//' && echo \" @ \" && "
      "cat /proc/cpuinfo | grep \"cpu MHz\" | sort -nr | head -1 | sed 's/^.*: //' | "
      "awk '{printf \"%.2f\", $1/1000}' && "
      "echo \"GHz (\" && nproc && echo \" core)\"");
#elif defined(__HAIKU__)
  const char *cpuname = run_command_s("sysinfo | grep \"CPU #0:\" | "
      "sed 's/CPU #0: \"'// | sed 's/\"//' | sed 's/(R)//' | sed 's/(TM)//' | "
      "sed 's/^.* Gen //' | sed 's/CPU //' | sed 's/ Processor//'");
  const char *freq = run_command_s("sysinfo | grep -A1 \"CPU #0\" | tail -1 | "
      "sed 's/^.*: //' | awk '{ printf \"%.2f\", $1 / 1000 }'");
  long long int proc = run_command_lld("nproc");

  char *cmd = (char *)malloc(128 * sizeof(char));
  if (!cmd) {
    return NULL;
  }

  snprintf(cmd, 128, "%s @ %sGHz (%lld core)", cpuname, freq, proc);

  return cmd;
#elif defined(__APPLE__)
  return run_command_s("sysctl -n machdep.cpu.brand_string | sed 's/(R)//' | "
                  "sed 's/(TM)//' | sed 's/CPU //' | sed 's/ Processor//' && "
                  "echo \" (\" && sysctl -n hw.logicalcpu_max && echo \" core)\"");
#endif
  return NULL;
}
