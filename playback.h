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

/* The function will play the input frame array after a certain delayTime. 
 *
 * Parameter: frame: a pointer to a float array specifying the frame buffer to be played.
 *            frameSize: an integer specifying the size of parameter frame. 
 *            delayTime: a long number specifying how long the delay will be in milliseconds. 
 */
void Playback_playWithDelay(float* frame, int frameSize, long delayTime);

#ifdef __cplusplus
}
#endif

#endif
