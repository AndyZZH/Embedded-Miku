#include "game.h"
#include "util.h"
#include "display.h"
#include "input.h"
#include "score_display.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <pthread.h>

#define DEFAULT_DELAY_TIMEms 2000 // default delay time is 1s
#define REACT_TIMEms 500 //default react time +- 0.25s
#define DEFAULT_SCORE 0 //default score is 0
#define DEFAULT_LIFE 8 // default chances before player lose
#define RESTART_BTN 6 // the id of button to be clicked to restart the game

// prototype

static int score = DEFAULT_SCORE;
static long long delayTime = DEFAULT_DELAY_TIMEms;
static long long beatQueue[XBOX_NUM_TYPE];
static int life = DEFAULT_LIFE;
static bool timeoutQueue[XBOX_NUM_TYPE];
static bool gameOver = false;
static pthread_mutex_t slot_lock;

static void decrease_life(){
  life--;
  printf("Life left: %d\n", life);
  //call turn off led
  Display_decreaseLife(life);
  if(life == 0){
    //game over
    gameOver = true;
  }
}



void Game_init(void){
    srand(time(NULL));
    score = DEFAULT_SCORE;
    score_setDigit(score);
    life = DEFAULT_LIFE;
    pthread_mutex_lock(&slot_lock);
    for (int i = 0; i < XBOX_NUM_TYPE; i++){
        beatQueue[i] = 0;
        timeoutQueue[i] = false;
    }
    pthread_mutex_unlock(&slot_lock);
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
	if(!gameOver){
      pthread_mutex_lock(&slot_lock);
	    for (int i = 0; i < XBOX_NUM_TYPE; i++){
		      //printf("beatqueue %lld, current time: %lld, delay: %lld\n",beatQueue[currentSlot], currentTime, delayTime );
		        if (currentSlot == XBOX_NUM_TYPE) currentSlot = 0; // start all over from left hand side
            if (beatQueue[currentSlot] + delayTime < currentTime){
		            // overdue, see it as an empty slot
		              beatQueue[currentSlot] = currentTime;
		              timeoutQueue[currentSlot] = true;

		            // call led dropping
		              Display_generateComponent(currentSlot);
		              break;
		         }
		         currentSlot++;
	    }
      pthread_mutex_unlock(&slot_lock);
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
    if(button_id == RESTART_BTN){
	     if(gameOver){
	        Game_init();
	        Display_rechargeLife(DEFAULT_LIFE);
	        gameOver = false;
          printf("Game restarted, life left: %d\n", DEFAULT_LIFE);
	      }
    }
    else if (timeInSlot + delayTime - currentTime < REACT_TIMEms && timeInSlot + delayTime - currentTime > -REACT_TIMEms ){
        // within time interval, score++
        score ++;
        score_setDigit(score);

        pthread_mutex_lock(&slot_lock);
        beatQueue[button_id] = 0;
        timeoutQueue[button_id] = false;
        pthread_mutex_unlock(&slot_lock);
	      printf("The score is %d.\n", score);
    }
    else{
	     decrease_life();
    }
}

/*
 * Function:  Game_checkTimeout()
 * --------------------
 * Function to check if a slot is timeout
 *
 *  returns: void
 */
void Game_checkTimeout(int slot){
  if(timeoutQueue[slot]){
    decrease_life();
  }
}

int Game_getScore(){
    return score;
}
