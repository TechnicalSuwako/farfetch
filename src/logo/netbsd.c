#if defined(__NetBSD__)
#include "netbsd.h"
#include "../config.h"
#include "../resolution.h"
#include "../wm.h"

#include <string.h>
#include <stdlib.h>

char *LOGO[23];
char *LOGO_SMALL[23];
const char *color;
const char *titlecolor;
size_t logosize = 18;
int minsize = MIN_SIZE;

void getOS() {
  if (!customcolor) color = MAGENTA;
  else color = customcolor;
  if (!customtitlecolor) titlecolor = MAGENTA;
  else titlecolor = customtitlecolor;
  const char *res = display_resolution();
  if (!res) minsize--;
  else free((void *)res);
  const char *wm = display_wm();
  if (!wm) minsize--;
  else free((void *)wm);

  if (!isbiglogo) {
    LOGO[0]  = MAGENTA "                     `-/oshdmNMNdhyo+:-`   " RESET;
    LOGO[1]  = WHITE   "y" MAGENTA "/s+:-``    `.-:+oydNMMMMNhs/-``           " RESET;
    LOGO[2]  = WHITE   "-m+" MAGENTA "NMMMMMMMMMMMMMMMMMMMNdhmNMMMmdhs+/-`    " RESET;
    LOGO[3]  = WHITE   " -m+" MAGENTA "NMMMMMMMMMMMMMMMMMMMMmy+:`             " RESET;
    LOGO[4]  = WHITE   "  -N/" MAGENTA "dMMMMMMMMMMMMMMMds:`                  " RESET;
    LOGO[5]  = WHITE   "   -N/" MAGENTA "hMMMMMMMMMmho:`                      " RESET;
    LOGO[6]  = WHITE   "    -N/" MAGENTA "-:/++/:.`                           " RESET;
    LOGO[7]  = WHITE   "     :M+                                   " RESET;
    LOGO[8]  = WHITE   "      :Mo                                  " RESET;
    LOGO[9]  = WHITE   "       :Ms                                 " RESET;
    LOGO[10] = WHITE   "        :Ms                                " RESET;
    LOGO[11] = WHITE   "         :Ms                               " RESET;
    LOGO[12] = WHITE   "          :Ms                              " RESET;
    LOGO[13] = WHITE   "           :Ms                             " RESET;
    LOGO[14] = WHITE   "            :Ms                            " RESET;
    LOGO[15] = WHITE   "             :Ms                           " RESET;
    LOGO[16] = WHITE   "              :Ms                          " RESET;
    LOGO[17] = WHITE   "                                           " RESET;
  } else {
    logosize = biglogoi;
    if (biglogoi < (size_t)minsize) {
      for (size_t i = biglogoi; i < (size_t)minsize; i++) {
        LOGO[i] = WHITE "                                           " RESET;
      }
    }
  }

  if (!issmalllogo) {
    LOGO_SMALL[0] = "\\\\" MAGENTA "\\`-______,----__    " RESET;
    LOGO_SMALL[1] = " \\\\        " MAGENTA "__,---\\`_  " RESET;
    LOGO_SMALL[2] = "  \\\\       " MAGENTA "\\`.____    " RESET;
    LOGO_SMALL[3] = "   \\\\" MAGENTA "-______,----\\`-  " RESET;
    LOGO_SMALL[4] = "    \\\\                " RESET;
    LOGO_SMALL[5] = "     \\\\               " RESET;
    LOGO_SMALL[6] = "      \\\\              " RESET;
    for (int i = 7; i < minsize; i++) {
      LOGO_SMALL[i]  = MAGENTA "                      " RESET;
    }
  } else {
    if (smalllogoi < (size_t)minsize) {
      for (size_t i = smalllogoi; i < (size_t)minsize; i++) {
        LOGO_SMALL[i] = WHITE "                      " RESET;
      }
    }
  }
}
#endif
