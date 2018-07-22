// Module to dequeue sound(through AudioRecorder_getNextAudioReading()) and process it
// 
// If there is beat in the sound
// 1. void Game_EnqueueBeat(void);
#ifndef __PROCESS_FRAME_H
#define __PROCESS_FRAME_H


void ProcessFrame_init(void);
void ProcessFrame_cleanup(void);

#endif