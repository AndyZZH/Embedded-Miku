#include <stdlib.h>
// #include <unistd.h>
#include <time.h>

#include "audio_recorder.h"
#include "playback.h"


int main() {
    AudioRecorder_init();
    Playback_init();

    unsigned long frameSize = AudioRecorder_getFrameSize();

    struct timespec reqtime;
    reqtime.tv_sec=0;
    reqtime.tv_nsec = 50 * 1000;
    while (1) {
        double *data = AudioRecorder_getNextAudioReading();
        if (data != NULL) {
            Playback_playWithDelay(data, frameSize, 1000);
        }
        nanosleep(&reqtime, NULL);
    }

    AudioRecorder_cleanup();

    return 0;
}