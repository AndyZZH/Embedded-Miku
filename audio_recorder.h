// Module to play a static demo audio file
#ifndef _AUDIO_RECORDER_H_
#define _AUDIO_RECORDER_H_

typedef struct {
	int numSamples;
	short *pData;
} wavedata_t;

void AudioRecorder_init(void);
void AudioRecorder_cleanup(void);
unsigned long AudioRecorder_getFrameSize(void);
short *AudioRecorder_getNextAudioReading(void);

// int  AudioRecorder_getVolume(void);
// void AudioRecorder_setVolume(int newVolume);

#endif
