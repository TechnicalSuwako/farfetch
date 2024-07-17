#if defined(__linux__)
#include "linux.h"
#include "../resolution.h"
#include "../wm.h"
#include "../libc.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char *LOGO[23];
char *LOGO_SMALL[23];
const char *color;
const char *titlecolor;
const char *logoname;
size_t logosize;
int minsize = MIN_SIZE;

void getDistro(const char *distroname) {
  const char *res = display_resolution();
  if (!res) minsize--;
  else free((void *)res);
  const char *wm = display_wm();
  if (!wm) minsize--;
  else free((void *)wm);
  const char *clang = display_libc();
  if (clang) minsize++;

  if (logoname == NULL) logoname = distroname;
  else {
    for (size_t i = 0; i < logosize; i++) {
      LOGO[i] = "";
    }
    for (int i = 0; i < minsize; i++) {
      LOGO_SMALL[i] = "";
    }
  }

  if (strncmp((char *)logoname, "alpine", strlen("alpine")) == 0) {
    color = MAGENTA;
    titlecolor = BLUE;
    logosize = 21;

    LOGO[0]  = BLUE "       .hddddddddddddddddddddddh.          " RESET;
    LOGO[1]  = BLUE "      :dddddddddddddddddddddddddd:         " RESET;
    LOGO[2]  = BLUE "     /dddddddddddddddddddddddddddd/        " RESET;
    LOGO[3]  = BLUE "    +dddddddddddddddddddddddddddddd+       " RESET;
    LOGO[4]  = BLUE "  `sdddddddddddddddddddddddddddddddds`     " RESET;
    LOGO[5]  = BLUE " `ydddddddddddd++hdddddddddddddddddddy`    " RESET;
    LOGO[6]  = BLUE ".hddddddddddd+`  `+ddddh:-sdddddddddddh.   " RESET;
    LOGO[7]  = BLUE "hdddddddddd+`      `+y:    .sddddddddddh   " RESET;
    LOGO[8]  = BLUE "ddddddddh+`   `//`   `.`     -sddddddddd   " RESET;
    LOGO[9]  = BLUE "ddddddh+`   `/hddh/`   `:s-    -sddddddd   " RESET;
    LOGO[10] = BLUE "ddddh+`   `/+/dddddh/`   `+s-    -sddddd   " RESET;
    LOGO[11] = BLUE "ddd+`   `/o` :dddddddh/`   `oy-    .yddd   " RESET;
    LOGO[12] = BLUE "hdddyo+ohddyosdddddddddho+oydddy++ohdddh   " RESET;
    LOGO[13] = BLUE ".hddddddddddddddddddddddddddddddddddddh.   " RESET;
    LOGO[14] = BLUE " `yddddddddddddddddddddddddddddddddddy`    " RESET;
    LOGO[15] = BLUE "  `sdddddddddddddddddddddddddddddddds`     " RESET;
    LOGO[16] = BLUE "    +dddddddddddddddddddddddddddddd+       " RESET;
    LOGO[17] = BLUE "     /dddddddddddddddddddddddddddd/        " RESET;
    LOGO[18] = BLUE "      :dddddddddddddddddddddddddd:         " RESET;
    LOGO[19] = BLUE "       .hddddddddddddddddddddddh.          " RESET;
    LOGO[20] = BLUE "                                           " RESET;

    LOGO_SMALL[0] = BLUE  "   /\\ /\\      " RESET;
    LOGO_SMALL[1] = BLUE  "  /" WHITE "/ " BLUE "\\  \\     " RESET;
    LOGO_SMALL[2] = BLUE  " /" WHITE "/   " BLUE "\\  \\    " RESET;
    LOGO_SMALL[3] = BLUE  "/" WHITE "//    " BLUE "\\  \\   " RESET;
    LOGO_SMALL[4] = WHITE "//      " BLUE "\\  \\  " RESET;
    LOGO_SMALL[5] = BLUE  "         \\    " RESET;
    for (int i = 6; i < minsize; i++) {
      LOGO_SMALL[i]  = BLUE "              " RESET;
    }
  } else if (strncmp((char *)logoname, "arch", strlen("arch")) == 0) {
    color = CYAN;
    titlecolor = CYAN;
    logosize = 20;

    LOGO[0]  = CYAN "                  -`                    " RESET;
    LOGO[1]  = CYAN "                 .o+`                   " RESET;
    LOGO[2]  = CYAN "                `ooo/                   " RESET;
    LOGO[3]  = CYAN "               `+oooo:                  " RESET;
    LOGO[4]  = CYAN "              `+oooooo:                 " RESET;
    LOGO[5]  = CYAN "              -+oooooo+:                " RESET;
    LOGO[6]  = CYAN "            `/:-:++oooo+:               " RESET;
    LOGO[7]  = CYAN "           `/++++/+++++++:              " RESET;
    LOGO[8]  = CYAN "          `/++++++++++++++:             " RESET;
    LOGO[9]  = CYAN "         `/+++ooooooooooooo/`           " RESET;
    LOGO[10] = CYAN "        ./ooosssso++osssssso+`          " RESET;
    LOGO[11] = CYAN "       .oossssso-````/ossssss+`         " RESET;
    LOGO[12] = CYAN "      -osssssso.      :ssssssso.        " RESET;
    LOGO[13] = CYAN "     :osssssss/        osssso+++.       " RESET;
    LOGO[14] = CYAN "    /ossssssss/        +ssssooo/-       " RESET;
    LOGO[15] = CYAN "  `/ossssso+/:-        -:/+osssso+-     " RESET;
    LOGO[16] = CYAN " `+sso+:-`                 `.-/+oso:    " RESET;
    LOGO[17] = CYAN "`++:.                           `-/+/   " RESET;
    LOGO[18] = CYAN ".`                                 `/   " RESET;
    LOGO[19] = CYAN "                                        " RESET;

    LOGO_SMALL[0] = CYAN  "      /\\        " RESET;
    LOGO_SMALL[1] = CYAN  "     /  \\       " RESET;
    LOGO_SMALL[2] = CYAN  "    /\\   \\      " RESET;
    LOGO_SMALL[3] = WHITE "   /      \\     " RESET;
    LOGO_SMALL[4] = WHITE "  /   ,,   \\    " RESET;
    LOGO_SMALL[5] = WHITE " /   |  |  -\\   " RESET;
    LOGO_SMALL[6] = WHITE "/_-''    ''-_\\  " RESET;
    for (int i = 7; i < minsize; i++) {
      LOGO_SMALL[i]  = CYAN "                " RESET;
    }
  } else if (strncmp((char *)logoname, "arco", strlen("arch")) == 0) {
    color = BLUE;
    titlecolor = WHITE;
    logosize = 20;

    LOGO[0]  = BLUE "                    /-                      " RESET;
    LOGO[1]  = BLUE "                   ooo:                     " RESET;
    LOGO[2]  = BLUE "                  yoooo/                    " RESET;
    LOGO[3]  = BLUE "                 yooooooo                   " RESET;
    LOGO[4]  = BLUE "                yooooooooo                  " RESET;
    LOGO[5]  = BLUE "               yooooooooooo                 " RESET;
    LOGO[6]  = BLUE "             .yooooooooooooo                " RESET;
    LOGO[7]  = BLUE "            .oooooooooooooooo               " RESET;
    LOGO[8]  = BLUE "           .oooooooarcoooooooo              " RESET;
    LOGO[9]  = BLUE "          .ooooooooo-oooooooooo             " RESET;
    LOGO[10] = BLUE "         .ooooooooo-  oooooooooo            " RESET;
    LOGO[11] = BLUE "        :ooooooooo.    :ooooooooo           " RESET;
    LOGO[12] = BLUE "       :ooooooooo.      :ooooooooo          " RESET;
    LOGO[13] = BLUE "      :oooarcooo         .oooarcooo         " RESET;
    LOGO[14] = BLUE "     :ooooooooy           .ooooooooo        " RESET;
    LOGO[15] = BLUE "    :ooooooooo   " WHITE "/ooooooooooooooooooo       " RESET;
    LOGO[16] = BLUE "   :ooooooooo      " WHITE ".-ooooooooooooooooo.     " RESET;
    LOGO[17] = BLUE "  ooooooooo-             " WHITE "-ooooooooooooo.    " RESET;
    LOGO[18] = BLUE " ooooooooo-                 " WHITE ".-oooooooooo.   " RESET;
    LOGO[19] = BLUE "ooooooooo.                     " WHITE "-ooooooooo   " RESET;

    LOGO_SMALL[0]  = BLUE "          A             " RESET;
    LOGO_SMALL[1]  = BLUE "         ooo            " RESET;
    LOGO_SMALL[2]  = BLUE "        ooooo           " RESET;
    LOGO_SMALL[3]  = BLUE "       ooooooo          " RESET;
    LOGO_SMALL[4]  = BLUE "      ooooooooo         " RESET;
    LOGO_SMALL[5]  = BLUE "     ooooo ooooo        " RESET;
    LOGO_SMALL[6]  = BLUE "    ooooo   ooooo       " RESET;
    LOGO_SMALL[7]  = BLUE "   ooooo     ooooo      " RESET;
    LOGO_SMALL[8]  = BLUE "  ooooo  " WHITE "<oooooooo>     " RESET;
    LOGO_SMALL[9]  = BLUE " ooooo      " WHITE "<oooooo>    " RESET;
    LOGO_SMALL[10] = BLUE "ooooo          " WHITE "<oooo>   " RESET;
    for (int i = 11; i < minsize; i++) {
      LOGO_SMALL[i]  = BLUE "                        " RESET;
    }
  } else if (strncmp((char *)logoname, "artix", strlen("artix")) == 0) {
    color = CYAN;
    titlecolor = CYAN;
    logosize = 21;

    LOGO[0]  = CYAN "                   '                     " RESET;
    LOGO[1]  = CYAN "                  'o'                    " RESET;
    LOGO[2]  = CYAN "                 'ooo'                   " RESET;
    LOGO[3]  = CYAN "                'ooxoo'                  " RESET;
    LOGO[4]  = CYAN "               'ooxxxoo'                 " RESET;
    LOGO[5]  = CYAN "              'oookkxxoo'                " RESET;
    LOGO[6]  = CYAN "             'oiioxkkxxoo'               " RESET;
    LOGO[7]  = CYAN "            ':;:iiiioxxxoo'              " RESET;
    LOGO[8]  = CYAN "               `'.;::ioxxoo'             " RESET;
    LOGO[9]  = CYAN "          '-.      `':;jiooo'            " RESET;
    LOGO[10] = CYAN "         'oooio-..     `'i:io'           " RESET;
    LOGO[11] = CYAN "        'ooooxxxxoio:,.   `'-;'          " RESET;
    LOGO[12] = CYAN "       'ooooxxxxxkkxoooIi:-.  `'         " RESET;
    LOGO[13] = CYAN "      'ooooxxxxxkkkkxoiiiiiji'           " RESET;
    LOGO[14] = CYAN "     'ooooxxxxxkxxoiiii:'`     .i'       " RESET;
    LOGO[15] = CYAN "    'ooooxxxxxoi:::'`       .;ioxo'      " RESET;
    LOGO[16] = CYAN "   'ooooxooi::'`         .:iiixkxxo'     " RESET;
    LOGO[17] = CYAN "  'ooooi:'`                `'';ioxxo'    " RESET;
    LOGO[18] = CYAN " 'i:'`                          '':io'   " RESET;
    LOGO[19] = CYAN "'`                                   `'  " RESET;
    LOGO[20] = CYAN "                                         " RESET;

    LOGO_SMALL[0] = CYAN "      /\\        " RESET;
    LOGO_SMALL[1] = CYAN "     /  \\       " RESET;
    LOGO_SMALL[2] = CYAN "    /`'.,\\      " RESET;
    LOGO_SMALL[3] = CYAN "   /     ',     " RESET;
    LOGO_SMALL[4] = CYAN "  /      ,`\\    " RESET;
    LOGO_SMALL[5] = CYAN " /   ,.'`.  \\   " RESET;
    LOGO_SMALL[6] = CYAN "/.,'`     `'.\\  " RESET;
    for (int i = 7; i < minsize; i++) {
      LOGO_SMALL[i]  = CYAN "                " RESET;
    }
  } else if (strncmp((char *)logoname, "centos", strlen("centos")) == 0) {
    color = GREEN;
    titlecolor = YELLOW;
    logosize = 18;

    LOGO[0]  = YELLOW  "                 ..                    " RESET;
    LOGO[1]  = YELLOW  "               .PLTJ.                  " RESET;
    LOGO[2]  = YELLOW  "              <><><><>                 " RESET;
    LOGO[3]  = GREEN   "     KKSSV' 4KKK " YELLOW "LJ" MAGENTA " KKKL.'VSSKK        " RESET;
    LOGO[4]  = GREEN   "     KKV' 4KKKKK " YELLOW "LJ" MAGENTA " KKKKAL 'VKK        " RESET;
    LOGO[5]  = GREEN   "     V' ' 'VKKKK " YELLOW "LJ" MAGENTA " KKKKV' ' 'V        " RESET;
    LOGO[6]  = GREEN   "     .4MA.' 'VKK " YELLOW "LJ" MAGENTA " KKV' '.4Mb.        " RESET;
    LOGO[7]  = GREEN   "   . KKKKKA.' 'V " YELLOW "LJ" MAGENTA " V' '.4KKKKK .      " RESET;
    LOGO[8]  = GREEN   " .4D KKKKKKKA.'' " YELLOW "LJ" MAGENTA " ''.4KKKKKKK FA.    " RESET;
    LOGO[9]  = MAGENTA "<QDD ++++++++++++  " BLUE "++++++++++++ GFD>   " RESET;
    LOGO[10] = GREEN   " 'VD KKKKKKKK'.. " GREEN "LJ " YELLOW "..'KKKKKKKK FV     " RESET;
    LOGO[11] = BLUE    "   ' VKKKKK'. .4 " GREEN "LJ " YELLOW "K. .'KKKKKV '      " RESET;
    LOGO[12] = BLUE    "      'VK'. .4KK " GREEN "LJ " YELLOW "KKA. .'KV'         " RESET;
    LOGO[13] = BLUE    "     A. . .4KKKK " GREEN "LJ " YELLOW "KKKKA. . .4        " RESET;
    LOGO[14] = BLUE    "     KKA. 'KKKKK " GREEN "LJ " YELLOW "KKKKK' .4KK        " RESET;
    LOGO[15] = BLUE    "     KKSSA. VKKK " GREEN "LJ " YELLOW "KKKV .4SSKK        " RESET;
    LOGO[16] = GREEN   "              <><><><>                 " RESET;
    LOGO[17] = GREEN   "               'MKKM'                  " RESET;
    LOGO[18] = GREEN   "                 ''                    " RESET;

    LOGO_SMALL[0] = GREEN   " ____" YELLOW "^" MAGENTA "____    " RESET;
    LOGO_SMALL[1] = GREEN   " |\\  " YELLOW "|" MAGENTA "  /|    " RESET;
    LOGO_SMALL[2] = GREEN   " | \\ " YELLOW "|" MAGENTA " / |    " RESET;
    LOGO_SMALL[3] = MAGENTA "<---- " BLUE "---->   " RESET;
    LOGO_SMALL[4] = BLUE    " | / " GREEN "|" YELLOW " \\ |    " RESET;
    LOGO_SMALL[5] = BLUE    " |/__" GREEN "|" YELLOW "__\\|    " RESET;
    LOGO_SMALL[6] = GREEN   "     v        " RESET;
    for (int i = 7; i < minsize; i++) {
      LOGO_SMALL[i]  = BLUE "              " RESET;
    }
  } else if (strncmp((char *)logoname, "crux", strlen("crux")) == 0) {
    color = MAGENTA;
    titlecolor = BLUE;
    logosize = 19;

    LOGO[0]  = BLUE    "         odddd             " RESET;
    LOGO[1]  = BLUE    "      oddxkkkxxdoo         " RESET;
    LOGO[2]  = BLUE    "     ddcoddxxxdoool        " RESET;
    LOGO[3]  = BLUE    "     xdclodod  olol        " RESET;
    LOGO[4]  = BLUE    "     xoc  xdd  olol        " RESET;
    LOGO[5]  = BLUE    "     xdc  " MAGENTA "k00" BLUE "Okdlol        " RESET;
    LOGO[6]  = BLUE    "     xxd" MAGENTA "kOKKKOkd" BLUE "ldd        " RESET;
    LOGO[7]  = BLUE    "     xdco" MAGENTA "xOkdlo" BLUE "dldd        " RESET;
    LOGO[8]  = BLUE    "     ddc:cl" MAGENTA "lll" BLUE "oooodo       " RESET;
    LOGO[9]  = BLUE    "   odxxdd" WHITE "xkO000kx" BLUE "ooxdo     " RESET;
    LOGO[10] = BLUE    "  oxdd" WHITE "x0NMMMMMMWW0od" BLUE "kkxo   " RESET;
    LOGO[11] = BLUE    " oooxd" WHITE "0WMMMMMMMMMW0o" BLUE "dxkx   " RESET;
    LOGO[12] = BLUE    "docldkXW" WHITE "MMMMMMMWWN" BLUE "Odolco   " RESET;
    LOGO[13] = BLUE    "xx" MAGENTA "dx" BLUE "kxxOKN" WHITE "WMMWN" BLUE "0xdoxo::c   " RESET;
    LOGO[14] = MAGENTA "xOkkO" BLUE "0oo" WHITE "odOW" MAGENTA "WW" BLUE "XkdodOxc:l   " RESET;
    LOGO[15] = MAGENTA "dkkkxkkk" WHITE "OKX" MAGENTA "NNNX0Oxx" BLUE "xc:cd   " RESET;
    LOGO[16] = MAGENTA " odxxdx" WHITE "xllod" MAGENTA "ddooxx" BLUE "dc:ldo   " RESET;
    LOGO[17] = MAGENTA "   lodd" BLUE "dolccc" MAGENTA "ccox" BLUE "xoloo     " RESET;
    LOGO[18] = BLUE "                           " RESET;

    LOGO_SMALL[0] = BLUE    "    ___     " RESET;
    LOGO_SMALL[1] = BLUE    "   (" WHITE ".·" BLUE " |    " RESET;
    LOGO_SMALL[2] = BLUE    "   (" MAGENTA "<>" BLUE " |    " RESET;
    LOGO_SMALL[3] = BLUE    "  / " WHITE "__" BLUE "  \\   " RESET;
    LOGO_SMALL[4] = BLUE    " ( " WHITE "/  \\" BLUE " /|  " RESET;
    LOGO_SMALL[5] = MAGENTA "_" BLUE "/\\ "WHITE "__)" BLUE "/" MAGENTA "_" BLUE ")  " RESET;
    LOGO_SMALL[6] = MAGENTA "\\/" BLUE "-____" MAGENTA "\\/   " RESET;
    for (int i = 7; i < minsize; i++) {
      LOGO_SMALL[i]  = BLUE "            " RESET;
    }
  } else if (strncmp((char *)logoname, "debian", strlen("debian")) == 0) {
    color = RED;
    titlecolor = RED;
    logosize = 18;

    LOGO[0]  = WHITE "       _,met$$$$$gg.          " RESET;
    LOGO[1]  = WHITE "    ,g$$$$$$$$$$$$$$$P.       " RESET;
    LOGO[2]  = WHITE "  ,g$$P\"     \"\"\"Y$$.\".        " RESET;
    LOGO[3]  = WHITE " ,$$P'              `$$$.     " RESET;
    LOGO[4]  = WHITE "',$$P       ,ggs.     `$$b:   " RESET;
    LOGO[5]  = WHITE "`d$$'     ,$P\"'   " RED "." WHITE "    $$$    " RESET;
    LOGO[6]  = WHITE " $$P      d$'     " RED "," WHITE "    $$P    " RESET;
    LOGO[7]  = WHITE " $$:      $$.   -    ,d$$'    " RESET;
    LOGO[8]  = WHITE " $$;      Y$b._   _,d$P'      " RESET;
    LOGO[9]  = WHITE " Y$$.    " RED "`." WHITE "`\"Y$$$$P\"'         " RESET;
    LOGO[10] = WHITE " `$$b      " RED "\"-.__" WHITE "              " RESET;
    LOGO[11] = WHITE "  `Y$$                        " RESET;
    LOGO[12] = WHITE "   `Y$$.                      " RESET;
    LOGO[13] = WHITE "     `$$b.                    " RESET;
    LOGO[14] = WHITE "       `Y$$b.                 " RESET;
    LOGO[15] = WHITE "          `\"Y$b._             " RESET;
    LOGO[16] = WHITE "              `\"\"\"            " RESET;
    LOGO[17]  = RED "                              " RESET;

    LOGO_SMALL[0] = RED "  _____    " RESET;
    LOGO_SMALL[1] = RED " /  __ \\   " RESET;
    LOGO_SMALL[2] = RED "|  /    |  " RESET;
    LOGO_SMALL[3] = RED "|  \\___-   " RESET;
    LOGO_SMALL[4] = RED "-_         " RESET;
    LOGO_SMALL[5] = RED "  --_      " RESET;
    for (int i = 6; i < minsize; i++) {
      LOGO_SMALL[i]  = RED "           " RESET;
    }
  } else if (strncmp((char *)logoname, "devuan", strlen("devuan")) == 0) {
    color = MAGENTA;
    titlecolor = MAGENTA;
    logosize = 16;

    LOGO[0]  = MAGENTA "   ..,,;;;::;,..                   " RESET;
    LOGO[1]  = MAGENTA "           `':ddd;:,.              " RESET;
    LOGO[2]  = MAGENTA "                 `'dPPd:,.         " RESET;
    LOGO[3]  = MAGENTA "                     `:b$$b`.      " RESET;
    LOGO[4]  = MAGENTA "                        'P$$$d`    " RESET;
    LOGO[5]  = MAGENTA "                         .$$$$$`   " RESET;
    LOGO[6]  = MAGENTA "                         ;$$$$$P   " RESET;
    LOGO[7]  = MAGENTA "                      .:P$$$$$$`   " RESET;
    LOGO[8]  = MAGENTA "                  .,:b$$$$$$$;'    " RESET;
    LOGO[9]  = MAGENTA "             .,:dP$$$$$$$$b:'      " RESET;
    LOGO[10] = MAGENTA "      .,:;db$$$$$$$$$$Pd'`         " RESET;
    LOGO[11] = MAGENTA " ,db$$$$$$$$$$$$$$b:'`             " RESET;
    LOGO[12] = MAGENTA ":$$$$$$$$$$$$b:'`                  " RESET;
    LOGO[13] = MAGENTA " `$$$$$bd:''`                      " RESET;
    LOGO[14] = MAGENTA "   `'''`                           " RESET;
    LOGO[15] = MAGENTA "                                   " RESET;

    LOGO_SMALL[0] = MAGENTA "__   " RESET;
    LOGO_SMALL[1] = MAGENTA "  \\  " RESET;
    LOGO_SMALL[2] = MAGENTA " _/  " RESET;
    for (int i = 3; i < minsize; i++) {
      LOGO_SMALL[i]  = MAGENTA "     " RESET;
    }
  } else if (strncmp((char *)logoname, "fedora", strlen("fedora")) == 0) {
    color = BLUE;
    titlecolor = BLUE;
    logosize = 17;

    LOGO[0]  = BLUE "          /:-------------:\\          " RESET;
    LOGO[1]  = BLUE "       :-------------------::        " RESET;
    LOGO[2]  = BLUE "     :-----------" WHITE "/shhOHbmp" BLUE "---:\\      " RESET;
    LOGO[3]  = BLUE "   /-----------" WHITE "omMMMNNNMMD" BLUE "  ---:     " RESET;
    LOGO[4]  = BLUE "  :-----------" WHITE "sMMMMNMNMP" BLUE ".    ---:    " RESET;
    LOGO[5]  = BLUE " :-----------" WHITE ":MMMdP" BLUE "-------    ---\\   " RESET;
    LOGO[6]  = BLUE ",------------" WHITE ":MMMd" BLUE "--------    ---:   " RESET;
    LOGO[7]  = BLUE ":------------" WHITE ":MMMd" BLUE "-------    .---:   " RESET;
    LOGO[8]  = BLUE ":----    " WHITE "oNMMMMMMMMMNho" BLUE "     .----:   " RESET;
    LOGO[9]  = BLUE ":--     ." WHITE "+shhhMMMmhhy++" BLUE "   .------/   " RESET;
    LOGO[10] = BLUE ":-    -------:" WHITE "MMMd" BLUE "--------------:    " RESET;
    LOGO[11] = BLUE ":-   --------" WHITE "/MMMd" BLUE "-------------;     " RESET;
    LOGO[12] = BLUE ":-    ------" WHITE "/hMMMy" BLUE "------------:      " RESET;
    LOGO[13] = BLUE ":-- " WHITE ":dMNdhhdNMMNo" BLUE "------------;       " RESET;
    LOGO[14] = BLUE ":---" WHITE ":sdNMMMMNds:" BLUE "------------:        " RESET;
    LOGO[15] = BLUE ":------" WHITE ":://:" BLUE "-------------::          " RESET;
    LOGO[16] = BLUE ":---------------------://            " RESET;

    LOGO_SMALL[0] = WHITE "      _____      " RESET;
    LOGO_SMALL[1] = WHITE "     /   __)" BLUE "\\    " RESET;
    LOGO_SMALL[2] = WHITE "     |  /  " BLUE "\\ \\   " RESET;
    LOGO_SMALL[3] = BLUE  "  __" WHITE "_|  |_" BLUE "_/ /   " RESET;
    LOGO_SMALL[4] = BLUE  " / " WHITE "(_    _)" BLUE "_/    " RESET;
    LOGO_SMALL[5] = BLUE  "/ /  " WHITE "|  |        " RESET;
    LOGO_SMALL[6] = BLUE  "\\ \\" WHITE "__/  |        " RESET;
    LOGO_SMALL[7] = BLUE  " \\" WHITE "(_____/        " RESET;
    for (int i = 8; i < minsize; i++) {
      LOGO_SMALL[i] = BLUE  "                 " RESET;
    }
  } else if (strncmp((char *)logoname, "gentoo", strlen("gentoo")) == 0) {
    color = MAGENTA;
    titlecolor = MAGENTA;
    logosize = 19;

    LOGO[0]  = MAGENTA "         -/oyddmdhs+:.                " RESET;
    LOGO[1]  = MAGENTA "     -o" WHITE "dNMMMMMMMMNNmhy+" MAGENTA "-`             " RESET;
    LOGO[2]  = MAGENTA "   -y" WHITE "NMMMMMMMMMMMNNNmmdhy" MAGENTA "+-           " RESET;
    LOGO[3]  = MAGENTA " `o" WHITE "mMMMMMMMMMMMMNmdmmmmddhhy" MAGENTA "/`        " RESET;
    LOGO[4]  = MAGENTA " om" WHITE "MMMMMMMMMMMN" MAGENTA "hhyyyo" WHITE "hmdddhhhd" MAGENTA "o`      " RESET;
    LOGO[5]  = MAGENTA ".y" WHITE "dMMMMMMMMMMd" MAGENTA "hs++so/s" WHITE "mdddhhhhdm" MAGENTA "+`    " RESET;
    LOGO[6]  = MAGENTA " oy" WHITE "hdmNMMMMMMMN" MAGENTA "dyooy" WHITE "dmddddhhhhyhN" MAGENTA "d.   " RESET;
    LOGO[7]  = MAGENTA "  :o" WHITE "yhhdNNMMMMMMMNNNmmdddhhhhhyym" MAGENTA "Mh   " RESET;
    LOGO[8]  = MAGENTA "    .:" WHITE "+sydNMMMMMNNNmmmdddhhhhhhmM" MAGENTA "my   " RESET;
    LOGO[9]  = MAGENTA "       /m" WHITE "MMMMMMNNNmmmdddhhhhhmMNh" MAGENTA "s:   " RESET;
    LOGO[10] = MAGENTA "    `o" WHITE "NMMMMMMMNNNmmmddddhhdmMNhs" MAGENTA "+`    " RESET;
    LOGO[11] = MAGENTA "  `s" WHITE "NMMMMMMMMNNNmmmdddddmNMmhs" MAGENTA "/.      " RESET;
    LOGO[12] = MAGENTA " /N" WHITE "MMMMMMMMNNNNmmmdddmNMNdso" MAGENTA ":`        " RESET;
    LOGO[13] = MAGENTA "+M" WHITE "MMMMMMNNNNNmmmmdmNMNdso" MAGENTA "/-           " RESET;
    LOGO[14] = MAGENTA "yM" WHITE "MNNNNNNNmmmmmNNMmhs+/" MAGENTA" -`             " RESET;
    LOGO[15] = MAGENTA "/h" WHITE "MMNNNNNNNNMNdhs++/" MAGENTA "-`                " RESET;
    LOGO[16] = MAGENTA "`/" WHITE "ohdmmddhys+++/:" MAGENTA ".`                   " RESET;
    LOGO[17] = MAGENTA "  `-//////:--.                        " RESET;
    LOGO[18] = MAGENTA "                                      " RESET;

    LOGO_SMALL[0] = MAGENTA " _-----_     " RESET;
    LOGO_SMALL[1] = MAGENTA "(       \\    " RESET;
    LOGO_SMALL[2] = MAGENTA "\\    0   \\   " RESET;
    LOGO_SMALL[3] = WHITE   " \\        )  " RESET;
    LOGO_SMALL[4] = WHITE   " /      _/   " RESET;
    LOGO_SMALL[5] = WHITE   "(     _-     " RESET;
    LOGO_SMALL[6] = WHITE   "\\____-       " RESET;
    for (int i = 7; i < minsize; i++) {
      LOGO_SMALL[i]  = MAGENTA "             " RESET;
    }
  } else if (strncmp((char *)logoname, "kubuntu", strlen("kubuntu")) == 0) {
    color = BLUE;
    titlecolor = BLUE;
    logosize = 20;

    LOGO[0]  = BLUE "           `.:/ossyyyysso/:.               " RESET;
    LOGO[1]  = BLUE "        .:oyyyyyyyyyyyyyyyyyyo:`           " RESET;
    LOGO[2]  = BLUE "      -oyyyyyyyo" WHITE "dMMy" BLUE "yyyyyyysyyyyo-         " RESET;
    LOGO[3]  = BLUE "    -syyyyyyyyyy" WHITE "dMMy" BLUE "oyyyy" WHITE "dmMMy" BLUE "yyyys-       " RESET;
    LOGO[4]  = BLUE "   oyyys" WHITE "dMy" BLUE "syyyy" WHITE "dMMMMMMMMMMMMMy" BLUE "yyyyyyo     " RESET;
    LOGO[5]  = BLUE " `oyyyy" WHITE "dMMMMy" BLUE "syysoooooo" WHITE "dMMMMy" BLUE "yyyyyyyyo`    " RESET;
    LOGO[6]  = BLUE " oyyyyyy" WHITE "dMMMMy" BLUE "yyyyyyyyyyy" WHITE "sdMMy" BLUE "sssssyyyo    " RESET;
    LOGO[7]  = BLUE "-yyyyyyyy" WHITE "dMy" BLUE "syyyyyyyyyyyyyys" WHITE "dMMMMMy" BLUE "syyy-   " RESET;
    LOGO[8]  = BLUE "oyyyysoo" WHITE "dMy" BLUE "yyyyyyyyyyyyyyyyyy" WHITE "dMMMMy" BLUE "syyyo   " RESET;
    LOGO[9]  = BLUE "yyys" WHITE "dMMMMMy" BLUE "yyyyyyyyyyyyyyyyyysosyyyyyyyy   " RESET;
    LOGO[10] = BLUE "yyys" WHITE "dMMMMMy" BLUE "yyyyyyyyyyyyyyyyyyyyyyyyyyyyy   " RESET;
    LOGO[11] = BLUE "oyyyyysos" WHITE "dy" BLUE "yyyyyyyyyyyyyyyyyy" WHITE "dMMMMy" BLUE "syyyo   " RESET;
    LOGO[12] = BLUE "-yyyyyyyy" WHITE "dMy" BLUE "syyyyyyyyyyyyyys" WHITE "dMMMMMy" BLUE "syyy-   " RESET;
    LOGO[13] = BLUE " oyyyyyy" WHITE "dMMMy" BLUE "syyyyyyyyyyys" WHITE "dMMy" BLUE "oyyyoyyyo    " RESET;
    LOGO[14] = BLUE " `oyyyy" WHITE "dMMMy" BLUE "syyyoooooo" WHITE "dMMMMy" BLUE "oyyyyyyyyo     " RESET; 
    LOGO[15] = BLUE "   oyyysyyoyyyys" WHITE "dMMMMMMMMMMMy" BLUE "yyyyyyyo      " RESET;
    LOGO[16] = BLUE "    -syyyyyyyyy" WHITE "dMMMy" BLUE "syyy" WHITE "dMMMy" BLUE "syyyys-       " RESET;
    LOGO[17] = BLUE "      -oyyyyyyy" WHITE "dMMy" BLUE "yyyyyysosyyyyo-         " RESET;
    LOGO[18] = BLUE "        ./oyyyyyyyyyyyyyyyyyyo/.           " RESET;
    LOGO[19] = BLUE "           `.:/oosyyyysso/:.`              " RESET;

    LOGO_SMALL[0] = BLUE "     |      " RESET;
    LOGO_SMALL[1] = BLUE "  \\  ---\\/  " RESET;
    LOGO_SMALL[2] = BLUE "  /  ---  \\ " RESET;
    LOGO_SMALL[3] = BLUE " -| |   |  =" RESET;
    LOGO_SMALL[4] = BLUE "  \\  --- _/ " RESET;
    LOGO_SMALL[5] = BLUE " /   ---/ \\ " RESET;
    for (int i = 6; i < minsize; i++) {
      LOGO_SMALL[i]  = BLUE "            " RESET;
    }
  } else if (strncmp((char *)logoname, "linuxmint", strlen("linuxmint")) == 0) {
    color = GREEN;
    titlecolor = GREEN;
    logosize = 19;

    LOGO[0]  = WHITE "             ...-:::::-...               " RESET;
    LOGO[1]  = WHITE "          .-MMMMMMMMMMMMMMM-.            " RESET;
    LOGO[2]  = WHITE "      .-MMMM" GREEN "`..-:::::::-..`" WHITE "MMMM-.        " RESET;
    LOGO[3]  = WHITE "    .:MMMM" GREEN ".:MMMMMMMMMMMMMMM:." WHITE "MMMM:.      " RESET;
    LOGO[4]  = WHITE "   -MMM" GREEN "-M---MMMMMMMMMMMMMMMMMMM." WHITE "MMM-     " RESET;
    LOGO[5]  = WHITE " `:MMM" GREEN ":MM`  :MMMM:....::-...-MMMM:" WHITE "MMM:`  " RESET;
    LOGO[6]  = WHITE " :MMM" GREEN ":MMM`  :MM:`  ``    ``  `:MMM:" WHITE "MMM:  " RESET;
    LOGO[7]  = WHITE ".MMM" GREEN ".MMMM`  :MM.  -MM.  .MM-  `MMMM." WHITE "MMM. " RESET;
    LOGO[8]  = WHITE ":MMM" GREEN ":MMMM`  :MM.  -MM-  .MM:  `MMMM-" WHITE "MMM: " RESET;
    LOGO[9]  = WHITE ":MMM" GREEN ":MMMM`  :MM.  -MM-  .MM:  `MMMM:" WHITE "MMM: " RESET;
    LOGO[10] = WHITE ":MMM" GREEN ":MMMM`  :MM.  -MM-  .MM:  `MMMM-" WHITE "MMM: " RESET;
    LOGO[11] = WHITE ".MMM" GREEN ".MMMM`  :MM:--:MM:--:MM:  `MMMM." WHITE "MMM. " RESET;
    LOGO[12] = WHITE " :MMM" GREEN ":MMM-  `-MMMMMMMMMMMM-`  -MMM-" WHITE "MMM:  " RESET;
    LOGO[13] = WHITE "  :MMM" GREEN ":MMM:`                `:MMM:" WHITE "MMM:   " RESET;
    LOGO[14] = WHITE "   .MMM" GREEN ".MMMM:--------------:MMMM." WHITE "MMM.    " RESET;
    LOGO[15] = WHITE "     '-MMMM" GREEN ".-MMMMMMMMMMMMMMM-." WHITE "MMMM-'     " RESET;
    LOGO[16] = WHITE "       '.-MMMM" GREEN "``--:::::--``" WHITE "MMMM-.'       " RESET;
    LOGO[17] = WHITE "            '-MMMMMMMMMMMMM-'            " RESET;
    LOGO[18] = WHITE "               ``-:::::-``               " RESET;

    LOGO_SMALL[0] = GREEN " ___________  " RESET;
    LOGO_SMALL[1] = GREEN "|_          \\ " RESET;
    LOGO_SMALL[2] = GREEN "  | " WHITE "| _____ " GREEN "| " RESET;
    LOGO_SMALL[3] = GREEN "  | " WHITE "| | | | " GREEN "| " RESET;
    LOGO_SMALL[4] = GREEN "  | " WHITE "| | | | " GREEN "| " RESET;
    LOGO_SMALL[5] = GREEN "  | " WHITE "\\_____/ " GREEN "| " RESET;
    LOGO_SMALL[6] = GREEN "  \\_________/ " RESET;
    for (int i = 7; i < minsize; i++) {
      LOGO_SMALL[i]  = GREEN "              " RESET;
    }
  } else if (strncmp((char *)logoname, "lubuntu", strlen("lubuntu")) == 0) {
    color = BLUE;
    titlecolor = BLUE;
    logosize = 20;

    LOGO[0]  = BLUE "           `-mddhhhhhhhhhddmss`             " RESET;
    LOGO[1]  = BLUE "        ./mdhhhhhhhhhhhhhhhhhhhhhh.         " RESET;
    LOGO[2]  = BLUE "     :mdhhhhhhhhhhhhhhhhhhhhhhhhhhhm`       " RESET;
    LOGO[3]  = BLUE "   :ymhhhhhhhhhhhhhhhyyyyyyhhhhhhhhhy:      " RESET;
    LOGO[4]  = BLUE "  `odhyyyhhhhhhhhhy+-````./syhhhhhhhho`     " RESET;
    LOGO[5]  = BLUE " `hhy..:oyhhhhhhhy-`:osso/..:/++oosyyyh`    " RESET;
    LOGO[6]  = BLUE " dhhs   .-/syhhhhs`shhhhhhyyyyyyyyyyyyhs    " RESET;
    LOGO[7]  = BLUE ":hhhy`  yso/:+syhy/yhhhhhshhhhhhhhhhhhhh:   " RESET;
    LOGO[8]  = BLUE "hhhhho. +hhhys++oyyyhhhhh-yhhhhhhhhhhhhhs   " RESET;
    LOGO[9]  = BLUE "hhhhhhs-`/syhhhhyssyyhhhh:-yhhhhhhhhhhhhh   " RESET;
    LOGO[10] = BLUE "hhhhhhs  `:/+ossyyhyyhhhhs -yhhhhhhhhhhhh   " RESET;
    LOGO[11] = BLUE "hhhhhhy/ `syyyssyyyyhhhhhh: :yhhhhhhhhhhs   " RESET;
    LOGO[12] = BLUE ":hhhhhhyo:-/osyhhhhhhhhhhho  ohhhhhhhhhh:   " RESET;
    LOGO[13] = BLUE " sdhhhhhhhyyssyyhhhhhhhhhhh+  +hhhhhhhhs    " RESET;
    LOGO[14] = BLUE " `shhhhhhhhhhhhhhhhhhhhhhy+` .yhhhhhhhh`    " RESET;
    LOGO[15] = BLUE "  +sdhhhhhhhhhhhhhhhhhyo/. `/yhhhhhhhd`     " RESET;
    LOGO[16] = BLUE "   `:shhhhhhhhhh+---..``.:+yyhhhhhhh:       " RESET;
    LOGO[17] = BLUE "     `:mdhhhhhh/.syssyyyyhhhhhhhd:`         " RESET;
    LOGO[18] = BLUE "        `+smdhhh+shhhhhhhhhhhhdm`           " RESET;
    LOGO[19] = BLUE "           `sNmdddhhhhhhhddm-`              " RESET;

    LOGO_SMALL[0] = BLUE "    _____   " RESET;
    LOGO_SMALL[1] = BLUE "   /   _ \\  " RESET;
    LOGO_SMALL[2] = BLUE "  /\\\\_|_\\ \\ " RESET;
    LOGO_SMALL[3] = BLUE " | |   \\   |" RESET;
    LOGO_SMALL[4] = BLUE "  \\  __/  / " RESET;
    LOGO_SMALL[5] = BLUE "   \\_____/  " RESET;
    for (int i = 6; i < minsize; i++) {
      LOGO_SMALL[i]  = BLUE "            " RESET;
    }
  } else if (strncmp((char *)logoname, "manjaro", strlen("manjaro")) == 0) {
    color = GREEN;
    titlecolor = GREEN;
    logosize = 14;

    LOGO[0]  = GREEN "██████████████████  ████████  " RESET;
    LOGO[1]  = GREEN "██████████████████  ████████  " RESET;
    LOGO[2]  = GREEN "██████████████████  ████████  " RESET;
    LOGO[3]  = GREEN "██████████████████  ████████  " RESET;
    LOGO[4]  = GREEN "████████            ████████  " RESET;
    LOGO[5]  = GREEN "████████  ████████  ████████  " RESET;
    LOGO[6]  = GREEN "████████  ████████  ████████  " RESET;
    LOGO[7]  = GREEN "████████  ████████  ████████  " RESET;
    LOGO[8]  = GREEN "████████  ████████  ████████  " RESET;
    LOGO[9]  = GREEN "████████  ████████  ████████  " RESET;
    LOGO[10] = GREEN "████████  ████████  ████████  " RESET;
    LOGO[11] = GREEN "████████  ████████  ████████  " RESET;
    LOGO[12] = GREEN "████████  ████████  ████████  " RESET;
    LOGO[13] = GREEN "████████  ████████  ████████  " RESET;

    LOGO_SMALL[0] = GREEN "||||||||| |||| " RESET;
    LOGO_SMALL[1] = GREEN "||||||||| |||| " RESET;
    LOGO_SMALL[2] = GREEN "||||      |||| " RESET;
    LOGO_SMALL[3] = GREEN "|||| |||| |||| " RESET;
    LOGO_SMALL[4] = GREEN "|||| |||| |||| " RESET;
    LOGO_SMALL[5] = GREEN "|||| |||| |||| " RESET;
    LOGO_SMALL[6] = GREEN "|||| |||| |||| " RESET;
    for (int i = 7; i < minsize; i++) {
      LOGO_SMALL[i]  = GREEN "               " RESET;
    }
  } else if (strncmp((char *)logoname, "opensuse", strlen("opensuse")) == 0) {
    color = GREEN;
    titlecolor = GREEN;
    logosize = 18;

    LOGO[0]  = WHITE "           .;ldkO0000Okdl;.            " RESET;
    LOGO[1]  = WHITE "       .;d00xl:^''''''^:ok00d;.        " RESET;
    LOGO[2]  = WHITE "     .d00l'                'o00d.      " RESET;
    LOGO[3]  = WHITE "   .d0Kd'  " GREEN "Okxol:;,." WHITE "          :O0d.    " RESET;
    LOGO[4]  = WHITE "  .OK" GREEN "KKK0kOKKKKKKKKKKOxo:," WHITE "      lKO.   " RESET;
    LOGO[5]  = WHITE " ,0K" GREEN "KKKKKKKKKKKKKKK0P^,,,^dx:" WHITE "    ;00,  " RESET;
    LOGO[6]  = WHITE ".OK" GREEN "KKKKKKKKKKKKKKKk'.oOPPb.'0k." WHITE "   cKO. " RESET;
    LOGO[7]  = WHITE ":KK" GREEN "KKKKKKKKKKKKKKK: kKx..dd lKd" WHITE "   'OK: " RESET;
    LOGO[8]  = WHITE "dKK" GREEN "KKKKKKKKKOx0KKKd ^0KKKO' kKKc" WHITE "   dKd " RESET;
    LOGO[9]  = WHITE "dKK" GREEN "KKKKKKKKKK;.;oOKx,..^..;kKKK0." WHITE "  dKd " RESET;
    LOGO[10] = WHITE ":KK" GREEN "KKKKKKKKKK0o;...^cdxxOK0O/^^'" WHITE "  .0K: " RESET;
    LOGO[11] = WHITE " kKK" GREEN "KKKKKKKKKKKKK0x;,,......,;od" WHITE "  lKk  " RESET;
    LOGO[12] = WHITE " '0K" GREEN "KKKKKKKKKKKKKKKKKKKK00KKOo^" WHITE "  c00'  " RESET;
    LOGO[13] = WHITE "  'kK" GREEN "KKOxddxkOO00000Okxoc;''" WHITE "   .dKk'   " RESET;
    LOGO[14] = WHITE "    l0Ko.                    .c00l'    " RESET;
    LOGO[15] = WHITE "     'l0Kk:.              .;xK0l'      " RESET;
    LOGO[16] = WHITE "        'lkK0xl:;,,,,;:ldO0kl'         " RESET;
    LOGO[17] = WHITE "            '^:ldxkkkkxdl:^'           " RESET;

    LOGO_SMALL[0] = GREEN "  _______   " RESET;
    LOGO_SMALL[1] = GREEN "__|   __ \\  " RESET;
    LOGO_SMALL[2] = GREEN "     / .\\ \\ " RESET;
    LOGO_SMALL[3] = GREEN "     \\__/ | " RESET;
    LOGO_SMALL[4] = GREEN "   _______| " RESET;
    LOGO_SMALL[5] = GREEN "   \\_______ " RESET;
    LOGO_SMALL[6] = GREEN "__________/ " RESET;
    for (int i = 7; i < minsize; i++) {
      LOGO_SMALL[i]  = GREEN "            " RESET;
    }
  } else if (
      strncmp((char *)logoname, "postmarketos", strlen("postmarketos")) == 0
    ) {
    color = GREEN;
    titlecolor = GREEN;
    logosize = 18;

    LOGO[0]  = GREEN "                 /\\                    " RESET;
    LOGO[1]  = GREEN "                /  \\                   " RESET;
    LOGO[1]  = GREEN "               /    \\                  " RESET;
    LOGO[2]  = GREEN "              /      \\                 " RESET;
    LOGO[3]  = GREEN "             /        \\                " RESET;
    LOGO[4]  = GREEN "            /          \\               " RESET;
    LOGO[5]  = GREEN "            \\           \\              " RESET;
    LOGO[6]  = GREEN "          /\\ \\____       \\             " RESET;
    LOGO[7]  = GREEN "         /  \\____ \\       \\            " RESET;
    LOGO[8]  = GREEN "        /       /  \\       \\           " RESET;
    LOGO[9]  = GREEN "       /       /    \\    ___\\          " RESET;
    LOGO[10] = GREEN "      /       /      \\  / ____         " RESET;
    LOGO[11] = GREEN "     /       /        \\/ /    \\        " RESET;
    LOGO[12] = GREEN "    /       / __________/      \\       " RESET;
    LOGO[13] = GREEN "   /        \\ \\                 \\      " RESET;
    LOGO[14] = GREEN "  /          \\ \\                 \\     " RESET;
    LOGO[15] = GREEN " /           / /                  \\    " RESET;
    LOGO[16] = GREEN "/___________/ /____________________\\   " RESET;
    LOGO[17] = GREEN "                                       " RESET;

    LOGO_SMALL[0] = GREEN "        /\\          " RESET;
    LOGO_SMALL[1] = GREEN "       /  \\         " RESET;
    LOGO_SMALL[2] = GREEN "      /    \\        " RESET;
    LOGO_SMALL[3] = GREEN "      \\__   \\       " RESET;
    LOGO_SMALL[4] = GREEN "    /\\__ \\  _\\      " RESET;
    LOGO_SMALL[5] = GREEN "   /   /  \\/ __     " RESET;
    LOGO_SMALL[6] = GREEN "  /   / ____/  \\    " RESET;
    LOGO_SMALL[7] = GREEN " /    \\ \\       \\   " RESET;
    LOGO_SMALL[8] = GREEN "/_____/ /________\\  " RESET;
    for (int i = 9; i < minsize; i++) {
      LOGO_SMALL[i]  = GREEN "                    " RESET;
    }
  } else if (strncmp((char *)logoname, "redhat", strlen("redhat")) == 0) {
    color = RED;
    titlecolor = RED;
    logosize = 18;

    LOGO[0]  = RED "           .MMM..:MMMMMMM                  " RESET;
    LOGO[1]  = RED "          MMMMMMMMMMMMMMMMMM               " RESET;
    LOGO[2]  = RED "          MMMMMMMMMMMMMMMMMMMM.            " RESET;
    LOGO[3]  = RED "         MMMMMMMMMMMMMMMMMMMMMM            " RESET;
    LOGO[4]  = RED "        ,MMMMMMMMMMMMMMMMMMMMMM:           " RESET;
    LOGO[5]  = RED "        MMMMMMMMMMMMMMMMMMMMMMMM           " RESET;
    LOGO[6]  = RED "  .MMMM'  MMMMMMMMMMMMMMMMMMMMMM           " RESET;
    LOGO[7]  = RED " MMMMMM    `MMMMMMMMMMMMMMMMMMMM.          " RESET;
    LOGO[8]  = RED "MMMMMMMM      MMMMMMMMMMMMMMMMMM .         " RESET;
    LOGO[9]  = RED "MMMMMMMMM.       `MMMMMMMMMMMMM' MM.       " RESET;
    LOGO[10] = RED "MMMMMMMMMMM.                     MMMM      " RESET;
    LOGO[11] = RED "`MMMMMMMMMMMMM.                 ,MMMMM.    " RESET;
    LOGO[12] = RED " `MMMMMMMMMMMMMMMMM.          ,MMMMMMMM.   " RESET;
    LOGO[13] = RED "    MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM   " RESET;
    LOGO[14] = RED "      MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM:   " RESET;
    LOGO[15] = RED "         MMMMMMMMMMMMMMMMMMMMMMMMMMMMMM    " RESET;
    LOGO[16] = RED "            `MMMMMMMMMMMMMMMMMMMMMMMM:     " RESET;
    LOGO[17] = RED "                ``MMMMMMMMMMMMMMMMM'       " RESET;

    LOGO_SMALL[0] = RED "   /=======\\    " RESET;
    LOGO_SMALL[1] = RED "   |       |    " RESET;
    LOGO_SMALL[2] = RED "   |       |    " RESET;
    LOGO_SMALL[3] = RED "  / \\      \\    " RESET;
    LOGO_SMALL[4] = RED " =   ======+\\   " RESET;
    LOGO_SMALL[5] = RED "/ \\________/ \\  " RESET;
    LOGO_SMALL[6] = RED "\\             | " RESET;
    LOGO_SMALL[7] = RED " \\___________/  " RESET;
    for (int i = 8; i < minsize; i++) {
      LOGO_SMALL[i]  = RED "                " RESET;
    }
  } else if (strncmp((char *)logoname, "rocky", strlen("rocky")) == 0) {
    color = GREEN;
    titlecolor = GREEN;
    logosize = 17;

    LOGO[0]  = GREEN "            .-/+oossssoo+/-.               " RESET;
    LOGO[1]  = GREEN "        `:+ssssssssssssssssss+:`           " RESET;
    LOGO[2]  = GREEN "      -+ssssssssssssssssssyyssss+-         " RESET;
    LOGO[3]  = GREEN "    .osssssssssssssssssssssssssssso.       " RESET;
    LOGO[4]  = GREEN "   /ssssssssssssssssssssssssssssssss/      " RESET;
    LOGO[5]  = GREEN "  +ssssssssssssssssssssssssssssssssss+     " RESET;
    LOGO[6]  = GREEN " /ssssssssssssssssssssssssssssssssssss/    " RESET;
    LOGO[7]  = GREEN ".ssssssssssssssssssssssssssssssssssssss.   " RESET;
    LOGO[8]  = GREEN "+ssssssssssssssssssssssssssssssssssssss+   " RESET;
    LOGO[9]  = GREEN ".sssssssssssssssssssss  sssssssssssssss.   " RESET;
    LOGO[10] = GREEN " /sssssssssssssssss  ssss  sssssssssss/    " RESET;
    LOGO[11] = GREEN "  +ssssssssssssss  ssssssss  ssssssss+     " RESET;
    LOGO[12] = GREEN "   /sssssssssss  sssssssssssss  ssss/      " RESET;
    LOGO[13] = GREEN "    .osssssss  sssssssssssssssss  o.       " RESET;
    LOGO[14] = GREEN "      -+sss  sssssssssssssssssss+-         " RESET;
    LOGO[15] = GREEN "        `  ssssssssssssssssss+:`           " RESET;
    LOGO[16] = GREEN "            .-/+oossssoo+/-.               " RESET;

    LOGO_SMALL[0] = GREEN "  _____ " RESET;
    LOGO_SMALL[1] = GREEN " /     \\ " RESET;
    LOGO_SMALL[2] = GREEN " |  /\\ | " RESET;
    LOGO_SMALL[3] = GREEN " | /  \\| " RESET;
    LOGO_SMALL[4] = GREEN " \\/____/ " RESET;
    for (int i = 5; i < minsize; i++) {
      LOGO_SMALL[i]  = GREEN "         " RESET;
    }
  } else if (strncmp((char *)logoname, "ubuntu", strlen("ubuntu")) == 0) {
    color = RED;
    titlecolor = RED;
    logosize = 20;

    LOGO[0]  = RED "            .-/+oossssoo+/-.             " RESET;
    LOGO[1]  = RED "        `:+ssssssssssssssssss+:`         " RESET;
    LOGO[2]  = RED "      -+ssssssssssssssssssyyssss+-       " RESET;
    LOGO[3]  = RED "    .ossssssssssssssssss" WHITE "dMMMNy" RED "sssso.     " RESET;
    LOGO[4]  = RED "   /sssssssssss" WHITE "hdmmNNmmyNMMMMh" RED "ssssss/    " RESET;
    LOGO[5]  = RED "  +sssssssss" WHITE "hm" RED "yd" WHITE "MMMMMMMNddddy" RED "ssssssss+   " RESET;
    LOGO[6]  = RED " /ssssssss" WHITE "hNMMM" RED "yh" WHITE "hyyyyhmNMMMNh" RED "ssssssss/  " RESET;
    LOGO[7]  = RED ".ssssssss" WHITE "dMMMNh" RED "ssssssssss" WHITE "hNMMMd" RED "ssssssss. " RESET;
    LOGO[8]  = RED "+ssss" WHITE "hhhyNMMNy" RED "ssssssssssss" WHITE "yNMMMy" RED "sssssss+ " RESET;
    LOGO[9]  = RED "oss" WHITE "yNMMMNyMMh" RED "ssssssssssssss" WHITE "hmmmh" RED "ssssssso " RESET;
    LOGO[10] = RED "oss" WHITE "yNMMMNyMMh" RED "sssssssssssssshmmmhssssssso " RESET;
    LOGO[11] = RED "+ssss" WHITE "hhhyNMMNy" RED "ssssssssssss" WHITE "yNMMMy" RED "sssssss+ " RESET;
    LOGO[12] = RED ".ssssssss" WHITE "dMMMNh" RED "ssssssssss" WHITE "hNMMMd" RED "ssssssss. " RESET;
    LOGO[13] = RED " /ssssssss" WHITE "hNMMM" RED "yh" WHITE "hyyyyhdNMMMNh" RED "ssssssss/  " RESET;
    LOGO[14] = RED "  +sssssssss" WHITE "dm" RED "yd" WHITE "MMMMMMMMddddy" RED "ssssssss+   " RESET;
    LOGO[15] = RED "   /sssssssssss" WHITE "hdmNNNNmyNMMMMh" RED "ssssss/    " RESET;
    LOGO[16] = RED "    .ossssssssssssssssss" WHITE "dMMMNy" RED "sssso.     " RESET;
    LOGO[17] = RED "      -+sssssssssssssssss" WHITE "yyy" RED "ssss+-       " RESET;
    LOGO[18] = RED "        `:+ssssssssssssssssss+:`         " RESET;
    LOGO[19] = RED "            .-/+oossssoo+/-.             " RESET;

    LOGO_SMALL[0] = RED "         _  " RESET;
    LOGO_SMALL[1] = RED "     ---(_) " RESET;
    LOGO_SMALL[2] = RED " _/  ---  \\ " RESET;
    LOGO_SMALL[3] = RED "(_) |   |   " RESET;
    LOGO_SMALL[4] = RED "  \\  --- _/ " RESET;
    LOGO_SMALL[5] = RED "     ---(_) " RESET;
    for (int i = 6; i < minsize; i++) {
      LOGO_SMALL[i]  = RED "            " RESET;
    }
  } else if (strncmp((char *)logoname, "void", strlen("void")) == 0) {
    color = WHITE;
    titlecolor = GREEN;
    logosize = 19;

    LOGO[0]  = GREEN "                __.;=====;.__                    " RESET;
    LOGO[1]  = GREEN "            _.=+==++=++=+=+===;.                 " RESET;
    LOGO[2]  = GREEN "             -=+++=+===+=+=+++++=_               " RESET;
    LOGO[3]  = GREEN "        .     -=:``     `--==+=++==.             " RESET;
    LOGO[4]  = GREEN "       _vi,    `            --+=++++:            " RESET;
    LOGO[5]  = GREEN "      .uvnvi.       _._       -==+==+.           " RESET;
    LOGO[6]  = GREEN "     .vvnvnI`    .;==|==;.     :|=||=|.          " RESET;
    LOGO[7]  = GREY  "+QmQQm" GREEN "pvvnv; " GREY "_yYsyQQWUUQQQm #QmQ#" GREEN ":" GREY "QQQWUV$QQm.    " RESET;
    LOGO[8]  = GREY  " -QQWQW" GREEN "pvvo" GREY "wZ?.wQQQE" GREEN "==<" GREY "!QWWQ/QWQW.QQWW" GREEN "(: " GREY "jQWQE   " RESET;
    LOGO[9]  = GREY  "  -$QQQQmmU'  jQQQ@" GREEN "+=<" GREY "QWQQ)mQQQ.mQQQC" GREEN "+;" GREY "jWQQ@'    " RESET;
    LOGO[10] = GREY  "   -$WQ8Y" GREEN "nI:   " GREY "QWQQwgQQWV" GREEN"`" GREY "mWQQ.jQWQQgyyWW@!      " RESET;
    LOGO[11] = GREEN "     -1vvnvv.     `~+++`        ++|+++           " RESET;
    LOGO[12] = GREEN "      +vnvnnv,                 `-|===            " RESET;
    LOGO[13] = GREEN "       +vnvnvns.           .      :=-            " RESET;
    LOGO[14] = GREEN "        -Invnvvnsi..___..=sv=.     `             " RESET;
    LOGO[15] = GREEN "          +Invnvnvnnnnnnnnvvnn;.                 " RESET;
    LOGO[16] = GREEN "            ~|Invnvnvvnvvvnnv}+`                 " RESET;
    LOGO[17] = GREEN "               -~|{*l}*|~                        " RESET;
    LOGO[18] = GREEN "                                                 " RESET;

    LOGO_SMALL[0] = GREEN "    _______    " RESET;
    LOGO_SMALL[1] = GREEN " _ \\______ -   " RESET;
    LOGO_SMALL[2] = GREEN "| \\  ___  \\ |  " RESET;
    LOGO_SMALL[3] = GREEN "| | /   \\ | |  " RESET;
    LOGO_SMALL[4] = GREEN "| | \\___/ | |  " RESET;
    LOGO_SMALL[5] = GREEN "| \\______ \\_|  " RESET;
    LOGO_SMALL[6] = GREEN " -_______\\     " RESET;
    for (int i = 7; i < minsize; i++) {
      LOGO_SMALL[i]  = GREEN "               " RESET;
    }
  } else if (strncmp((char *)logoname, "xubuntu", strlen("xubuntu")) == 0) {
    color = BLUE;
    titlecolor = BLUE;
    logosize = 20;

    LOGO[0]  = BLUE "           `-/osyhddddhyso/-`              " RESET;
    LOGO[1]  = BLUE "        .+yddddddddddddddddddy+.           " RESET;
    LOGO[2]  = BLUE "      :yddddddddddddddddddddddddy:         " RESET;
    LOGO[3]  = BLUE "    -yddddddddddddddddddddhdddddddy-       " RESET;
    LOGO[4]  = BLUE "   odddddddddddyshdddddddh`dddd+ydddo      " RESET;
    LOGO[5]  = BLUE " `yddddddhshdd-   ydddddd+`ddh.:dddddy`    " RESET;
    LOGO[6]  = BLUE " sddddddy   /d.   :dddddd-:dy`-ddddddds    " RESET;
    LOGO[7]  = BLUE ":ddddddds    /+   .dddddd`yy`:ddddddddd:   " RESET;
    LOGO[8]  = BLUE "sdddddddd`    .    .-:/+ssdyodddddddddds   " RESET;
    LOGO[9]  = BLUE "ddddddddy                  `:ohddddddddd   " RESET;
    LOGO[10] = BLUE "dddddddd.                      +dddddddd   " RESET;
    LOGO[11] = BLUE "sddddddy                        ydddddds   " RESET;
    LOGO[12] = BLUE ":dddddd+                      .oddddddd:   " RESET;
    LOGO[13] = BLUE " sdddddo                   ./ydddddddds    " RESET;
    LOGO[14] = BLUE " `yddddd.              `:ohddddddddddy`    " RESET;
    LOGO[15] = BLUE "   oddddh/`      `.:+shdddddddddddddo      " RESET;
    LOGO[16] = BLUE "    -ydddddhyssyhdddddddddddddddddy-       " RESET;
    LOGO[17] = BLUE "      :yddddddddddddddddddddddddy:         " RESET;
    LOGO[18] = BLUE "        .+yddddddddddddddddddy+.           " RESET;
    LOGO[19] = BLUE "           `-/osyhddddhyso/-`              " RESET;

    LOGO_SMALL[0] = BLUE "    _____   " RESET;
    LOGO_SMALL[1] = BLUE "   /     \\  " RESET;
    LOGO_SMALL[2] = BLUE "  / ||_ / \\ " RESET;
    LOGO_SMALL[3] = BLUE " | |   \\   |" RESET;
    LOGO_SMALL[4] = BLUE "  \\ \\__/  / " RESET;
    LOGO_SMALL[5] = BLUE "   \\_____/  " RESET;
    for (int i = 6; i < minsize; i++) {
      LOGO_SMALL[i]  = BLUE "            " RESET;
    }
  } else {
    color = WHITE;
    titlecolor = WHITE;
    logosize = 13;

    LOGO[0]  = GREY   "        #####           " RESET;
    LOGO[1]  = GREY   "       #######          " RESET;
    LOGO[2]  = GREY   "       ##" WHITE "O" GREY "#" WHITE "O" GREY "##          " RESET;
    LOGO[3]  = GREY   "       #" YELLOW "#####" GREY "#          " RESET;
    LOGO[4]  = GREY   "     ##" WHITE "##" YELLOW "###" WHITE "##" GREY "##        " RESET;
    LOGO[5]  = GREY   "    #" WHITE "##########" GREY "##       " RESET;
    LOGO[6]  = GREY   "   #" WHITE "############" GREY "##      " RESET;
    LOGO[7]  = GREY   "   #" WHITE "############" GREY "###     " RESET;
    LOGO[8]  = YELLOW "  ##" GREY "#" WHITE "###########" GREY "##" YELLOW "#     " RESET;
    LOGO[9]  = YELLOW "######" YELLOW "#" GREY "#" WHITE "######" GREY "#" YELLOW "######   " RESET;
    LOGO[10] = YELLOW "#######" GREY "#" WHITE "#####" GREY "#" YELLOW "#######   " RESET;
    LOGO[11] = YELLOW "  #####" GREY "#######" YELLOW "#####     " RESET;
    LOGO[12] = GREY   "                        " RESET;

    LOGO_SMALL[0] = GREY   "   ___     " RESET;
    LOGO_SMALL[1] = GREY   "  /   \\    " RESET;
    LOGO_SMALL[2] = GREY   "  |" WHITE "0 0" GREY "|    " RESET;
    LOGO_SMALL[3] = GREY   "  | " YELLOW "v" GREY " |    " RESET;
    LOGO_SMALL[4] = GREY   " / " WHITE "/ \\" GREY " \\   " RESET;
    LOGO_SMALL[5] = GREY   " | " WHITE "\\_/" GREY " |   " RESET;
    LOGO_SMALL[6] = YELLOW "/ " GREY "_____" YELLOW " \\  " RESET;
    LOGO_SMALL[7] = YELLOW "\\/     \\/  " RESET;
    for (int i = 8; i < minsize; i++) {
      LOGO_SMALL[i]  = GREY "           " RESET;
    }
  }
}
#endif
