#if defined(__sun)
#ifndef LOGO_SUNOS_H
#define LOGO_SUNOS_H

#include <stdio.h>
#include "../distro.h"
#include "colors.h"

extern char *LOGO[23];
extern char *LOGO_SMALL[23];
extern const char *color;
extern const char *titlecolor;
extern const char *logoname;
extern size_t logosize;

void getDistro(const char *distroname);

#endif
#endif
