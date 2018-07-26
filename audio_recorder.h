// Record sounds from microphone jack in real time. The library will use a linked list
// as its internal data structure. 
#ifndef _AUDIO_RECORDER_H_
#define _AUDIO_RECORDER_H_

extern "C" {

// init() must be called before any other functions,
// cleanup() must be called last to stop recording threads and free memory.
void AudioRecorder_init(void);
void AudioRecorder_cleanup(void);

unsigned long AudioRecorder_getFrameSize(void);
short *AudioRecorder_getNextAudioReading(void);

// Get/set the volume.
// setVolume() function posted by StackOverflow user "trenki" at:
// http://stackoverflow.com/questions/6787318/set-alsa-master-volume-from-c-code
int  AudioRecorder_getVolume(void);
void AudioRecorder_setVolume(int newVolume);

}

#endif

