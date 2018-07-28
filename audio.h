#ifndef _AUDIO_H_
#define _AUDIO_H_

#include <alsa/asoundlib.h>
#include <thread>

#define DEFAULT_PLAYBACK_VOLUME  100
#define DEFAULT_CAPTURE_VOLUME  80
#define MAX_VOLUME      100

#define SAMPLE_RATE 44100
#define NUM_CHANNELS 1

enum AudioMode {
    CAPTURE, 
    PLAYBACK
};

class Audio {
public:
    Audio(AudioMode mode);
    virtual ~Audio();

    void setPlaybackVolume(int newVolume);
    void setCaptureVolume(int newVolume);
    // int getVolume() const { return volume; }
    unsigned long getFrameSize() const { return playbackBufferSize; }
protected:
    int volume;
    unsigned long playbackBufferSize;
    snd_pcm_t *handle;

    std::thread threadObj;
    // Defining an abstract function which must be overwritten in derived class
    virtual void doThread() = 0;
};

#endif
