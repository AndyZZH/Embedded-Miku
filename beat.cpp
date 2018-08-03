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
#define AUBIO_ONSET_LOG_COMPRESSION         10
#define AUBIO_ONSET_MIN_INTER_INTERVAL_MS   200

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
        std::cout << "[" << Util_CurrentTimeStr() << "] " << "Is beat! " << std::endl;
        Game_EnqueueBeat();
    }

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

    if (aubio_onset_set_compression(tempo, AUBIO_ONSET_LOG_COMPRESSION)) {
        std::cerr << "Failed to enable log compression for aubio library!" << std::endl;
    }

    if (aubio_onset_set_minioi_ms(tempo, AUBIO_ONSET_MIN_INTER_INTERVAL_MS)) {
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