#include <stdio.h>
#include <unistd.h>
#include "beat.h"
#include "led.h"
#include "display.h"
#include "game.h"
#include "input.h"
#include "score_display.h"
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
    result = Display_init((2000*1000000)/16);
    if (result > 0)
        return 0;
    Input_init();
    Game_init();
    AudioRecorder_init();
    Beat_init();
    ProcessFrame_init();
    score_starter();
    Playback_init();

    volatile int haha = 0;
    while (1) {
        haha++;
        // if (haha > 400000000) exit(1);
    }

    LED_cleanup();
    Display_cleanup();
    Input_cleanup();
    Game_cleanup();
    AudioRecorder_cleanup();
    ProcessFrame_cleanup();
    score_stop();
    Playback_cleanup();
    
    return 0;
}