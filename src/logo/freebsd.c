#if defined(__FreeBSD__)
#include "freebsd.h"
#include "../config.h"
#include "../resolution.h"
#include "../wm.h"

#include <string.h>
#include <stdlib.h>

char *LOGO[23];
char *LOGO_SMALL[23];
const char *color;
const char *titlecolor;
size_t logosize = 16;
int minsize = MIN_SIZE;

void getOS() {
  if (!customcolor) color = RED;
  else color = customcolor;
  if (!customtitlecolor) titlecolor = RED;
  else titlecolor = customtitlecolor;
  const char *res = display_resolution();
  if (!res) minsize--;
  else free((void *)res);
  const char *wm = display_wm();
  if (!wm) minsize--;
  else free((void *)wm);

  if (!isbiglogo && !issmalllogo) {
    for (int i = 0; i < LOGO_SIZE; i++) {
      LOGO[i] = NULL;
      LOGO_SMALL[i] = NULL;
    }
  }

  if (!isbiglogo) {
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
  } else {
    logosize = biglogoi;
    if (biglogoi < (size_t)minsize) {
      for (size_t i = biglogoi; i < (size_t)minsize; i++) {
        LOGO[i] = WHITE "                                   " RESET;
      }
    }
  }

  if (!issmalllogo) {
    LOGO_SMALL[0] = RED "/\\,-'''''-,/\\  " RESET;
    LOGO_SMALL[1] = RED "\\_)       (_/  " RESET;
    LOGO_SMALL[2] = RED "|           |  " RESET;
    LOGO_SMALL[3] = RED "|           |  " RESET;
    LOGO_SMALL[4] = RED " ;         ;   " RESET;
    LOGO_SMALL[5] = RED "  '-_____-'    " RESET;
    for (int i = 6; i < minsize; i++) {
      LOGO_SMALL[i]  = RED "               " RESET;
    }
  } else {
    if (smalllogoi < (size_t)minsize) {
      for (size_t i = smalllogoi; i < (size_t)minsize; i++) {
        LOGO_SMALL[i] = WHITE "               " RESET;
      }
    }
  }
}
#endif
