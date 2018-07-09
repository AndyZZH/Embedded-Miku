#include "./libs/btrack/BTrack_wrapper.h"
#include "beat.h"

#include <stdio.h>
bool Beat_isBeat(short* frameInShort, int frameSize){
    struct BTrack* bt = newBTrack_hs_fs(frameSize/2, frameSize);
    double frame[frameSize];
    for (int i = 0; i < frameSize; i++){
        frame[i] = (double)frameInShort[i];
    }
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