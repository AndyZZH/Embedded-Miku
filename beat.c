#include "./libs/btrack/BTrack_wrapper.h"
#include "beat.h"
#include "audio_recorder.h"
#include <stdio.h>
#include <stdlib.h>

#define DEFAULT_HOP_SIZE 50
/*
 * Function:  Beat_isBeat
 * --------------------
 * Function to ouput whether there is beat in a frame
 *  returns: Boolean
 */
// bool Beat_isBeat(double* frame, int frameSize,BTrack* bt){
bool Beat_isBeat(short* frame, int frameSize){
    // struct BTrack* bt = newBTrack_hs_fs(DEFAULT_HOP_SIZE, frameSize);
    // printf("frameSize: %d\n", frameSize);
    // fill frame
    // BTrack_call_processAudioFrame(bt,frame);
    // bool ans = BTrack_call_beatDueInCurrentFrame(bt);
    // bool ans = false;
    // BTrack_clean(bt);
    
    // **************************************
    // // threshold
    // long sum = 0;
    // for (int i = 0; i< frameSize; i++){
    //     // printf("%f\n", frame[i]);
    //     sum = sum + (long)(frame[i]*100);
    // }
    // printf("%ld\n", sum);


    // **************************************
    // random
    int r = rand() % 10;
    bool ans = r < 2;
    if (ans)
    {
        printf("beat\n");
    }
    else{
        printf("no beat\n");
    }
    return ans;
}