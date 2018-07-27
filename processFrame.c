#include "audio_recorder.h"
#include "processFrame.h"
#include "beat.h"
#include "playback.h"
#include "game.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <stdbool.h>

#define DEFAULT_HOP_SIZE 50

// prototype
static void* processFrameThread(void* arg);

static _Bool processFrameTerminated = false;
static pthread_t processFrameId;
static int frameSize;
static struct timespec reqtime;
static struct BTrack* bt;

void ProcessFrame_init(void){
    reqtime.tv_sec=0;
    reqtime.tv_nsec = 50 * 1000;
    bt = newBTrack_hs_fs(DEFAULT_HOP_SIZE, 100);    
    pthread_create(&processFrameId, NULL, processFrameThread, NULL);
}

void ProcessFrame_cleanup(void){
    printf("[ProcessFrame] processFrame cleanup starting");
    processFrameTerminated = true;
    pthread_join(processFrameId,NULL);
    printf("[ProcessFrame] processFrame cleanup finished");
}

static void* processFrameThread(void* arg){
    printf("[ProcessFrame] processFrame thread start");
    frameSize = AudioRecorder_getFrameSize();
    while (!processFrameTerminated){
        double* frame= AudioRecorder_getNextAudioReading();
        if (frame == NULL){
            continue;
        }
        Playback_playWithDelay(frame,frameSize, Game_getDelayTime());
        if (Beat_isBeat(frame,frameSize)){
            Game_EnqueueBeat();
        }
        nanosleep(&reqtime, NULL);
    }
    return NULL;
}
