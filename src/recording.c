#if defined(__OpenBSD__)
#include "recording.h"

#include <stdio.h>
#include <string.h>
#include <unistd.h>

void run_rec_command(const char *command) {
  char buf[128];

  FILE *p = popen(command, "r");
  if (!p) {
    fprintf(stderr, "録画コマンドを実効に失敗: %s", command);
    return;
  }

  while (fgets(buf, sizeof(buf), p) != NULL) {
    buf[strcspn(buf, "\n")] = '\0';
    printf("%s", strncmp(buf, "0", strlen(buf)) ? "off" : "on");
  }

  pclose(p);
}

void display_recording_audio() {
  run_rec_command("sysctl -n kern.audio.record");
}

void display_recording_video() {
  run_rec_command("sysctl -n kern.video.record");
}
#endif
