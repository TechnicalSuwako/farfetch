#include "linux_def.h"

#include <string.h>

void getDistro(const char *distroname) {
  if (strncmp((char *)distroname, "alpine", strlen("alpine")) == 0) {
#undef DISTRO
#undef COLOR
#undef TITLECOLOR
#define DISTRO DISTRO_ALPINE
#define COLOR MAGENTA
#define TITLECOLOR BLUE
  } else if (strncmp((char *)distroname, "artix", strlen("artix")) == 0) {
#undef DISTRO
#undef COLOR
#undef TITLECOLOR
#define DISTRO DISTRO_ARCH
#define COLOR CYAN
#define TITLECOLOR CYAN
  } else if (strncmp((char *)distroname, "arch", strlen("arch")) == 0) {
#undef DISTRO
#undef COLOR
#undef TITLECOLOR
#define DISTRO DISTRO_ARTIX
#define COLOR CYAN
#define TITLECOLOR CYAN
  } else if (strncmp((char *)distroname, "crux", strlen("crux")) == 0) {
#undef DISTRO
#undef COLOR
#undef TITLECOLOR
#define DISTRO DISTRO_CRUX
#define COLOR MAGENTA
#define TITLECOLOR BLUE
  } else if (strncmp((char *)distroname, "debian", strlen("debian")) == 0) {
#undef DISTRO
#undef COLOR
#undef TITLECOLOR
#define DISTRO DISTRO_DEBIAN
#define COLOR RED
#define TITLECOLOR RED
  } else if (strncmp((char *)distroname, "devuan", strlen("devuan")) == 0) {
#undef DISTRO
#undef COLOR
#undef TITLECOLOR
#define DISTRO DISTRO_DEVUAN
#define COLOR MAGENTA
#define TITLECOLOR MAGENTA
  } else if (strncmp((char *)distroname, "gentoo", strlen("gentoo")) == 0) {
#undef DISTRO
#undef COLOR
#undef TITLECOLOR
#define DISTRO DISTRO_GENTOO
#define COLOR MAGENTA
#define TITLECOLOR MAGENTA
  } else if (
      strncmp((char *)distroname,
        "postmarketos",
        strlen("postmarketos")
      ) == 0
    ) {
#undef DISTRO
#undef COLOR
#undef TITLECOLOR
#define DISTRO DISTRO_POSTMARKETOS
#define COLOR GREEN
#define TITLECOLOR GREEN
  } else if (strncmp((char *)distroname, "void", strlen("void")) == 0) {
#undef DISTRO
#undef COLOR
#undef TITLECOLOR
#define DISTRO DISTRO_VOID
#define COLOR WHITE
#define TITLECOLOR GREEN
  }
}
