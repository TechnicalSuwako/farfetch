#if defined(__HAIKU__)
#include "haiku.h"
#include "../config.h"
#include "../resolution.h"

#include <string.h>
#include <stdlib.h>

char *LOGO[23];
char *LOGO_SMALL[23];
const char *color;
const char *titlecolor;
size_t logosize = 20;
int minsize = MIN_SIZE;

void getOS() {
  if (!customcolor) color = GREEN;
  else color = customcolor;
  if (!customtitlecolor) titlecolor = RED;
  else titlecolor = customtitlecolor;
  const char *res = display_resolution();
  if (!res) minsize--;
  else free((void *)res);

  if (!isbiglogo && !issmalllogo) {
    for (int i = 0; i < LOGO_SIZE; i++) {
      LOGO[i] = NULL;
      LOGO_SMALL[i] = NULL;
    }
  }

  if (!isbiglogo) {
    LOGO[0]   = YELLOW "     /      " RESET;
    LOGO[1]   = YELLOW "    //      " RESET;
    LOGO[2]   = YELLOW "   / \\      " RESET;
    LOGO[3]   = YELLOW "  /  -      " RESET;
    LOGO[4]   = YELLOW " /   \\      " RESET;
    LOGO[5]   = YELLOW " \\    \\     " RESET;
    LOGO[6]   = YELLOW " -    /     " RESET;
    LOGO[7]   = YELLOW "/    /      " RESET;
    LOGO[8]   = YELLOW "|    \\      " RESET;
    LOGO[9]   = YELLOW "|     \\     " RESET;
    LOGO[10]  = YELLOW "\\      \\    " RESET;
    LOGO[11]  = YELLOW "-      -    " RESET;
    LOGO[12]  = YELLOW "\\      \\    " RESET;
    LOGO[13]  = YELLOW " \\      \\   " RESET;
    LOGO[14]  = YELLOW "  \\     /   " RESET;
    LOGO[15]  = YELLOW "   \\   /    " RESET;
    LOGO[16]  = YELLOW "    \\ /     " RESET;
    LOGO[17]  = YELLOW "    | |     " RESET;
    LOGO[18]  = YELLOW "    | |     " RESET;
    LOGO[19]  = YELLOW "    |_|     " RESET;
  } else {
    logosize = biglogoi;
    if (biglogoi < (size_t)minsize) {
      for (size_t i = biglogoi; i < (size_t)minsize; i++) {
        LOGO[i] = WHITE "            " RESET;
      }
    }
  }

  if (!issmalllogo) {
    LOGO_SMALL[0] = YELLOW "  /    " RESET;
    LOGO_SMALL[1] = YELLOW " / \\   " RESET;
    LOGO_SMALL[2] = YELLOW "/  |   " RESET;
    LOGO_SMALL[3] = YELLOW "|  |   " RESET;
    LOGO_SMALL[4] = YELLOW "\\  /   " RESET;
    LOGO_SMALL[5] = YELLOW " ||    " RESET;
    LOGO_SMALL[6] = YELLOW " ||    " RESET;
    for (int i = 7; i < minsize; i++) {
      LOGO_SMALL[i] = YELLOW "       " RESET;
    }
  } else {
    if (smalllogoi < (size_t)minsize) {
      for (size_t i = smalllogoi; i < (size_t)minsize; i++) {
        LOGO_SMALL[i] = WHITE "       " RESET;
      }
    }
  }
}
#endif
