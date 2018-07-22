#include <alsa/asoundlib.h>
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
    AudioRecorder() : Audio();
    short *getNextAudioReading();
private:
    std::queue<short *> sndQueue;
};


AudioRecorder::AudioRecorder() {
    // Open the PCM output
    int err = snd_pcm_open(&handle, "default", SND_PCM_STREAM_CAPTURE, 0);
    if (err < 0) {
        printf("Playback open error: %s\n", snd_strerror(err));
        exit(EXIT_FAILURE);
    }

    // Configure parameters of PCM output
    err = snd_pcm_set_params(handle,
            SND_PCM_FORMAT_S16_LE,
            SND_PCM_ACCESS_RW_INTERLEAVED,
            NUM_CHANNELS,
            SAMPLE_RATE,
            1,			// Allow software resampling
            50000);		// 0.05 seconds per buffer
    if (err < 0) {
        printf("Playback open error: %s\n", snd_strerror(err));
        exit(EXIT_FAILURE);
    }

    // Allocate this software's playback buffer to be the same size as the
    // the hardware's playback buffers for efficient data transfers.
    // ..get info on the hardware buffers:
    unsigned long unusedBufferSize = 0;
    snd_pcm_get_params(handle, &unusedBufferSize, &playbackBufferSize);

    // Launch a new thread to start recording and push samples to the queue.
    threadObj = thread([this]{ this->doThread(); });
}


short *AudioRecorder::getNextAudioReading() {
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
        sndQueue.push(buffer);
    }
}


// ----- Adapters to wrap C++ code into C
static AudioRecorder recorder;

extern "C"
void AudioRecorder_setVolume(int newVolume) {
    recorder.setVolume(newVolume);
}

extern "C"
unsigned long AudioRecorder_getFrameSize(void) {
    return recorder.getFrameSize();
}

extern "C"
void AudioRecorder_init(void) {
    recorder = AudioRecorder();
}

extern "C"
short *AudioRecorder_getNextAudioReading(void) {
    return recorder.getNextAudioReading();
}