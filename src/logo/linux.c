#if defined(__linux__)
#include "linux.h"

#include <stdio.h>
#include <string.h>

char *LOGO[23];
char *LOGO_SMALL[23];
const char *color;
const char *titlecolor;

void getDistro(const char *distroname) {
  if (strncmp((char *)distroname, "alpine", strlen("alpine")) == 0) {
    color = MAGENTA;
    titlecolor = BLUE;

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
    for (int i = 6; i < MIN_SIZE; i++) {
      LOGO_SMALL[i]  = BLUE "              " RESET;
    }
  } else if (strncmp((char *)distroname, "artix", strlen("artix")) == 0) {
    color = CYAN;
    titlecolor = CYAN;

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
    for (int i = 7; i < MIN_SIZE; i++) {
      LOGO_SMALL[i]  = CYAN "                " RESET;
    }
  } else if (strncmp((char *)distroname, "arch", strlen("arch")) == 0) {
    color = CYAN;
    titlecolor = CYAN;

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
    for (int i = 7; i < MIN_SIZE; i++) {
      LOGO_SMALL[i]  = CYAN "                " RESET;
    }
  } else if (strncmp((char *)distroname, "crux", strlen("crux")) == 0) {
    color = MAGENTA;
    titlecolor = BLUE;

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
    for (int i = 7; i < MIN_SIZE; i++) {
      LOGO_SMALL[i]  = BLUE "                 " RESET;
    }
  } else if (strncmp((char *)distroname, "debian", strlen("debian")) == 0) {
    color = RED;
    titlecolor = RED;

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
    for (int i = 6; i < MIN_SIZE; i++) {
      LOGO_SMALL[i]  = RED "           " RESET;
    }
  } else if (strncmp((char *)distroname, "devuan", strlen("devuan")) == 0) {
    color = MAGENTA;
    titlecolor = MAGENTA;

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
    for (int i = 3; i < MIN_SIZE; i++) {
      LOGO_SMALL[i]  = MAGENTA "     " RESET;
    }
  } else if (strncmp((char *)distroname, "gentoo", strlen("gentoo")) == 0) {
    color = MAGENTA;
    titlecolor = MAGENTA;

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
    for (int i = 7; i < MIN_SIZE; i++) {
      LOGO_SMALL[i]  = MAGENTA "             " RESET;
    }
  } else if (
      strncmp((char *)distroname,
        "postmarketos",
        strlen("postmarketos")
      ) == 0
    ) {
    color = GREEN;
    titlecolor = GREEN;

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
    for (int i = 9; i < MIN_SIZE; i++) {
      LOGO_SMALL[i]  = GREEN "                    " RESET;
    }
  } else if (strncmp((char *)distroname, "void", strlen("void")) == 0) {
    color = WHITE;
    titlecolor = GREEN;

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
    for (int i = 7; i < MIN_SIZE; i++) {
      LOGO_SMALL[i]  = GREEN "               " RESET;
    }
  } else {
    color = WHITE;
    titlecolor = WHITE;

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
    for (int i = 8; i < MIN_SIZE; i++) {
      LOGO_SMALL[i]  = GREY "           " RESET;
    }
  }
}
#endif
