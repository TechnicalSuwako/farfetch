#if defined(__HAIKU__)
#include "haiku.h"
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
  color = GREEN;
  titlecolor = RED;
  const char *res = display_resolution();
  if (!res) minsize--;
  else free((void *)res);

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
}
#endif
