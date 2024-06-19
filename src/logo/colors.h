#ifndef LOGO_COLORS_H
#define LOGO_COLORS_H

#if defined(__OpenBSD__) || defined(__linux__)
#define MIN_SIZE 11
#else
#define MIN_SIZE 10
#endif

#define LOGO_SIZE 24

#define GREY    "\e[1;30m"
#define RED     "\e[1;31m"
#define GREEN   "\e[1;32m"
#define YELLOW  "\e[1;33m"
#define BLUE    "\e[1;34m"
#define MAGENTA "\e[1;35m"
#define CYAN    "\e[1;36m"
#define WHITE   "\e[1;37m"
#define RESET   "\e[0m"

#endif
