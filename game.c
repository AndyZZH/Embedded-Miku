#include "game.h"
#include "util.h"
#include "display.h"
#include "input.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <stdbool.h>
#include <time.h>

#define DEFAULT_DELAY_TIMEms 1000 // default delay time is 1s
#define REACT_TIMEms 250 //default react time +- 0.25s 
#define DEFAULT_SCORE 0 //default react time +- 0.25s 

// prototype

static int score = DEFAULT_SCORE;
static long long delayTime = DEFAULT_DELAY_TIMEms;
static long long beatQueue[XBOX_NUM_TYPE];


void Game_init(void){
    srand(time(NULL));
    for (int i = 0; i < XBOX_NUM_TYPE; i++){
        beatQueue[i] = 0;
    }
}

void Game_cleanup(void){
    printf("[game] game cleanup starting");
    printf("[game] game cleanup finished");
}

/*
 * Function:  Game_EnqueueBeat()
 * --------------------
 * Function to enqueue beat in BeatSlot
 * - if there is slot is overdue, replace
 * - if no slot available, skip
 * 
 * Randomly choice start point at BeatSlot
 * 
 * 
 *  returns: void
 */
void Game_EnqueueBeat(void){
    int currentSlot = rand() % XBOX_NUM_TYPE;
    long long currentTime = Util_getCurrentTime();
    for (int i =0; i < XBOX_NUM_TYPE; i++){
        if (currentSlot == XBOX_NUM_TYPE) currentSlot = 0; // start all over from left hand side
        if (beatQueue[currentSlot] + delayTime > currentTime){
            // overdue, see it as an empty slot
            beatQueue[currentSlot] = currentTime;
            // call led dropping
            Display_generateComponent(currentSlot);
            break;
        }
    }
}

long long Game_getDelayTime(void){
    return delayTime;
}

/*
 * Function:  Game_checkBeat()
 * --------------------
 * Function to get the button_id, genereate button struct {timestamp, button_id}
 * Compare {timestamp, button_id} with BeatSlot
 * If valid: score++, set timestamp in slot{button_id} 0 (make it overdue)
 * otherwise do nothing
 * 
 *  returns: void
 */
void Game_checkBeat(int button_id){
    long long currentTime = Util_getCurrentTime();
    long long timeInSlot = beatQueue[button_id];
    if (timeInSlot + delayTime - currentTime < REACT_TIMEms && timeInSlot + delayTime - currentTime > -REACT_TIMEms ){
        // within time interval, score++
        score ++;
        beatQueue[button_id] = 0;
    }
}

int Game_getScore(){
    return score;
}