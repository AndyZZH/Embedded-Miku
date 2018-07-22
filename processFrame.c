#include "audio_recorder.h"
#include "processFrame.h"
#include "beat.h"
#include "playback.h"
#include "game.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

// prototype
static void* processFrame(void* arg);

static _Bool processFrameTerminated = false;
static pthread_t processFrameId;
static int frameSize;
void ProcessFrame_init(void){
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
        short* frame= AudioRecorder_getNextAudioReading();
        if (frame == NULL){
            continue;
        }
        Playback_playWithDelay(frame,frameSize, Game_getDelayTime);
        if (Beat_isBeat(frame,frameSize)){
            Game_EnqueueBeat();
        }
    }
    return NULL;
}