#include "memory.h"
#include "common.h"

#include <stdio.h>

void display_memory() {
  long long int memused = 0;
  long long int memtotal = 0;
#if defined(__OpenBSD__)
  memused = run_command_lld("vmstat | awk 'END {printf $3}' | sed 's/M//'");
  memtotal = run_command_lld("sysctl -n hw.physmem") / 1024LL / 1024LL;
#elif defined(__FreeBSD__) || defined(__DragonFly__)
  // 13M Active, 200M Inact, 184M Laundry,
  long long int used1 = run_command_lld("top | grep \"Mem:\" | awk '{print $2}' | "
      "sed 's/M//'");
  long long int used2 = run_command_lld("top | grep \"Mem:\" | awk '{print $4}' | "
      "sed 's/M//'");
  long long int used3 = run_command_lld("top | grep \"Mem:\" | awk '{print $6}' | "
      "sed 's/M//'");
  long long int used4 = run_command_lld("top | grep \"ARC:\" | awk '{print $6}' | "
      "sed 's/M//'");
  memused = used1 + used2 + used3 + used4;
  memtotal = run_command_lld("sysctl -n hw.physmem") / 1024LL / 1024LL;
#elif defined(__NetBSD__)
  memused = run_command_lld("top | grep \"Memory:\" | awk '{print $2}' | "
      "sed 's/M//'");
  memtotal = run_command_lld("sysctl -n hw.physmem64") / 1024LL / 1024LL;
#elif defined(__sun)
  // Memory: 3993M phys mem, 504M free mem,
  memused = run_command_lld("top | grep \"Memory:\" | awk '{print $5}' | "
      "sed 's/M//'");
  memtotal = run_command_lld("top | grep \"Memory:\" | awk '{print $2}' | "
      "sed 's/M//'");
  /* memtotal = run_command_lld("sysctl -n hw.physmem64") / 1024LL / 1024LL; */
#elif defined(__minix)
  memtotal = run_command_lld("sysctl -n hw.physmem") / 1024LL / 1024LL;
#elif defined(__linux__)
  long long int memaval = run_command_lld("cat /proc/meminfo | grep MemAvailable | "
                                          "awk '{print $2}'") / 1024LL;
  memtotal = run_command_lld("cat /proc/meminfo | grep MemTotal | "
      "awk '{print $2}'") / 1024LL;
  memused = memtotal - memaval;
  /* memused = run_command_lld("cat /proc/meminfo | grep MemFree | "
      "awk '{print $2}'") / 1024LL; */
#elif defined(__APPLE__)
  memtotal = run_command_lld("sysctl -n hw.memsize") / 1024LL / 1024LL;
  long long int memwired = run_command_lld("vm_stat | awk '/ wired/ { print $4 }'");
  long long int memactive = run_command_lld("vm_stat | awk '/ active/ { printf $3 }'");
  long long int memcompressed = run_command_lld("vm_stat | "
                                                "awk '/ occupied/ { printf $5 }'");
  memused = (memwired + memactive + memcompressed) * 4LL / 1024LL;
#elif defined(__HAIKU__)
  memtotal = run_command_lld("vmstat | awk '/max memory:/ {max=$3} END {print max/1024/1024}'");
  long long int memfree = run_command_lld("vmstat | awk '/free memory:/ {free=$3} END {print free/1024/1024}'");
  memused = memtotal - memfree;
#endif

  printf("%lld MiB / %lld MiB", memused, memtotal);
}
