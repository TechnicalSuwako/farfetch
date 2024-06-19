#if defined(__NetBSD__)
#ifndef LOGO_NETBSD_H
#define LOGO_NETBSD_H

#include <stdio.h>
#include "colors.h"

extern char *LOGO[23];
extern char *LOGO_SMALL[23];
extern const char *color;
extern const char *titlecolor;
extern size_t logosize;

void getOS();

#endif
#endif
