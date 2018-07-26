#include <stdlib.h>


#include "audio_recorder.h"
#include "playback.h"


int main() {
    AudioRecorder_init();
    Playback_init();

    unsigned long frameSize = AudioRecorder_getFrameSize();

    while (1) {
        double *data = AudioRecorder_getNextAudioReading();
        if (data != NULL) {
            Playback_playWithDelay(data, frameSize, 100);
        }
    }

    AudioRecorder_cleanup();

    return 0;
}