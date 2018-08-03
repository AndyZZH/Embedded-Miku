#include <exception>
#include <iostream>

#include "audio.h"

#define ALSA_BUFFER_SIZE 80000

Audio::Audio(AudioMode mode) {
    volume = 0;
    playbackBufferSize = 0;



    // Open the PCM input/output depending on audio mode
    if (mode == CAPTURE) {
        setCaptureVolume(DEFAULT_CAPTURE_VOLUME);
        int err = snd_pcm_open(&handle, "default", SND_PCM_STREAM_CAPTURE, 0);
        if (err < 0) {
            printf("Capture open error: %s\n", snd_strerror(err));
            exit(EXIT_FAILURE);
        }
    }
    else if (mode == PLAYBACK) {
        setPlaybackVolume(DEFAULT_PLAYBACK_VOLUME);
        int err = snd_pcm_open(&handle, "default", SND_PCM_STREAM_PLAYBACK, 0);
        if (err < 0) {
            printf("Playback open error: %s\n", snd_strerror(err));
            exit(EXIT_FAILURE);
        }
    }
    else {
        throw new std::invalid_argument("The audio mode specified is not recognized. ");
    }

    // Configure parameters of PCM output
    int err = snd_pcm_set_params(handle,
            // SND_PCM_FORMAT_FLOAT64_LE,
            SND_PCM_FORMAT_FLOAT_LE,
            SND_PCM_ACCESS_RW_INTERLEAVED,
            NUM_CHANNELS,
            SAMPLE_RATE,
            1,		            // Allow software resampling
            ALSA_BUFFER_SIZE);	// 0.08 seconds per buffer
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


Audio::~Audio() {
    threadObj.join();
}


void Audio::setPlaybackVolume(int newVolume) {
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


void Audio::setCaptureVolume(int newVolume) {
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
    const char *selem_name = "PGA";

    snd_mixer_open(&handle, 0);
    snd_mixer_attach(handle, card);
    snd_mixer_selem_register(handle, NULL, NULL);
    snd_mixer_load(handle);

    snd_mixer_selem_id_alloca(&sid);
    snd_mixer_selem_id_set_index(sid, 0);
    snd_mixer_selem_id_set_name(sid, selem_name);
    snd_mixer_elem_t* elem = snd_mixer_find_selem(handle, sid);

    snd_mixer_selem_get_capture_volume_range(elem, &min, &max);
    snd_mixer_selem_set_capture_volume_all(elem, volume * max / 100);

    snd_mixer_close(handle);
}
