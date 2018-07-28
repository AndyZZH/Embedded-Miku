#include <climits>
#include <cstdio>
#include <mutex>

#include "audio.h"
#include "playback.h"


class AudioPlayer : public Audio {
public:
    AudioPlayer();
    ~AudioPlayer();

    void play(float* frame, int frameSize);
private:
    std::mutex audioMutex;
    void doThread() override;
};


AudioPlayer::AudioPlayer() : Audio(PLAYBACK) {
    // Launch a new thread to start playing back
    // playbackBuffer = nullptr;
    // threadObj = std::thread([this]{ this->doThread(); });
}


AudioPlayer::~AudioPlayer() {
    // delete[] playbackBuffer;
}


void AudioPlayer::play(float* frame, int frameSize) {
    // Output the audio
    std::lock_guard<std::mutex> guard(audioMutex);
    snd_pcm_sframes_t frames = snd_pcm_writei(handle, frame, frameSize);

    // Check for (and handle) possible error conditions on output
    if (frames < 0) {
        fprintf(stderr, "[AudioPlayback]: writei() returned %li\n", frames);
        frames = snd_pcm_recover(handle, frames, 1);
    }
    if (frames < 0) {
        fprintf(stderr, "[AudioPlayback] ERROR: Failed writing audio with snd_pcm_writei(): %li\n", frames);
        exit(EXIT_FAILURE);
    }
    if (frames > 0 && (unsigned long) frames < playbackBufferSize) {
        printf("[AudioPlayback] Short write (expected %li, wrote %li)\n", playbackBufferSize, frames);
    }
}


void AudioPlayer::doThread() {

}

// ----------------------------------------------------------------------------
static AudioPlayer *player;

extern "C"
void Playback_init(void) {
    player = new AudioPlayer();
}

extern "C"
void Playback_cleanup(void) {
    delete player;
}

extern "C"
void Playback_playWithDelay(float* frame, int frameSize, long delayTime) {
    // Create a new thread for delayed queueing wavedata
    std::thread([=]{
        using namespace std;
        this_thread::sleep_for(chrono::milliseconds(delayTime));
        player->play(frame, frameSize); 
        delete[] frame;
    }).detach();
}
