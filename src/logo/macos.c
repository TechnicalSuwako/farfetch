#if defined(__APPLE__)
#include "macos.h"
#include "../resolution.h"
#include "../packages.h"

#include <string.h>
#include <stdlib.h>

char *LOGO[23];
char *LOGO_SMALL[23];
const char *color;
const char *titlecolor;
size_t logosize = 17;
int minsize = MIN_SIZE;

void getOS() {
  color = YELLOW;
  titlecolor = GREEN;
  const char *res = display_resolution();
  if (!res) minsize--;
  else free((void *)res);
  const char *pac = display_packages();
  if (!pac) minsize--;
  else free((void *)pac);

  LOGO[0]  = GREEN   "                    'c.          " RESET;
  LOGO[1]  = GREEN   "                 ,xNMM.          " RESET;
  LOGO[2]  = GREEN   "               .OMMMMo           " RESET;
  LOGO[3]  = GREEN   "               OMMM0,            " RESET;
  LOGO[4]  = GREEN   "     .;loddo:' loolloddol;.      " RESET;
  LOGO[5]  = GREEN   "   cKMMMMMMMMMMNWMMMMMMMMMM0:    " RESET;
  LOGO[6]  = YELLOW  " .KMMMMMMMMMMMMMMMMMMMMMMMWd.    " RESET;
  LOGO[7]  = YELLOW  " XMMMMMMMMMMMMMMMMMMMMMMMX.      " RESET;
  LOGO[8]  = RED     ";MMMMMMMMMMMMMMMMMMMMMMMM:       " RESET;
  LOGO[9]  = RED     ":MMMMMMMMMMMMMMMMMMMMMMMM:       " RESET;
  LOGO[10] = RED     ".MMMMMMMMMMMMMMMMMMMMMMMMX.      " RESET;
  LOGO[11] = RED     " kMMMMMMMMMMMMMMMMMMMMMMMMWd.    " RESET;
  LOGO[12] = MAGENTA " .XMMMMMMMMMMMMMMMMMMMMMMMMMMk   " RESET;
  LOGO[13] = MAGENTA "  .XMMMMMMMMMMMMMMMMMMMMMMMMK.   " RESET;
  LOGO[14] = BLUE    "    kMMMMMMMMMMMMMMMMMMMMMMd     " RESET;
  LOGO[15] = BLUE    "     ;KMMMMMMMWXXWMMMMMMMk.      " RESET;
  LOGO[16] = BLUE    "       .cooc,.    .,coo:.        " RESET;

  LOGO_SMALL[0] = GREEN   "       .:'   " RESET;
  LOGO_SMALL[1] = GREEN   "    _ :'_    " RESET;
  LOGO_SMALL[2] = YELLOW  " .'`_`-'_``. " RESET;
  LOGO_SMALL[3] = YELLOW  ":________.-' " RESET;
  LOGO_SMALL[4] = RED     ":_______:    " RESET;
  LOGO_SMALL[5] = RED     ":_______:    " RESET;
  LOGO_SMALL[6] = MAGENTA " :_______`-; " RESET;
  LOGO_SMALL[7] = BLUE    "  `._.-._.'  " RESET;
  for (int i = 8; i < minsize; i++) {
    LOGO_SMALL[i]  = RED "             " RESET;
  }
}
#endif
