#ifndef CONFIG_H
#define CONFIG_H

#include <stdbool.h>

extern bool isos;
extern bool ishost;
#if defined(__linux__) || defined(__sunos)
extern bool isdistro;
#endif
extern bool isuptime;
#if defined(__OpenBSD__)
extern bool isrecording;
#endif
extern bool ispackages;
extern bool islibc;
extern bool isresolution;
extern bool iswm;
extern bool isshell;
extern bool iscpu;
extern bool isgpu;
extern bool ismemory;
extern bool isstorage;

void getconf();

#endif
