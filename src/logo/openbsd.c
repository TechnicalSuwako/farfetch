#if defined(__OpenBSD__)
#include "openbsd.h"
#include "../resolution.h"

#include <string.h>
#include <stdlib.h>

char *LOGO[23];
char *LOGO_SMALL[23];
const char *color;
const char *titlecolor;
size_t logosize = 23;
int minsize = MIN_SIZE;

void getOS() {
  color = YELLOW;
  titlecolor = YELLOW;
  const char *res = display_resolution();
  if (!res) minsize--;
  else free((void *)res);

  for (int i = 0; i < LOGO_SIZE; i++) {
    LOGO[i] = NULL;
    LOGO_SMALL[i] = NULL;
  }

  LOGO[0]  = CYAN   "                                     _    " RESET;
  LOGO[1]  = CYAN   "                                    (_)   " RESET;
  LOGO[2]  = YELLOW "              |    .                      " RESET;
  LOGO[3]  = YELLOW "          .   |L  /|   .          " CYAN "_       " RESET;
  LOGO[4]  = YELLOW "      _ . |\\ _| \\--+._/| .      " CYAN " (_)      " RESET;
  LOGO[5]  = YELLOW "     / ||\\| Y J  )   / |/| ./             " RESET;
  LOGO[6]  = YELLOW "    J  |)'( |        ` F`.'/       " CYAN " _     " RESET;
  LOGO[7]  = YELLOW "  -<|  F         __     .-<       " CYAN " (_)    " RESET;
  LOGO[8]  = YELLOW "    | /       .-'" CYAN "." YELLOW " `.  /" CYAN "-. " YELLOW "L___           " RESET;
  LOGO[9]  = YELLOW "    J \\      <    " CYAN "\\ " YELLOW " | |" GREY " O" CYAN "\\" YELLOW "|.-' " CYAN " _        " RESET;
  LOGO[10] = YELLOW "  _J \\  .-    \\" CYAN "/" GREY " O " CYAN "|" YELLOW" | \\  |F   " CYAN " (_)       " RESET;
  LOGO[11] = YELLOW " '-F  -<_.     \\   .-'  `-' L__           " RESET;
  LOGO[12] = YELLOW "__J  _   _.     >-'  )" RED "._." YELLOW "   |-'           " RESET;
  LOGO[13] = YELLOW " `-|.'   /_.          " RED "\\_|" YELLOW "   F             " RESET;
  LOGO[14] = YELLOW "  /.-   .                _.<              " RESET;
  LOGO[15] = YELLOW " /'    /.'             .'  `\\             " RESET;
  LOGO[16] = YELLOW "  /L  /'   |/      _.-'-\\                 " RESET;
  LOGO[17] = YELLOW " /'J       ___.---'\\|                     " RESET;
  LOGO[18] = YELLOW "   |\\  .--' V  | `. `                     " RESET;
  LOGO[19] = YELLOW "   |/`. `-.     `._)                      " RESET;
  LOGO[20] = YELLOW "      / .-.\\                              " RESET;
  LOGO[21] = YELLOW "      \\ (  `\\                             " RESET;
  LOGO[22] = YELLOW "       `.\\                                " RESET;
  LOGO[22] = YELLOW "                                          " RESET;

  LOGO_SMALL[0] = YELLOW "      _____      " RESET;
  LOGO_SMALL[1] = YELLOW "    \\-     -/    " RESET;
  LOGO_SMALL[2] = YELLOW " \\_/         \\   " RESET;
  LOGO_SMALL[3] = YELLOW " |        " RESET "O O" YELLOW" |  " RESET;
  LOGO_SMALL[4] = YELLOW " |_  <   )  3 )  " RESET;
  LOGO_SMALL[5] = YELLOW " / \\         /   " RESET;
  LOGO_SMALL[6] = YELLOW "    /-_____-\\    " RESET;
  for (int i = 7; i < minsize; i++) {
    LOGO_SMALL[i] = YELLOW "                 " RESET;
  }
}
#endif
