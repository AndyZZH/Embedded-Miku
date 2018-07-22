#ifndef __BTRACK_WRAPPER_H
#define __BTRACK_WRAPPER_H
#include <stdbool.h>
#ifdef __cplusplus
extern "C" {
#endif

typedef struct BTrack BTrack;

BTrack* newBTrack();
BTrack* newBTrack_hs(int hopSize_);
BTrack* newBTrack_hs_fs(int hopSize_, int frameSize_);
void BTrack_call_processAudioFrame(struct BTrack*,double *frame);
bool BTrack_call_beatDueInCurrentFrame(struct BTrack*);
void BTrack_clean(struct BTrack* bt);
#ifdef __cplusplus
}
#endif
#endif