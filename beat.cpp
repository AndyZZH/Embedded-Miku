#include "./libs/btrack/BTrack_wrapper.h"
#include "beat.h"
#include "audio_recorder.h"

extern "C" {
#include "game.h"
}

#include <iostream>
#include <thread>

// #define DEFAULT_HOP_SIZE 50
/*
 * Function:  Beat_isBeat
 * --------------------
 * Function to ouput whether there is beat in a frame
 *  returns: Boolean
 */
// bool Beat_isBeat(double* frame, int frameSize,BTrack* bt){

static volatile bool isIdle = true;

// bool Beat_isBeat(short* frame, int frameSize){

static void Beat_processBeat(double* frame, unsigned long frameSize, BTrack* bt) {
    isIdle = false;
    // struct BTrack* bt = newBTrack_hs_fs(frameSize/2, frameSize);
    // std::cout << "frameSize: " <<  frameSize << std::endl;
    // fill frame
    BTrack_call_processAudioFrame(bt, frame);
    bool ans = BTrack_call_beatDueInCurrentFrame(bt);

    std::cout << frame[0] << std::endl;

    if (ans) {
        std::cout << "Is beat!" << std::endl;
        Game_EnqueueBeat();
    } else {
        std::cout << "Not a beat" << std::endl;
    }

    // BTrack_clean(bt);
    isIdle = true;
    // return ans;
    
    // **************************************
    // // threshold
    // long sum = 0;
    // for (int i = 0; i< frameSize; i++){
    //     // printf("%f\n", frame[i]);
    //     sum = sum + (long)(frame[i]*100);
    // }
    // printf("%ld\n", sum);


    // **************************************
    // random
    // int r = rand() % 10;
    // bool ans = r < 2;
    // if (ans)
    // {
    //     printf("beat\n");
    // }
    // else{
    //     printf("no beat\n");
    // }
    // return ans;
}


extern "C"
bool Beat_isIdle() {
    return isIdle;
}


extern "C"
void Beat_enqueueIfIsBeat(double* frame, unsigned long frameSize, BTrack* bt) {
    std::thread([=]{ Beat_processBeat(frame, frameSize, bt); }).detach();
}