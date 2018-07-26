#include <alsa/asoundlib.h>
#include <cstdio>
#include <mutex>
#include <queue>
#include <thread>

#include "audio.h"

extern "C" {
    #include "audio_recorder.h"
}


#define DEFAULT_VOLUME 80

#define SAMPLE_RATE 44100
#define NUM_CHANNELS 1
#define SAMPLE_SIZE (sizeof(short)) 


class AudioRecorder : public Audio {
public:
    AudioRecorder();
    ~AudioRecorder();
    std::unique_ptr<short[]> getNextAudioReading();
private:
    std::mutex soundQueueMutex;
    std::queue<std::unique_ptr<short[]>> sndQueue;
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


std::unique_ptr<short[]> AudioRecorder::getNextAudioReading() {
    std::lock_guard<std::mutex> guard(soundQueueMutex);
    if (!sndQueue.empty()) {
        auto returnVal = std::move(sndQueue.front());
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
        // std::unique_ptr<short[]> buffer(new short[playbackBufferSize]);

        // Read the audio
        snd_pcm_sframes_t frames = snd_pcm_readi(handle, buffer, playbackBufferSize);

        // Check for (and handle) possible error conditions on output
        if (frames < 0) {
            fprintf(stderr, "AudioMixer: readi() returned %li\n", frames);
            frames = snd_pcm_recover(handle, frames, 1);
        }
        if (frames < 0) {
            fprintf(stderr, "ERROR: Failed writing audio with snd_pcm_readi(): %li\n", frames);
            exit(EXIT_FAILURE);
        }
        if (frames > 0 && frames < (long)playbackBufferSize) {
            printf("Short write (expected %li, wrote %li)\n", playbackBufferSize, frames);
        }

        // Push the pointer of data to the queue
        std::lock_guard<std::mutex> guard(soundQueueMutex);
        std::unique_ptr<short[]> buffer_unique_ptr(buffer);
        sndQueue.push(std::move(buffer_unique_ptr));
    }
}


// ----- Adapters to wrap C++ code into C
static AudioRecorder *recorder;

extern "C"
void AudioRecorder_setVolume(int newVolume) {
    recorder->setVolume(newVolume);
}

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
    return recorder->getNextAudioReading().get();
}