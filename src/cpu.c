#include "cpu.h"
#include "common.h"

#include <stdio.h>
#if defined(__linux__)
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
      "if [ \"$(LC_ALL=C cat /sys/devices/system/cpu/cpu0/cpufreq/bios_limit 2>&1)\""
      " != \"cat: /sys/devices/system/cpu/cpu0/cpufreq/bios_limit: "
      "No such file or directory\" ]; then "
        "cat /sys/devices/system/cpu/cpu0/cpufreq/bios_limit | "
        "awk '{printf \"%.2f\", $1/1000000}'; else "
        "cat /sys/devices/system/cpu/cpu0/cpufreq/cpuinfo_max_freq | "
        "awk '{printf \"%.2f\", $1/1000000}'; fi && "
      "echo \"GHz (\" && nproc && echo \" core)\"");
#elif defined(__APPLE__)
  return run_command_s("sysctl -n machdep.cpu.brand_string | sed 's/(R)//' | "
                  "sed 's/(TM)//' | sed 's/CPU //' | sed 's/ Processor//' && "
                  "echo \" (\" && sysctl -n hw.logicalcpu_max && echo \" core)\"");
#endif
  return NULL;
}
