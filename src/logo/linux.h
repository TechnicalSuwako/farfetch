#ifndef LOGO_LINUX_H
#define LOGO_LINUX_H

#include "../distro.h"

#define GREY    "\e[1;30m"
#define RED     "\e[1;31m"
#define GREEN   "\e[1;32m"
#define YELLOW  "\e[1;33m"
#define BLUE    "\e[1;34m"
#define MAGENTA "\e[1;35m"
#define CYAN    "\e[1;36m"
#define WHITE   "\e[1;37m"
#define RESET   "\e[0m"

#define COLOR WHITE
#define TITLECOLOR WHITE

#define DISTRO_LINUX 0
#define DISTRO_ALPINE 1
#define DISTRO_ARCH 2
#define DISTRO_ARTIX 3
#define DISTRO_CRUX 4
#define DISTRO_DEBIAN 5
#define DISTRO_DEVUAN 6
#define DISTRO_GENTOO 7
#define DISTRO_POSTMARKETOS 8
#define DISTRO_VOID 9

#ifndef DISTRO
#define DISTRO DISTRO_LINUX
#endif

#define COLOR WHITE
#define TITLECOLOR WHITE

#if DISTRO == DISTRO_LINUX
char *LOGO[] = {
GREY   "        #####           " RESET, 
GREY   "       #######          " RESET,
GREY   "       ##" WHITE "O" GREY "#" WHITE "O" GREY "##          " RESET,
GREY   "       #" YELLOW "#####" GREY "#          " RESET,
GREY   "     ##" WHITE "##" YELLOW "###" WHITE "##" GREY "##        " RESET,
GREY   "    #" WHITE "##########" GREY "##       " RESET,
GREY   "   #" WHITE "############" GREY "##      " RESET,
GREY   "   #" WHITE "############" GREY "###     " RESET,
YELLOW "  ##" GREY "#" WHITE "###########" GREY "##" YELLOW "#     " RESET,
YELLOW "######" YELLOW "#" GREY "#" WHITE "######" GREY "#" YELLOW "######   " RESET,
YELLOW "#######" GREY "#" WHITE "#####" GREY "#" YELLOW "#######   " RESET,
YELLOW "  #####" GREY "#######" YELLOW "#####     " RESET,
GREY   "                        " RESET,
GREY   "                        " RESET,
GREY   "                        " RESET,
GREY   "                        " RESET,
GREY   "                        " RESET,
GREY   "                        " RESET
};

char *LOGO_SMALL[] = {
GREY   "   ___     " RESET,
GREY   "  /   \\    " RESET,
GREY   "  |" WHITE "0 0" GREY "|    " RESET,
GREY   "  | " YELLOW "v" GREY " |    " RESET,
GREY   " / " WHITE "/ \\" GREY " \\   " RESET,
GREY   " | " WHITE "\\_/" GREY " |   " RESET,
YELLOW "/ " GREY "_____" YELLOW " \\  " RESET,
YELLOW "\\/     \\/  " RESET
};
#elif DISTRO == DISTRO_ALPINE
// Alpine
char *LOGO[] = {
BLUE "       .hddddddddddddddddddddddh.          " RESET,
BLUE "      :dddddddddddddddddddddddddd:         " RESET,
BLUE "     /dddddddddddddddddddddddddddd/        " RESET,
BLUE "    +dddddddddddddddddddddddddddddd+       " RESET,
BLUE "  `sdddddddddddddddddddddddddddddddds`     " RESET,
BLUE " `ydddddddddddd++hdddddddddddddddddddy`    " RESET,
BLUE ".hddddddddddd+`  `+ddddh:-sdddddddddddh.   " RESET,
BLUE "hdddddddddd+`      `+y:    .sddddddddddh   " RESET,
BLUE "ddddddddh+`   `//`   `.`     -sddddddddd   " RESET,
BLUE "ddddddh+`   `/hddh/`   `:s-    -sddddddd   " RESET,
BLUE "ddddh+`   `/+/dddddh/`   `+s-    -sddddd   " RESET,
BLUE "ddd+`   `/o` :dddddddh/`   `oy-    .yddd   " RESET,
BLUE "hdddyo+ohddyosdddddddddho+oydddy++ohdddh   " RESET,
BLUE ".hddddddddddddddddddddddddddddddddddddh.   " RESET,
BLUE " `yddddddddddddddddddddddddddddddddddy`    " RESET,
BLUE "  `sdddddddddddddddddddddddddddddddds`     " RESET,
BLUE "    +dddddddddddddddddddddddddddddd+       " RESET,
BLUE "     /dddddddddddddddddddddddddddd/        " RESET,
BLUE "      :dddddddddddddddddddddddddd:         " RESET,
BLUE "       .hddddddddddddddddddddddh.          " RESET
};

char *LOGO_SMALL[] = {
BLUE  "   /\\ /\\      " RESET,
BLUE  "  /" WHITE "/ " BLUE "\\  \\     " RESET,
BLUE  " /" WHITE "/   " BLUE "\\  \\    " RESET,
BLUE  "/" WHITE "//    " BLUE "\\  \\   " RESET,
WHITE "//      " BLUE "\\  \\  " RESET,
BLUE  "         \\    " RESET
};
#elif DISTRO == DISTRO_ARCH
// Arch
char *LOGO[] = {
CYAN "                  -`                    " RESET,
CYAN "                 .o+`                   " RESET,
CYAN "                `ooo/                   " RESET,
CYAN "               `+oooo:                  " RESET,
CYAN "              `+oooooo:                 " RESET,
CYAN "              -+oooooo+:                " RESET,
CYAN "            `/:-:++oooo+:               " RESET,
CYAN "           `/++++/+++++++:              " RESET,
CYAN "          `/++++++++++++++:             " RESET,
CYAN "         `/+++ooooooooooooo/`           " RESET,
CYAN "        ./ooosssso++osssssso+`          " RESET,
CYAN "       .oossssso-````/ossssss+`         " RESET,
CYAN "      -osssssso.      :ssssssso.        " RESET,
CYAN "     :osssssss/        osssso+++.       " RESET,
CYAN "    /ossssssss/        +ssssooo/-       " RESET,
CYAN "  `/ossssso+/:-        -:/+osssso+-     " RESET,
CYAN " `+sso+:-`                 `.-/+oso:    " RESET,
CYAN "`++:.                           `-/+/   " RESET,
CYAN ".`                                 `/   " RESET
};

char *LOGO_SMALL[] = {
CYAN  "      /\\        " RESET,
CYAN  "     /  \\       " RESET,
CYAN  "    /\\   \\      " RESET,
WHITE "   /      \\     " RESET,
WHITE "  /   ,,   \\    " RESET,
WHITE " /   |  |  -\\   " RESET,
WHITE "/_-''    ''-_\\  " RESET
};

#elif DISTRO == DISTRO_ARTIX
// Artix
char *LOGO[] = {
CYAN "                   '                     " RESET,
CYAN "                  'o'                    " RESET,
CYAN "                 'ooo'                   " RESET,
CYAN "                'ooxoo'                  " RESET,
CYAN "               'ooxxxoo'                 " RESET,
CYAN "              'oookkxxoo'                " RESET,
CYAN "             'oiioxkkxxoo'               " RESET,
CYAN "            ':;:iiiioxxxoo'              " RESET,
CYAN "               `'.;::ioxxoo'             " RESET,
CYAN "          '-.      `':;jiooo'            " RESET,
CYAN "         'oooio-..     `'i:io'           " RESET,
CYAN "        'ooooxxxxoio:,.   `'-;'          " RESET,
CYAN "       'ooooxxxxxkkxoooIi:-.  `'         " RESET,
CYAN "      'ooooxxxxxkkkkxoiiiiiji'           " RESET,
CYAN "     'ooooxxxxxkxxoiiii:'`     .i'       " RESET,
CYAN "    'ooooxxxxxoi:::'`       .;ioxo'      " RESET,
CYAN "   'ooooxooi::'`         .:iiixkxxo'     " RESET,
CYAN "  'ooooi:'`                `'';ioxxo'    " RESET,
CYAN " 'i:'`                          '':io'   " RESET,
CYAN "'`                                   `'  " RESET
};

char *LOGO_SMALL[] = {
CYAN "      /\\        " RESET,
CYAN "     /  \\       " RESET,
CYAN "    /`'.,\\      " RESET,
CYAN "   /     ',     " RESET,
CYAN "  /      ,`\\    " RESET,
CYAN " /   ,.'`.  \\   " RESET,
CYAN "/.,'`     `'.\\  " RESET
};

#elif DISTRO == DISTRO_CRUX
// CRUX
char *LOGO[] = {
BLUE    "         odddd             " RESET,
BLUE    "      oddxkkkxxdoo         " RESET,
BLUE    "     ddcoddxxxdoool        " RESET,
BLUE    "     xdclodod  olol        " RESET,
BLUE    "     xoc  xdd  olol        " RESET,
BLUE    "     xdc  " MAGENTA "k00" BLUE "Okdlol        " RESET,
BLUE    "     xxd" MAGENTA "kOKKKOkd" BLUE "ldd        " RESET,
BLUE    "     xdco" MAGENTA "xOkdlo" BLUE "dldd        " RESET,
BLUE    "     ddc:cl" MAGENTA "lll" BLUE "oooodo       " RESET,
BLUE    "   odxxdd" WHITE "xkO000kx" BLUE "ooxdo     " RESET,
BLUE    "  oxdd" WHITE "x0NMMMMMMWW0od" BLUE "kkxo   " RESET,
BLUE    " oooxd" WHITE "0WMMMMMMMMMW0o" BLUE "dxkx   " RESET,
BLUE    "docldkXW" WHITE "MMMMMMMWWN" BLUE "Odolco   " RESET,
BLUE    "xx" MAGENTA "dx" BLUE "kxxOKN" WHITE "WMMWN" BLUE "0xdoxo::c   " RESET,
MAGENTA "xOkkO" BLUE "0oo" WHITE "odOW" MAGENTA "WW" BLUE "XkdodOxc:l   " RESET,
MAGENTA "dkkkxkkk" WHITE "OKX" MAGENTA "NNNX0Oxx" BLUE "xc:cd   " RESET,
MAGENTA " odxxdx" WHITE "xllod" MAGENTA "ddooxx" BLUE "dc:ldo   " RESET,
MAGENTA "   lodd" BLUE "dolccc" MAGENTA "ccox" BLUE "xoloo     " RESET
};

char *LOGO_SMALL[] = {
BLUE    "    ___     " RESET,
BLUE    "   (" WHITE ".·" BLUE " |    " RESET,
BLUE    "   (" MAGENTA "<>" BLUE " |    " RESET,
BLUE    "  / " WHITE "__" BLUE "  \\   " RESET,
BLUE    " ( " WHITE "/  \\" BLUE " /|  " RESET,
MAGENTA "_" BLUE "/\\ "WHITE "__)" BLUE "/" MAGENTA "_" BLUE ")  " RESET,
MAGENTA "\\/" BLUE "-____" MAGENTA "\\/   " RESET
};

#elif DISTRO == DISTRO_DEBIAN
// Debian
char *LOGO[] = {
WHITE "       _,met$$$$$gg.          " RESET,
WHITE "    ,g$$$$$$$$$$$$$$$P.       " RESET,
WHITE "  ,g$$P\"     \"\"\"Y$$.\".        " RESET,
WHITE " ,$$P'              `$$$.     " RESET,
WHITE "',$$P       ,ggs.     `$$b:   " RESET,
WHITE "`d$$'     ,$P\"'   " RED "." WHITE "    $$$    " RESET,
WHITE " $$P      d$'     " RED "," WHITE "    $$P    " RESET,
WHITE " $$:      $$.   -    ,d$$'    " RESET,
WHITE " $$;      Y$b._   _,d$P'      " RESET,
WHITE " Y$$.    " RED "`." WHITE "`\"Y$$$$P\"'         " RESET,
WHITE " `$$b      " RED "\"-.__" WHITE "              " RESET,
WHITE "  `Y$$                        " RESET,
WHITE "   `Y$$.                      " RESET,
WHITE "     `$$b.                    " RESET,
WHITE "       `Y$$b.                 " RESET,
WHITE "          `\"Y$b._             " RESET,
WHITE "              `\"\"\"            " RESET,
WHITE "  " RESET
};

char *LOGO_SMALL[] = {
RED "  _____    " RESET,
RED " /  __ \\   " RESET,
RED "|  /    |  " RESET,
RED "|  \\___-   " RESET,
RED "-_         " RESET,
RED "  --_      " RESET
};

#elif DISTRO == DISTRO_DEVUAN
// Devuan
char *LOGO[] = {
MAGENTA "   ..,,;;;::;,..                   " RESET,
MAGENTA "           `':ddd;:,.              " RESET,
MAGENTA "                 `'dPPd:,.         " RESET,
MAGENTA "                     `:b$$b`.      " RESET,
MAGENTA "                        'P$$$d`    " RESET,
MAGENTA "                         .$$$$$`   " RESET,
MAGENTA "                         ;$$$$$P   " RESET,
MAGENTA "                      .:P$$$$$$`   " RESET,
MAGENTA "                  .,:b$$$$$$$;'    " RESET,
MAGENTA "             .,:dP$$$$$$$$b:'      " RESET,
MAGENTA "      .,:;db$$$$$$$$$$Pd'`         " RESET,
MAGENTA " ,db$$$$$$$$$$$$$$b:'`             " RESET,
MAGENTA ":$$$$$$$$$$$$b:'`                  " RESET,
MAGENTA " `$$$$$bd:''`                      " RESET,
MAGENTA "   `'''`                           " RESET,
MAGENTA "                                   " RESET,
MAGENTA "                                   " RESET,
MAGENTA "                                   " RESET
};

char *LOGO_SMALL[] = {
MAGENTA "__   " RESET,
MAGENTA "  \\  " RESET,
MAGENTA " _/  " RESET
};

#elif DISTRO == DISTRO_GENTOO
// Gentoo
char *LOGO[] = {
MAGENTA "         -/oyddmdhs+:.                " RESET,
MAGENTA "     -o" WHITE "dNMMMMMMMMNNmhy+" MAGENTA "-`             " RESET,
MAGENTA "   -y" WHITE "NMMMMMMMMMMMNNNmmdhy" MAGENTA "+-           " RESET,
MAGENTA " `o" WHITE "mMMMMMMMMMMMMNmdmmmmddhhy" MAGENTA "/`        " RESET,
MAGENTA " om" WHITE "MMMMMMMMMMMN" MAGENTA "hhyyyo" WHITE "hmdddhhhd" MAGENTA "o`      " RESET,
MAGENTA ".y" WHITE "dMMMMMMMMMMd" MAGENTA "hs++so/s" WHITE "mdddhhhhdm" MAGENTA "+`    " RESET,
MAGENTA " oy" WHITE "hdmNMMMMMMMN" MAGENTA "dyooy" WHITE "dmddddhhhhyhN" MAGENTA "d.   " RESET,
MAGENTA "  :o" WHITE "yhhdNNMMMMMMMNNNmmdddhhhhhyym" MAGENTA "Mh   " RESET,
MAGENTA "    .:" WHITE "+sydNMMMMMNNNmmmdddhhhhhhmM" MAGENTA "my   " RESET,
MAGENTA "       /m" WHITE "MMMMMMNNNmmmdddhhhhhmMNh" MAGENTA "s:   " RESET,
MAGENTA "    `o" WHITE "NMMMMMMMNNNmmmddddhhdmMNhs" MAGENTA "+`    " RESET,
MAGENTA "  `s" WHITE "NMMMMMMMMNNNmmmdddddmNMmhs" MAGENTA "/.      " RESET,
MAGENTA " /N" WHITE "MMMMMMMMNNNNmmmdddmNMNdso" MAGENTA ":`        " RESET,
MAGENTA "+M" WHITE "MMMMMMNNNNNmmmmdmNMNdso" MAGENTA "/-           " RESET,
MAGENTA "yM" WHITE "MNNNNNNNmmmmmNNMmhs+/" MAGENTA" -`             " RESET,
MAGENTA "/h" WHITE "MMNNNNNNNNMNdhs++/" MAGENTA "-`                " RESET,
MAGENTA "`/" WHITE "ohdmmddhys+++/:" MAGENTA ".`                   " RESET,
MAGENTA "  `-//////:--.                        " RESET
};

char *LOGO_SMALL[] = {
MAGENTA " _-----_     " RESET,
MAGENTA "(       \\    " RESET,
MAGENTA "\\    0   \\   " RESET,
WHITE   " \\        )  " RESET,
WHITE   " /      _/   " RESET,
WHITE   "(     _-     " RESET,
WHITE   "\\____-       " RESET
};

#elif DISTRO == DISTRO_POSTMARKETOS
// postmarketOS
char *LOGO[] = {
GREEN "                 /\\                    " RESET,
GREEN "                /  \\                   " RESET,
GREEN "               /    \\                  " RESET,
GREEN "              /      \\                 " RESET,
GREEN "             /        \\                " RESET,
GREEN "            /          \\               " RESET,
GREEN "            \\           \\              " RESET,
GREEN "          /\\ \\____       \\             " RESET,
GREEN "         /  \\____ \\       \\            " RESET,
GREEN "        /       /  \\       \\           " RESET,
GREEN "       /       /    \\    ___\\          " RESET,
GREEN "      /       /      \\  / ____         " RESET,
GREEN "     /       /        \\/ /    \\        " RESET,
GREEN "    /       / __________/      \\       " RESET,
GREEN "   /        \\ \\                 \\      " RESET,
GREEN "  /          \\ \\                 \\     " RESET,
GREEN " /           / /                  \\    " RESET,
GREEN "/___________/ /____________________\\   " RESET,
GREEN "                                       " RESET
};

char *LOGO_SMALL[] = {
GREEN "        /\\          " RESET,
GREEN "       /  \\         " RESET,
GREEN "      /    \\        " RESET,
GREEN "      \\__   \\       " RESET,
GREEN "    /\\__ \\  _\\      " RESET,
GREEN "   /   /  \\/ __     " RESET,
GREEN "  /   / ____/  \\    " RESET,
GREEN " /    \\ \\       \\   " RESET,
GREEN "/_____/ /________\\  " RESET
};
#elif DISTRO == DISTRO_VOID
// Void
char *LOGO[] = {
GREEN "                __.;=====;.__                    " RESET,
GREEN "            _.=+==++=++=+=+===;.                 " RESET,
GREEN "             -=+++=+===+=+=+++++=_               " RESET,
GREEN "        .     -=:``     `--==+=++==.             " RESET,
GREEN "       _vi,    `            --+=++++:            " RESET,
GREEN "      .uvnvi.       _._       -==+==+.           " RESET,
GREEN "     .vvnvnI`    .;==|==;.     :|=||=|.          " RESET,
GREY  "+QmQQm" GREEN "pvvnv; " GREY "_yYsyQQWUUQQQm #QmQ#" GREEN ":" GREY "QQQWUV$QQm.    " RESET,
GREY  " -QQWQW" GREEN "pvvo" GREY "wZ?.wQQQE" GREEN "==<" GREY "!QWWQ/QWQW.QQWW" GREEN "(: " GREY "jQWQE   " RESET,
GREY  "  -$QQQQmmU'  jQQQ@" GREEN "+=<" GREY "QWQQ)mQQQ.mQQQC" GREEN "+;" GREY "jWQQ@'    " RESET,
GREY  "   -$WQ8Y" GREEN "nI:   " GREY "QWQQwgQQWV" GREEN"`" GREY "mWQQ.jQWQQgyyWW@!      " RESET,
GREEN "     -1vvnvv.     `~+++`        ++|+++           " RESET,
GREEN "      +vnvnnv,                 `-|===            " RESET,
GREEN "       +vnvnvns.           .      :=-            " RESET,
GREEN "        -Invnvvnsi..___..=sv=.     `             " RESET,
GREEN "          +Invnvnvnnnnnnnnvvnn;.                 " RESET,
GREEN "            ~|Invnvnvvnvvvnnv}+`                 " RESET,
GREEN "               -~|{*l}*|~                        " RESET,
GREEN "                                                 " RESET,
GREEN "                                                 " RESET
};

char *LOGO_SMALL[] = {
GREEN "    _______    " RESET,
GREEN " _ \\______ -   " RESET,
GREEN "| \\  ___  \\ |  " RESET,
GREEN "| | /   \\ | |  " RESET,
GREEN "| | \\___/ | |  " RESET,
GREEN "| \\______ \\_|  " RESET,
GREEN " -_______\\     " RESET
};
#endif
#endif
