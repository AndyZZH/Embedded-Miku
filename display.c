#include <pthread.h>
#include <stdio.h>
#include <time.h>
#include <stdbool.h>
#include "game.h"
#include "led.h"

#define COMPONENT_MAX_NUM 16 
#define DISPLAY_WIDTH 32 
#define DISPLAY_HEIGHT 16
#define SLOT_SIZE 8
#define SLOT_NUM 4

#define MAX_LIFE 8

/*
 *   button:
 *      - 0 : A (Green)
 *      - 1 : B (Red)
 *      - 2 : X (Blue)
 *      - 3 : Y (Yellow)
 */
typedef struct {
    int slot;
    int height;
} component; 

static int color_mapping[SLOT_NUM] = { 2, 1, 4, 3 };  //index : contoroller button number & SLOT number

static pthread_t displayThread;
static pthread_mutex_t currentComponentLock = PTHREAD_MUTEX_INITIALIZER;
//static pthread_mutex_t lifeLock = PTHREAD_MUTEX_INITIALIZER;
static bool running;
static long totalDelay;
static int goneLife;

static component currentComponent[COMPONENT_MAX_NUM];

static void* displayLoop (void *);
static void displayLife(void);

int Display_init (int delayTimeInMs, void (*f) (int))
{
    for (int i = 0; i < COMPONENT_MAX_NUM; i++){
        currentComponent[i].height = -1;
        currentComponent[i].slot = -1;
    } 
    running = true;
    totalDelay = delayTimeInMs *1000000 ; 
    goneLife = 0;

    int threadCreateResult = pthread_create (&displayThread, NULL, displayLoop, NULL);
    return threadCreateResult;
}

// functino for thread which will keep checking currentComponent and display them
static void* displayLoop (void* empty)
{
    printf ( "start displaying loop \n");

    struct timespec reqtime;
    reqtime.tv_sec = totalDelay / 1000000000; 
    reqtime.tv_nsec = totalDelay % 1000000000; 

    int width = DISPLAY_WIDTH / SLOT_NUM;
    int currentHeight;
    int slot;
    while (running) {
        LED_clean_display();
        
        for (int i = 0; i < COMPONENT_MAX_NUM && goneLife < MAX_LIFE; i++){
            pthread_mutex_lock (&currentComponentLock);
            {
                currentHeight = currentComponent[i].height; 
                slot = currentComponent[i].slot;
            }
            pthread_mutex_unlock (&currentComponentLock);

            if ( currentHeight >= DISPLAY_HEIGHT){
                currentComponent[i].height = -1;
			    Game_checkTimeout(slot);
            }

            if ( currentHeight >=0 ){
                LED_display_rectangle(slot*SLOT_SIZE + goneLife/2, currentHeight, slot*SLOT_SIZE + width-1 - goneLife/2, (currentHeight+1) % DISPLAY_HEIGHT, color_mapping[slot] );
                currentComponent[i].height++;
                if (currentComponent[i].height >= DISPLAY_HEIGHT){
                    currentComponent[i].height = -1;
			        Game_checkTimeout(slot);
                } 
            }
        } 
        displayLife();
        nanosleep(&reqtime, NULL); 
    }
    printf ( "stop displaying loop \n");
    return NULL;
}

static void displayLife (void)
{
    for (int i = 0; i < 4; i++){
        LED_display_rectangle(i*SLOT_SIZE + goneLife/2, DISPLAY_HEIGHT-1, (i+1)*SLOT_SIZE - (1 + goneLife/2), DISPLAY_HEIGHT-1, color_mapping[i]);
    }
}

void Display_cleanup(void)
{
    running = false;
    pthread_join (displayThread, NULL);
    LED_cleanup();
}

void Display_generateComponent (int button)
{
    if (button > 3 || button < 0)
        return;
    pthread_mutex_lock (&currentComponentLock);
    {
        for (int i = 0; i < COMPONENT_MAX_NUM; i++){
            if (currentComponent[i].height == -1){
                currentComponent[i].height = 0;
                currentComponent[i].slot = button;
                break;
            }
        }
    }
    pthread_mutex_unlock (&currentComponentLock);
    return;
}

void Display_decreaseLife(int life)
{
    if (life >= MAX_LIFE){
        goneLife = 0;
        return;
    }
    if (goneLife <= MAX_LIFE -1)
    {
    	goneLife = MAX_LIFE - life;
    }
}

void Display_rechargeLife(int life)
{
    if (life >= MAX_LIFE){
        goneLife = 0;
        return;
    }
    if (life <= 0) {
        goneLife = MAX_LIFE; 
        return;
    }
    goneLife = MAX_LIFE - life;
    pthread_mutex_lock (&currentComponentLock);
    {
        for (int i = 0; i < COMPONENT_MAX_NUM; i++){
            currentComponent[i].height = -1;
            currentComponent[i].slot = -1;
        }
    }
    pthread_mutex_unlock (&currentComponentLock);

}
