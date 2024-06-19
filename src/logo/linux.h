#if defined(__linux__)
#ifndef LOGO_LINUX_H
#define LOGO_LINUX_H

#include "../distro.h"
#include "colors.h"

extern char *LOGO[23];
extern char *LOGO_SMALL[23];
extern const char *color;
extern const char *titlecolor;
extern size_t logosize;

void getDistro(const char *distroname);

#endif
#endif
