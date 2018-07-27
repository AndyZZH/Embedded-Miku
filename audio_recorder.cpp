#include <alsa/asoundlib.h>
#include <cstdio>
#include <mutex>
#include <queue>
#include <thread>

#include "audio.h"
#include "audio_recorder.h"


class AudioRecorder : public Audio {
public:
    AudioRecorder();
    ~AudioRecorder();
    short *getNextAudioReading();
private:
    std::mutex soundQueueMutex;
    std::queue<short*> sndQueue;
    void doThread() override;
};


AudioRecorder::AudioRecorder() : Audio(CAPTURE) {
    // Launch a new thread to start sampling and push data to queue
    threadObj = std::thread([this]{ this->doThread(); });
}


AudioRecorder::~AudioRecorder() {
    // Intentionally left blank.
    // Thread joining is processed in the base class. 
}


short *AudioRecorder::getNextAudioReading() {
    std::lock_guard<std::mutex> guard(soundQueueMutex);
    if (!sndQueue.empty()) {
        short *returnVal = sndQueue.front();
        sndQueue.pop();
        return returnVal;
    } else {
        return nullptr;
    }
} 


void AudioRecorder::doThread() {
    // TODO: Need to handle infinite loop. Possibly implement stopping mechanism. 
    while (true) {
        // Create a new array to store read samples
        short *buffer = new short[playbackBufferSize];

        // Read the audio
        snd_pcm_sframes_t frames = snd_pcm_readi(handle, buffer, playbackBufferSize);

        // Check for (and handle) possible error conditions on output
        if (frames < 0) {
            fprintf(stderr, "[AudioRecorder]: readi() returned %li\n", frames);
            frames = snd_pcm_recover(handle, frames, 1);
        }
        if (frames < 0) {
            fprintf(stderr, "[AudioRecorder] ERROR: Failed writing audio with snd_pcm_readi(): %li\n", frames);
            exit(EXIT_FAILURE);
        }
        if (frames > 0 && frames < (long)playbackBufferSize) {
            printf("[AudioRecorder] Short write (expected %li, wrote %li)\n", playbackBufferSize, frames);
        }

        // Push the pointer of data to the queue
        std::lock_guard<std::mutex> guard(soundQueueMutex);
        sndQueue.push(buffer);
    }
}


// ----- Adapters to wrap C++ code into C
static AudioRecorder *recorder;

// extern "C"
// void AudioRecorder_setVolume(int newVolume) {
//     recorder->setVolume(newVolume);
// }

extern "C"
unsigned long AudioRecorder_getFrameSize(void) {
    return recorder->getFrameSize();
}

extern "C"
void AudioRecorder_init(void) {
    recorder = new AudioRecorder();
}

extern "C"
void AudioRecorder_cleanup(void) {
    delete recorder;
}

extern "C"
short *AudioRecorder_getNextAudioReading(void) {
    return recorder->getNextAudioReading();
}
