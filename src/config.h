#ifndef CONFIG_H
#define CONFIG_H

#include <stdbool.h>
#include <unistd.h>

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
extern bool isbiglogo;
extern bool issmalllogo;
extern size_t biglogoi;
extern size_t smalllogoi;
extern const char *customcolor;
extern const char *customtitlecolor;
extern const char *customlogobig;
extern const char *customlogosmall;

void getconf();

#endif
