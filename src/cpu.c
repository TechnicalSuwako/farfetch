#include "cpu.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void run_cpu_command(const char *command) {
  char buf[128];

  FILE *p = popen(command, "r");
  if (!p) {
    fprintf(stderr, "CPUコマンドを実効に失敗: %s", command);
    return;
  }

  while (fgets(buf, sizeof(buf), p) != NULL) {
    buf[strcspn(buf, "\n")] = '\0';
    printf("%s", buf);
  }

  pclose(p);
}

void display_cpu() {
#if defined(__NetBSD__)
  run_cpu_command("sysctl -n machdep.cpu_brand | sed 's/(R)//' | "
                  "sed 's/(TM)//' | sed 's/CPU //' | sed 's/Processor//'");
  run_cpu_command("echo \" (\" && sysctl -n hw.ncpu && echo \" core)\"");
#elif defined(__FreeBSD__) || defined(__OpenBSD__)
  run_cpu_command("sysctl -n hw.model | sed 's/(R)//' | "
                  "sed 's/(TM)//' | sed 's/CPU //' | sed 's/Processor//'");
  run_cpu_command("echo \" (\" && sysctl -n hw.ncpu && echo \" core)\"");
#elif defined(__linux__)
  run_cpu_command("cat /proc/cpuinfo | awk -F '\\\\s*: | @' "
      "'/model name|Hardware|Processor|^cpu model|chip type|^cpu type/ { "
      "cpu=$2; if ($1 == \"Hardware\") exit } END { print cpu }' | "
      "sed 's/(R)//' | sed 's/(TM)//' | sed 's/CPU //' | sed 's/ Processor//' | "
      "sed 's/ [0-9]-Core//'");
  printf(" @ ");

  char buf[20];
  long int val;
  double fmt;
  FILE *fp = fopen("/sys/devices/system/cpu/cpu0/cpufreq/bios_limit", "r");
  if (fp == NULL) {
    perror("Error opening file");
    return;
  }

  if (fgets(buf, sizeof(buf), fp) != NULL) {
    val = strtol(buf, NULL, 10);
    fmt = val / 1000000.0;
    printf("%.2f", fmt);
  } else {
    perror("失敗");
    fclose(fp);
    return;
  }

  fclose(fp);
  run_cpu_command("echo \"GHz (\" && nproc && echo \" core)\"");
#endif
}
