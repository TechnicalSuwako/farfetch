#include "packages.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if defined(__linux__)
#include "distro.h"

/*const char *distroname;*/
#endif

const char *run_package_command(const char *command) {
  char buf[64];
  char *out = NULL;
  size_t outsize = 0;

  FILE *p = popen(command, "r");
  if (!p) {
    fprintf(stderr, "パッケージコマンドを実効に失敗: %s", command);
    return NULL;
  }

  while (fgets(buf, sizeof(buf), p) != NULL) {
    buf[strcspn(buf, "\n")] = '\0';

    size_t len = strlen(buf);
    char *nout = realloc(out, outsize + len + 1);
    if (nout == NULL) {
      perror("メモリの役割に失敗");
      free(out);
      pclose(p);
      return NULL;
    }

    out = nout;

    memccpy(out + outsize, buf, sizeof(buf), len);
    outsize += len;
    out[outsize] = '\0';
  }

  pclose(p);

  return out;
}

void display_packages() {
#if defined(__OpenBSD__) || defined(__NetBSD__)
  printf("%s (pkg_info)", run_package_command("pkg_info -a | wc -l | "
         "sed \"s/ //g\""));
#elif defined(__FreeBSD__) || defined(__DragonFly__)
  printf("%s (pkg)", run_package_command("pkg info -a | wc -l | "
         "sed \"s/ //g\""));
#elif defined(__linux__)
  if (strncmp(distroname, "void", strlen("void")) == 0) {
    printf("%s (xbps-query)", run_package_command("xbps-query -l | wc -l | "
           "sed \"s/ //g\""));
  }
#endif
}
