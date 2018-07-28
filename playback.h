#ifndef __PLAYBACK_H
#define __PLAYBACK_H

/*
 * Function:  Playback_playWithDelay()
 * --------------------
 * Function to enqueue frame to play
 * 
 *  returns: void
 */

#ifdef __cplusplus
extern "C" {
#endif

void Playback_init(void);
void Playback_cleanup(void);
void Playback_playWithDelay(float* frame, int frameSize, long delayTime);

#ifdef __cplusplus
}
#endif

#endif
