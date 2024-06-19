#if defined(__FreeBSD__)
#include "freebsd.h"

#include <string.h>

char *LOGO[23];
char *LOGO_SMALL[23];
const char *color;
const char *titlecolor;

void getOS() {
  color = RED;
  titlecolor = RED;

  LOGO[0]  = WHITE "```                        " RED "`       " RESET;
  LOGO[1]  = WHITE "  ` `.....---..." RED "....--.```   -/    " RESET;
  LOGO[2]  = WHITE "  +o   .--`         " RED "/y:`      +.   " RESET;
  LOGO[3]  = WHITE "   yo`:.            " RED ":o      `+-    " RESET;
  LOGO[4]  = WHITE "    y/               " RED "-/`   -o/     " RESET;
  LOGO[5]  = WHITE "   .-                  " RED "::/sy+:.    " RESET;
  LOGO[6]  = WHITE "   /                     " RED "`--  /    " RESET;
  LOGO[7]  = WHITE "  `:                          " RED ":`   " RESET;
  LOGO[8] = WHITE "  `:                          " RED ":`   " RESET;
  LOGO[9] = WHITE "   /                          " RED "/    " RESET;
  LOGO[10] = WHITE "   .-                        " RED "-.    " RESET;
  LOGO[11] = WHITE "    --                      " RED "-.     " RESET;
  LOGO[12] = WHITE "     `:`                  " RED "`:`      " RESET;
  LOGO[13] = RED   "       .--             `--.        " RESET;
  LOGO[14] = RED   "          .---.....----.           " RESET;
  LOGO[15] = RED   "                                   " RESET;

  LOGO_SMALL[0] = RED "/\\,-'''''-,/\\  " RESET;
  LOGO_SMALL[1] = RED "\\_)       (_/  " RESET;
  LOGO_SMALL[2] = RED "|           |  " RESET;
  LOGO_SMALL[3] = RED "|           |  " RESET;
  LOGO_SMALL[4] = RED " ;         ;   " RESET;
  LOGO_SMALL[5] = RED "  '-_____-'    " RESET;
  for (int i = 6; i < MIN_SIZE; i++) {
    LOGO_SMALL[i]  = RED "               " RESET;
  }
}
#endif
