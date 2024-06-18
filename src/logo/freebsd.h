#ifndef LOGO_FREEBSD_H
#define LOGO_FREEBSD_H

#define RED    "\e[1;31m"
#define WHITE  "\e[1;37m"
#define RESET   "\e[0m"

#define COLOR RED
#define TITLECOLOR RED

char *LOGO[] = {
WHITE "```                        " RED "`       " RESET,
WHITE "  ` `.....---..." RED "....--.```   -/    " RESET,
WHITE "  +o   .--`         " RED "/y:`      +.   " RESET,
WHITE "   yo`:.            " RED ":o      `+-    " RESET,
WHITE "    y/               " RED "-/`   -o/     " RESET,
WHITE "   .-                  " RED "::/sy+:.    " RESET,
WHITE "   /                     " RED "`--  /    " RESET,
WHITE "  `:                          " RED ":`   " RESET,
WHITE "  `:                          " RED ":`   " RESET,
WHITE "   /                          " RED "/    " RESET,
WHITE "   .-                        " RED "-.    " RESET,
WHITE "    --                      " RED "-.     " RESET,
WHITE "     `:`                  " RED "`:`      " RESET,
RED   "       .--             `--.        " RESET,
RED   "          .---.....----.           " RESET,
RED   "                                   " RESET,
RED   "                                   " RESET,
RED   "                                   " RESET
};

char *LOGO_SMALL[] = {
RED "/\\,-'''''-,/\\  " RESET,
RED "\\_)       (_/  " RESET,
RED "|           |  " RESET,
RED "|           |  " RESET,
RED " ;         ;   " RESET,
RED "  '-_____-'    " RESET
};

#endif
