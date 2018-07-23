#ifndef __PLAYBACK_H
#define __PLAYBACK_H
void Playback_init(void);
void Playback_cleanup(void);
void Playback_playWithDelay(short* frame, int frameSize, long delayTime);
#endif