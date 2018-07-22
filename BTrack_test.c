#include "./libs/btrack/BTrack_wrapper.h"

#include <stdio.h>

int main(int argc, char* argv[]) {
    // int frameSize = XX_getFrameSize();
    int frameSize = 20;
    struct BTrack* b = newBTrack_hz_fz(frameSize/2, frameSize);
    double *frame;
    // fill frame
    BTrack_call_processAudioFrame(b,frame);
    if (BTrack_call_beatDueInCurrentFrame(b))
    {
        printf("beat");
    }
    else{
        printf("no beat");
    }
}
