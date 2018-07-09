#include "BTrack.h"
#include "BTrack_wrapper.h"

#include <stdlib.h>
// C Usage:
// struct BTrack;
// void Btrack_call_processAudioFrame(struct BTrack*,double *frame);
// bool Btrack_call_beatDueInCurrentFrame(struct BTrack*,double *frame);
extern "C" {
        BTrack* newBTrack() {
                return new BTrack();
        }
        BTrack* newBTrack_hs(int hopSize_) {
                return new BTrack(hopSize_);
        }
        BTrack* newBTrack_hs_fs(int hopSize_, int frameSize_) {
                return new BTrack(hopSize_,frameSize_);
        }

        void BTrack_call_processAudioFrame(struct BTrack* bt,double *frame){
                bt->processAudioFrame(frame);
        }
        bool BTrack_call_beatDueInCurrentFrame(struct BTrack* bt){
                return bt->beatDueInCurrentFrame();
        }

        void BTrack_clean(struct BTrack* bt){
                delete bt;
        }
}