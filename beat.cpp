// #include "./libs/btrack/BTrack_wrapper.h"
#include "beat.h"
#include "audio_recorder.h"
#include "util.h"

#include <aubio/aubio.h>

extern "C" {
#include "game.h"
}

#include <cassert>
#include <iostream>
#include <thread>
#include <chrono>

#define SAMPLE_RATE 44100

// #define DEFAULT_HOP_SIZE 50
/*
 * Function:  Beat_isBeat
 * --------------------
 * Function to ouput whether there is beat in a frame
 *  returns: Boolean
 */
// bool Beat_isBeat(double* frame, int frameSize,BTrack* bt){

static aubio_onset_t *tempo;


static fvec_t *data_in;
static fvec_t *result;
// static unsigned long frameSize;

static volatile bool isIdle = true;



// static void Beat_processBeat(double* frame, unsigned long frameSize, BTrack* bt) {
//     isIdle = false;
//     // struct BTrack* bt = newBTrack_hs_fs(frameSize/2, frameSize);
//     // std::cout << "frameSize: " <<  frameSize << std::endl;
//     // fill frame
//     BTrack_call_processAudioFrame(bt, frame);
//     bool ans = BTrack_call_beatDueInCurrentFrame(bt);

//     std::cout << frame[0] << std::endl;

//     if (ans) {
//         std::cout << "Is beat!" << std::endl;
//         Game_EnqueueBeat();
//     } else {
//         std::cout << "Not a beat" << std::endl;
//     }

//     // BTrack_clean(bt);
//     isIdle = true;
//     // return ans;
    
//     // **************************************
//     // // threshold
//     // long sum = 0;
//     // for (int i = 0; i< frameSize; i++){
//     //     // printf("%f\n", frame[i]);
//     //     sum = sum + (long)(frame[i]*100);
//     // }
//     // printf("%ld\n", sum);


//     // **************************************
//     // random
//     // int r = rand() % 10;
//     // bool ans = r < 2;
//     // if (ans)
//     // {
//     //     printf("beat\n");
//     // }
//     // else{
//     //     printf("no beat\n");
//     // }
//     // return ans;
// }


static void Beat_processBeat(float* frame) {
    isIdle = false;

    // assert(data_in->length == frameSize);


    // Copy data to data_in fvec
    for (unsigned int i = 0; i < data_in->length; ++i) {
        data_in->data[i] = frame[i];
    }


    aubio_onset_do(tempo, data_in, result);
    smpl_t is_beat = fvec_get_sample(result, 0);
    

    if (is_beat) {
        std::cout << "[" << Util_CurrentTimeStr() << "] " << "Is beat! " 
                //   << aubio_tempo_get_bpm(tempo) << " bpm, "
                //   << "with confidence " << aubio_tempo_get_confidence(tempo) 
                  << std::endl;
        Game_EnqueueBeat();
    } //else {
    //     std::cout << "Not a beat" << std::endl;
    // }

    fvec_zeros(data_in);
    fvec_zeros(result);
    isIdle = true;
}


extern "C"
bool Beat_isIdle() {
    return isIdle;
}


extern "C"
void Beat_init() {
    unsigned long frameSize = AudioRecorder_getFrameSize();
    std::cout << "Frame size: " << frameSize << std::endl;
    int hopSize = frameSize / 2;

    data_in = new_fvec(frameSize);
    result = new_fvec(2);
    tempo = new_aubio_onset("energy", frameSize, hopSize, SAMPLE_RATE);

    // if (aubio_onset_set_threshold(tempo, 1)) {
    //     std::cerr << "Failed to set threshold for aubio library!" << std::endl;
    // }

    if (aubio_onset_set_awhitening(tempo, 1)) {
        std::cerr << "Failed to enable adaptive whitening for aubio library!" << std::endl;
    }

    if (aubio_onset_set_compression(tempo, 10)) {
        std::cerr << "Failed to enable log compression for aubio library!" << std::endl;
    }

    if (aubio_onset_set_minioi_ms(tempo, 200)) {
        std::cerr << "Failed to set minimum inter onset interval for aubio library!" << std::endl;
    }
}


// extern "C"
// void Beat_enqueueIfIsBeat(double* frame, unsigned long frameSize, BTrack* bt) {
//     std::thread([=]{ Beat_processBeat(frame, frameSize, bt); }).detach();
// }

extern "C"
void Beat_enqueueIfIsBeat(float* frame) {
    std::thread([=]{ Beat_processBeat(frame); }).detach();
}