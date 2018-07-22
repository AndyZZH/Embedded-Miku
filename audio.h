#include <alsa/asoundlib.h>
#include <iostream>
#include <thread>

#define DEFAULT_VOLUME  80
#define MAX_VOLUME      100

#define SAMPLE_RATE 44100
#define NUM_CHANNELS 1
#define SAMPLE_SIZE (sizeof(short)) 

class Audio {
public:
    Audio();
    void setVolume(int newVolume);
    int getVolume() const { return volume; }
    unsigned long getFrameSize() const { return playbackBufferSize; }
private:
    int volume;
    unsigned long playbackBufferSize;
    snd_pcm_t *handle;

    std::thread threadObj;
    virtual void doThread();
};


void Audio::Audio() {
    volume = 0;
    playbackBufferSize = 0;

    setVolume(DEFAULT_VOLUME);
}


void Audio::setVolume(int newVolume) {
    // Ensure volume is reasonable; If so, cache it for later getVolume() calls.
    if (newVolume < 0 || newVolume > MAX_VOLUME) {
        std::cout << "ERROR: Volume must be between 0 and 100.\n" << std::endl;
        return;
    }
    volume = newVolume;

    long min, max;
    snd_mixer_t *handle;
    snd_mixer_selem_id_t *sid;
    const char *card = "default";
    const char *selem_name = "PCM";

    snd_mixer_open(&handle, 0);
    snd_mixer_attach(handle, card);
    snd_mixer_selem_register(handle, NULL, NULL);
    snd_mixer_load(handle);

    snd_mixer_selem_id_alloca(&sid);
    snd_mixer_selem_id_set_index(sid, 0);
    snd_mixer_selem_id_set_name(sid, selem_name);
    snd_mixer_elem_t* elem = snd_mixer_find_selem(handle, sid);

    snd_mixer_selem_get_playback_volume_range(elem, &min, &max);
    snd_mixer_selem_set_playback_volume_all(elem, volume * max / 100);

    snd_mixer_close(handle);
}