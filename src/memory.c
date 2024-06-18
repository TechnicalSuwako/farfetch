#include "memory.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

long long int run_mem_command(const char *command) {
  char buf[128];
  long long int res = 0;

  FILE *p = popen(command, "r");
  if (!p) {
    fprintf(stderr, "ホストコマンドを実効に失敗: %s", command);
    return 0;
  }

  while (fgets(buf, sizeof(buf), p) != NULL) {
    buf[strcspn(buf, "\n")] = '\0';
  }

  res = atoll(buf);
  pclose(p);

  return res;
}

void display_memory() {
  long long int memused = 0;
  long long int memtotal = 0;
#if defined(__OpenBSD__)
  memused = run_mem_command("vmstat | awk 'END {printf $3}' | sed 's/M//'");
  memtotal = run_mem_command("sysctl -n hw.physmem") / 1024LL / 1024LL;
#elif defined(__FreeBSD__) || defined(__DragonFly__)
  // 13M Active, 200M Inact, 184M Laundry,
  long long int used1 = run_mem_command("top | grep \"Mem:\" | awk '{print $2}' | "
      "sed 's/M//'");
  long long int used2 = run_mem_command("top | grep \"Mem:\" | awk '{print $4}' | "
      "sed 's/M//'");
  long long int used3 = run_mem_command("top | grep \"Mem:\" | awk '{print $6}' | "
      "sed 's/M//'");
  long long int used4 = run_mem_command("top | grep \"ARC:\" | awk '{print $6}' | "
      "sed 's/M//'");
  memused = used1 + used2 + used3 + used4;
  memtotal = run_mem_command("sysctl -n hw.physmem") / 1024LL / 1024LL;
#elif defined(__NetBSD__)
  memused = run_mem_command("top | grep \"Memory:\" | awk '{print $2}' | "
      "sed 's/M//'");
  memtotal = run_mem_command("sysctl -n hw.physmem64") / 1024LL / 1024LL;
#elif defined(__minix)
  memtotal = run_mem_command("sysctl -n hw.physmem") / 1024LL / 1024LL;
#elif defined(__linux__)
  long long int memaval = run_mem_command("cat /proc/meminfo | grep MemAvailable | "
                                          "awk '{print $2}'") / 1024LL;
  memtotal = run_mem_command("cat /proc/meminfo | grep MemTotal | "
      "awk '{print $2}'") / 1024LL;
  memused = memtotal - memaval;
  /* memused = run_mem_command("cat /proc/meminfo | grep MemFree | "
      "awk '{print $2}'") / 1024LL; */
#endif

  printf("%lld MiB / %lld MiB", memused, memtotal);
}
