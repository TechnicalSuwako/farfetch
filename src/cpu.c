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
                  "sed 's/(TM)//' | sed 's/CPU //' | sed 's/Processor//' && "
                  "echo \" (\" && sysctl -n hw.ncpu && echo \" core)\"");
#elif defined(__sun)
  return run_command_s("psrinfo -pv | tail -1 | sed 's/(r)//g' | "
                       "sed 's/ CPU//' | sed 's/^ *//' && "
                       "echo \" (\" && psrinfo -p && echo \" core)\"");
#elif defined(__linux__)
  char buf[20];
  long int val;
  double fmt;
  FILE *fp = fopen("/sys/devices/system/cpu/cpu0/cpufreq/bios_limit", "r");
  if (fp == NULL) {
    fp = fopen("/sys/devices/system/cpu/cpu0/cpufreq/cpuinfo_max_freq", "r");
  }

  if (fp == NULL) {
    perror("失敗");
    return NULL;
  }

  if (fgets(buf, sizeof(buf), fp) != NULL) {
    val = strtol(buf, NULL, 10);
    fmt = val / 1000000.0;
    printf("%.2f", fmt);
  } else {
    perror("失敗");
    fclose(fp);
    return NULL;
  }

  fclose(fp);
  
  return run_command_s("cat /proc/cpuinfo | awk -F '\\\\s*: | @' "
      "'/model name|Hardware|Processor|^cpu model|chip type|^cpu type/ { "
      "cpu=$2; if ($1 == \"Hardware\") exit } END { print cpu }' | "
      "sed 's/(R)//' | sed 's/(TM)//' | sed 's/CPU //' | sed 's/ Processor//' | "
      "sed 's/ [0-9]-Core//' && echo \" @ \" && "
      "echo \"GHz (\" && nproc && echo \" core)\"");
#endif
  return NULL;
}
