#ifndef __BEAT_H
#define __BEAT_H

#include <stdbool.h>
#include "./libs/btrack/BTrack_wrapper.h"

bool Beat_isBeat(short* frame, int frameSize);
// bool Beat_isBeat(double* frame, int frameSize, BTrack* bt);
#endif