#include <alsa/asoundlib.h>
#include <iostream>
#include <queue>
using namespace std;

extern "C" {
    #include "audio_recorder.h"
}


#define DEFAULT_VOLUME 80

#define SAMPLE_RATE 44100
#define NUM_CHANNELS 1
#define SAMPLE_SIZE (sizeof(short)) 


class AudioRecorder {
public:
    AudioRecorder();
    void setVolume(int newVolume);
    int getVolume() const { return volume; }
    unsigned long getFrameSize() const { return playbackBufferSize; }

private:
    queue<short *> sndBuffer;
    int volume;
    unsigned long playbackBufferSize;
    snd_pcm_t *handle;
};


AudioRecorder::AudioRecorder() {
    volume = 0;
    playbackBufferSize = 0;

    setVolume(DEFAULT_VOLUME);

    // Open the PCM output
    int err = snd_pcm_open(&handle, "default", SND_PCM_STREAM_PLAYBACK, 0);
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
}


void AudioRecorder::setVolume(int newVolume) {
    // Ensure volume is reasonable; If so, cache it for later getVolume() calls.
    if (newVolume < 0 || newVolume > AUDIORECORDER_MAX_VOLUME) {
        cout << "ERROR: Volume must be between 0 and 100.\n" << endl;
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

