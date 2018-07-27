#include <stdio.h>
#include <unistd.h>
#include "led.h"
#include "display.h"
#include "game.h"
#include "input.h"
#include "processFrame.h"
#include <stdlib.h>
// #include <unistd.h>
#include <time.h>

#include "audio_recorder.h"
#include "playback.h"


int main() {
    int result = LED_init();
    if (result > 0)
        return 0;
    result = Display_init(300);
    if (result > 0)
        return 0;
    Input_init();
    Game_init();
    ProcessFrame_init();
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

    LED_cleanup();
    Display_cleanup();
    Input_cleanup();
    Game_cleanup();
    ProcessFrame_cleanup();
    AudioRecorder_cleanup();
    Playback_cleanup();
    
    return 0;
}