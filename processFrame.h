// Module to dequeue sound(through AudioRecorder_getNextAudioReading()) and playback
// If there is beat in the sound
// * Game_EnqueueBeat()
#ifndef __PROCESS_FRAME_H
#define __PROCESS_FRAME_H


void ProcessFrame_init(void);
void ProcessFrame_cleanup(void);

#endif
