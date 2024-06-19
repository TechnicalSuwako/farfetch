#if defined(__NetBSD__)
#include "netbsd.h"
#include "../resolution.h"

#include <string.h>

char *LOGO[23];
char *LOGO_SMALL[23];
const char *color;
const char *titlecolor;
size_t logosize = 18;
int minsize = MIN_SIZE;

void getOS() {
  color = MAGENTA;
  titlecolor = MAGENTA;
  if (!display_resolution()) minsize--;

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
}
#endif
