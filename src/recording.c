#if defined(__OpenBSD__)
#include "recording.h"
#include "common.h"

const char *display_recording_audio() {
  return run_command_s("sysctl -n kern.audio.record");
}

const char *display_recording_video() {
  return run_command_s("sysctl -n kern.video.record");
}
#endif
