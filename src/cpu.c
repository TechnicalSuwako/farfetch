#include "cpu.h"
#include "common.h"
#include <stdio.h>
#include <stdlib.h>

const char *display_cpu() {
#if !defined(__HAIKU__)
  const char *out = from_cache("/tmp/farfetch/cpu");
  if (out) return out;
#else
  const char *out = NULL;
#endif
  char *cmd = NULL;

#if defined(__NetBSD__)
  cmd = malloc(256);
  if (!cmd) return NULL;
  snprintf(cmd, 256, "sysctl -n machdep.cpu_brand | sed 's/(R)//' | "
        "sed 's/(TM)//' | sed 's/CPU //' | sed 's/Processor//' && "
        "echo \" (\" && sysctl -n hw.ncpu && echo \" core)\"");
#elif defined(__FreeBSD__) || defined(__OpenBSD__)
  cmd = malloc(1024);
  if (!cmd) return NULL;
  snprintf(cmd, 1024, "sysctl -n hw.model | sed 's/(R)//' | "
        "sed 's/(TM)//' | sed 's/CPU //' | sed 's/ Processor//' && "
        "echo \" (\" && sysctl -n hw.ncpu && echo \" core)\"");
#elif defined(__sun)
  cmd = malloc(1024);
  if (!cmd) return NULL;
  snprintf(cmd, 1024, "psrinfo -pv | tail -1 | "
        "sed 's/(r)//g; s/ CPU//; s/^ *//; s/ $//' | awk '{$1=$1};1' && "
        "echo \" (\" && psrinfo -p && echo \" core)\"");
#elif defined(__linux__)
  cmd =  "cat /proc/cpuinfo | awk -F '\\\\s*: | @' "
        "'/model name|Hardware|Processor|^cpu model|chip type|^cpu type/ { "
        "cpu=$2; if ($1 == \"Hardware\") exit } END { print cpu }' | "
        "sed 's/(R)//' | sed 's/(TM)//' | sed 's/CPU //' | sed 's/ Processor//' | "
        "sed 's/ [0-9]-Core//' && echo \" @ \" && "
        "cat /proc/cpuinfo | grep \"cpu MHz\" | sort -nr | head -1 | "
        "sed 's/^.*: //' | awk '{printf \"%.2f\", $1/1000}' && "
        "echo \"GHz (\" && nproc && echo \" core)\"";
#elif defined(__HAIKU__)
  const char *cpuname = run_command_s("sysinfo | grep \"CPU #0:\" | "
      "sed 's/CPU #0: \"'// | sed 's/\"//' | sed 's/(R)//' | sed 's/(TM)//' | "
      "sed 's/^.* Gen //' | sed 's/CPU //' | sed 's/ Processor//'");
  const char *freq = run_command_s("sysinfo | grep -A1 \"CPU #0\" | tail -1 | "
      "sed 's/^.*: //' | awk '{ printf \"%.2f\", $1 / 1000 }'");
  long long int proc = run_command_lld("nproc");

  cmd = (char *)malloc(128 * sizeof(char));
  if (!cmd) return NULL;

  snprintf(cmd, 128, "%s @ %sGHz (%lld core)", cpuname, freq, proc);

  free((void *)cpuname);
  free((void *)freq);
#elif defined(__APPLE__)
  cmd = malloc(1024);
  if (!cmd) return NULL;
  snprintf(cmd, 1024, "sysctl -n machdep.cpu.brand_string | sed 's/(R)//' | "
        "sed 's/(TM)//' | sed 's/CPU //' | sed 's/ Processor//' && "
        "echo \" (\" && sysctl -n hw.logicalcpu_max && echo \" core)\"");
#else
  return NULL;
#endif

  if (!cmd) return NULL;
  out = run_command_s(cmd);
#if !defined(__linux__)
  free(cmd);
#endif
#if !defined(__HAIKU__)
  to_cache("/tmp/farfetch/cpu", out);
#endif

  return out;
}
