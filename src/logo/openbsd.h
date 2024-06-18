#ifndef LOGO_OPENBSD_H
#define LOGO_OPENBSD_H

#define GREY    "\e[1;30m"
#define RED     "\e[1;31m"
#define YELLOW  "\e[1;33m"
#define CYAN    "\e[1;36m"
#define RESET   "\e[0m"

#define COLOR YELLOW
#define TITLECOLOR YELLOW

char *LOGO[] = {
CYAN   "                                     _    " RESET,
CYAN   "                                    (_)   " RESET,
YELLOW "              |    .                      " RESET,
YELLOW "          .   |L  /|   .          " CYAN "_       " RESET,
YELLOW "      _ . |\\ _| \\--+._/| .      " CYAN " (_)      " RESET,
YELLOW "     / ||\\| Y J  )   / |/| ./             " RESET,
YELLOW "    J  |)'( |        ` F`.'/       " CYAN " _     " RESET,
YELLOW "  -<|  F         __     .-<       " CYAN " (_)    " RESET,
YELLOW "    | /       .-'" CYAN "." YELLOW " `.  /" CYAN "-. " YELLOW "L___           " RESET,
YELLOW "    J \\      <    " CYAN "\\ " YELLOW " | |" GREY " O" CYAN "\\" YELLOW "|.-' " CYAN " _        " RESET,
YELLOW "  _J \\  .-    \\" CYAN "/" GREY " O " CYAN "|" YELLOW" | \\  |F   " CYAN " (_)       " RESET,
YELLOW " '-F  -<_.     \\   .-'  `-' L__           " RESET,
YELLOW "__J  _   _.     >-'  )" RED "._." YELLOW "   |-'           " RESET,
YELLOW " `-|.'   /_.          " RED "\\_|" YELLOW "   F             " RESET,
YELLOW "  /.-   .                _.<              " RESET,
YELLOW " /'    /.'             .'  `\\             " RESET,
YELLOW "  /L  /'   |/      _.-'-\\                 " RESET,
YELLOW " /'J       ___.---'\\|                     " RESET,
YELLOW "   |\\  .--' V  | `. `                     " RESET,
YELLOW "   |/`. `-.     `._)                      " RESET,
YELLOW "      / .-.\\                              " RESET,
YELLOW "      \\ (  `\\                             " RESET,
YELLOW "       `.\\                                " RESET
};

char *LOGO_SMALL[] = {
YELLOW "      _____      " RESET,
YELLOW "    \\-     -/    " RESET,
YELLOW " \\_/         \\   " RESET,
YELLOW " |        " RESET "O O" YELLOW" |  " RESET,
YELLOW " |_  <   )  3 )  " RESET,
YELLOW " / \\         /   " RESET,
YELLOW "    /-_____-\\    " RESET,
YELLOW "                 " RESET,
YELLOW "                 " RESET,
YELLOW "                 " RESET,
YELLOW "                 " RESET
};

#endif
