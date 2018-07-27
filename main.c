#include <stdio.h>
#include <unistd.h>
#include "led.h"
#include "display.h"
#include "game.h"
#include "processFrame.h"
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
    Playback_init();

    LED_cleanup();
    Display_cleanup();
    Input_cleanup();
    Game_cleanup();
    ProcessFrame_cleanup();
    Playback_cleanup();
    
    return 0;
}
