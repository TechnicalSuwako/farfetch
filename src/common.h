#ifndef COMMON_H
#define COMMON_H

long long int run_command_lld(const char *command);
const char *run_command_s(const char *command);
#if !defined(__HAIKU__)
const char *from_cache(const char *file);
int to_cache(const char *file, const char *res);
#endif

#endif
