#ifndef __PLAYBACK_H
#define __PLAYBACK_H

/*
 * Function:  Playback_playWithDelay()
 * --------------------
 * Function to enqueue frame to play
 * 
 *  returns: void
 */

void Playback_playWithDelay(short* frame, int frameSize, long delayTime);
#endif