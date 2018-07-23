#include <pthread.h>
#include <stdbool.h>
#include "led.h"

#define COMPONNET_MAX_NUM 20 
#define DISPLAY_WIDTH 16
#define COLOR_MAPPING_SIZE 4

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

static int color_mapping[COLOR_MAPPING_SIZE] = { 2, 1, 4, 3 }  //index : contoroller button number & SLOT number

static pthread_t displayThread;
static pthread_mutex_t currentComponentLock = PTHREAD_MUTEX_INITIALIZER;
static bool running;

static component currentComponent[COMPONENT_MAX_NUM];

static void* displayLoop (void *);

int Display_init (void)
{
    if ( LED_init() )
        return 1;
    
    for (int i = 0; i < COMPONNET_MAX_NUM; i++){
        currentComponent[i].height = -1;
        currentComponent[i].slot = -1;
    } 

    running = true;
    int threadCreateResult = pthread_create (&displayThread, NULL, displayLoop, NULL);
    return threadCreateResult;
}

// functino for thread which will keep checking currentComponent and display them
static void* displayLoop (void* empty)
{
    printf ( "start displaying loop \n");
    int i;
    int width = DISPLAY_WIDTH / COMPONENT_NUM;
    int currentHeight;
    int slot;
    while (running) {
        for ( i = 0; i < COMPONENT_MAX_NUM; i++){
            pthread_mutex_lock (*currentComponentLock);
            {
                currentHeight = currentComponent[i].height; 
                slot = currentComponent[i].slot;
            }
            pthread_mutex_unlock (*currentComponentLock);

            if ( currentHeight >= 16)
                currentHeight = -1;

            if ( currentHeight >=0 ){
                LED_display_rectangle(slot*4, currentHeight, slot*4 + width-1, currentHeight, color_mapping[slot]); 
                currentComponent[i].height++;
                if (currentComponent[i].height >= 16){
                    currentComponent = -1;
                } 
            }
        } 
        LED_refresh();
        LED_clearCanvas();
    }
    printf ( "stop displaying loop \n");
}

void Display_cleanup(void)
{
    running = false;
    pthread_join (displayHtread, NULL);
}

void Display_generateComponent(int button)
{
    pthread_mutex_lock (*currentComponentLock);
    {
        for (int i = 0; i < COMPONENT_MAX_NUM; i++){
            if (currentComponent[i].height == -1){
                currentComponent[i].height = 0;
                currentComponent[i].slot = button;
                break;
            }
        }
    }
    pthread_mutex_unlock (*currentComponentLock);
    return;
}
