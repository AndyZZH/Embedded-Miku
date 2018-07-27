#include "./libs/btrack/BTrack_wrapper.h"
#include "beat.h"

#include <stdio.h>

#define DEFAULT_HOP_SIZE 64
/*
 * Function:  Beat_isBeat
 * --------------------
 * Function to ouput whether there is beat in a frame
 *  returns: Boolean
 */

bool Beat_isBeat(double* frame, int frameSize){
    struct BTrack* bt = newBTrack_hs_fs(DEFAULT_HOP_SIZE, frameSize);
    // fill frame
    BTrack_call_processAudioFrame(bt,frame);
    bool ans = BTrack_call_beatDueInCurrentFrame(bt);
    BTrack_clean(bt);
    if (ans)
    {
        printf("beat");
    }
    else{
        printf("no beat");
    }
    return ans;
}