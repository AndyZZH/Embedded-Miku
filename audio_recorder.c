#include "audio_recorder.h"

#include <stdlib.h>
#include <pthread.h>

#define DEMO_SRC "wave-files/testing.wav"
#define TOTAL_WAVE_TYPE 1

// static void* staticAudioThread(void* arg);

static wavedata_t * demoWaveFile;
static pthread_t staticAudioThreadId;
static unsigned long current = 0;
static unsigned long frameSize;

void AudioRecorder_init(void){
    char *demoWaveFileSrc = DEMO_SRC;
    demoWaveFile = malloc(sizeof(wavedata_t));
    AudioMixer_readWaveFileIntoMemory(demoWaveFileSrc, demoWaveFile);
    frameSize = getFrameSize();
    // pthread_create(&staticAudioThreadId, NULL, staticAudioThread, NULL);
}

void AudioRecorder_cleanup(void){
    // pthread_join(staticAudioThreadId, NULL);
    printf("Stopped Beat...\n");
    //Clean wave files
    AudioMixer_freeWaveFileData(demoWaveFile);
    free(demoWaveFile);
}

unsigned long AudioRecorder_getFrameSize(void){
    return demoWaveFile->numSamples;
}

short *AudioRecorder_getNextAudioReading(void){
    current+=frameSize;
    return demoWaveFile->pData[current];
}

// static void* staticAudioThread(void* arg){}