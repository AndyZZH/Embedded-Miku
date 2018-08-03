// Record sounds from microphone jack in real time. The library will use a linked list
// as its internal data structure. 
#ifndef _AUDIO_RECORDER_H_
#define _AUDIO_RECORDER_H_

#ifdef __cplusplus
extern "C" {
#endif

// init() must be called before any other functions,
// cleanup() must be called last to stop recording threads and free memory.
void AudioRecorder_init(void);
void AudioRecorder_cleanup(void);

/* This function will return a number specifying the frame size read from ALSA library.
 * Frame size is used in various locations including creating buffer array. 
 */
unsigned long AudioRecorder_getFrameSize(void);

/* Get the latest audio recording fron a queue. The AudioRecorder will record samples 
 * using ALSA library and stores the readings in a queue. Calling this function will
 * dequeue the pointer to the latest reading in the queue.
 */
float *AudioRecorder_getNextAudioReading(void);

// Get/set the volume.
// setVolume() function posted by StackOverflow user "trenki" at:
// http://stackoverflow.com/questions/6787318/set-alsa-master-volume-from-c-code
int  AudioRecorder_getVolume(void);

#ifdef __cplusplus
}
#endif

#endif

