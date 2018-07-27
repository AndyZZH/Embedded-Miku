#ifndef __BEAT_H
#define __BEAT_H

#include "./libs/btrack/BTrack_wrapper.h"

#ifdef __cplusplus
extern "C" {
#endif

// bool Beat_isBeat(short* frame, int frameSize);
bool Beat_isIdle(void);
void Beat_enqueueIfIsBeat(double* frame, unsigned long frameSize, BTrack* bt);

#ifdef __cplusplus
}
#endif

#endif