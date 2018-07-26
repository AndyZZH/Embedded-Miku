#include <climits>
#include <cstdio>
#include <mutex>

#include "audio.h"
#include "playback.h"

// #define MAX_SOUND_BITES 30

// struct wavedata_t {
//     short *pData;
// 	int numSamples;
// };

// // Currently active (waiting to be played) sound bites
// struct playbackSound_t {
//     // A pointer to a previously allocated sound bite (wavedata_t struct).
//     // Note that many different sound-bite slots could share the same pointer
//     // (overlapping cymbal crashes, for example)
//     wavedata_t *pSound;

//     // The offset into the pData of pSound. Indicates how much of the
//     // sound has already been played (and hence where to start playing next).
//     int location;
// } ;


class AudioPlayer : public Audio {
public:
    AudioPlayer();
    ~AudioPlayer();

    void queueSound(short* frame);
private:
    short *playbackBuffer;
    std::mutex audioMutex;
    // playbackSound_t *soundBites;
    // void fillPlaybackBuffer();
    void doThread() override;
};


AudioPlayer::AudioPlayer() : Audio(PLAYBACK) {
    // soundBites = new playbackSound_t[MAX_SOUND_BITES];

    // Initialize the currently active sound-bites being played
    // Implement this. Hint: set the pSound pointer to NULL for each
    //     sound bite.
    // for (int i = 0; i < MAX_SOUND_BITES; ++i) {
    //     soundBites[i].pSound = nullptr;
    //     soundBites[i].location = 0;
    // }

    // playbackBuffer = new short[playbackBufferSize];

    // Launch a new thread to start playing back
    playbackBuffer = nullptr;
    threadObj = std::thread([this]{ this->doThread(); });
}


AudioPlayer::~AudioPlayer() {
    // delete[] playbackBuffer;
}


void AudioPlayer::queueSound(short* frame) {
    playbackBuffer = frame;
}


// void AudioPlayer::queueSound(short* frame, int frameSize)
// {
//     wavedata_t pSound { frame, frameSize };
//     // Ensure we are only being asked to play "good" sounds:
//     assert(pSound.numSamples > 0);
//     assert(pSound.pData);


//     // Insert the sound by searching for an empty sound bite spot
    
//     //  * 1. Since this may be called by other threads, and there is a thread
//     //  *    processing the soundBites[] array, we must ensure access is threadsafe.
//     std::lock_guard<std::mutex> guard(audioMutex);
    
//     //  * 2. Search through the soundBites[] array looking for a free slot.
//     //  * 3. If a free slot is found, place the new sound file into that slot.
//     //  *    Note: You are only copying a pointer, not the entire data of the wave file!
//     //  * 4. After searching through all slots, if no free slot is found then print
//     //  *    an error message to the console (and likely just return vs asserting/exiting
//     //  *    because the application most likely doesn't want to crash just for
//     //  *    not being able to play another wave file.
//      for (int i = 0; i < MAX_SOUND_BITES; ++i) {
//          if (soundBites[i].pSound == nullptr) {
//              soundBites[i].pSound = &pSound;
//              soundBites[i].location = 0;
//              return;
//          } 
//      }

//      // No free slot is found
//      fprintf(stderr, "[AudioMixer_queueSound] WARNING: No empty sound bite slot is found. ");
// }




// // Fill the playbackBuffer array with new PCM values to output.
// //    playbackBuffer: buffer to fill with new PCM data from sound bites.
// //    size: the number of values to store into playbackBuffer
// void AudioPlayer::fillPlaybackBuffer()
// {
//     int size = playbackBufferSize;

//     //  * 1. Wipe the playbackBuffer to all 0's to clear any previous PCM data.
//     //  *    Hint: use memset()
//     memset(playbackBuffer, 0, size * sizeof(short));

//     //  * 2. Since this is called from a background thread, and soundBites[] array
//     //  *    may be used by any other thread, must synchronize this.
//     std::lock_guard<std::mutex> guard(audioMutex);

//     //  * 3. Loop through each slot in soundBites[], which are sounds that are either
//     //  *    waiting to be played, or partially already played:
//     //  *    - If the sound bite slot is unused, do nothing for this slot.
//     //  *    - Otherwise "add" this sound bite's data to the play-back buffer
//     //  *      (other sound bites needing to be played back will also add to the same data).
//     //  *      * Record that this portion of the sound bite has been played back by incrementing
//     //  *        the location inside the data where play-back currently is.
//     //  *      * If you have now played back the entire sample, free the slot in the
//     //  *        soundBites[] array.
//     for (int i = 0; i < MAX_SOUND_BITES; ++i) {
//         if (soundBites[i].pSound != nullptr) {
//             int location = soundBites[i].location;
//             wavedata_t *pSound = soundBites[i].pSound;
//             for (int j = 0; location < pSound->numSamples && j < size; ++location, ++j) {
//                 int sample = playbackBuffer[j];
//                 sample += pSound->pData[location];

//                 // Clamping signals if overflowing
//                 if (sample > SHRT_MAX) {
//                     sample = SHRT_MAX;
//                 } else if (sample < SHRT_MIN) {
//                     sample = SHRT_MIN;
//                 }

//                 playbackBuffer[j] = (short) sample;
//             }

//             // Played the entire sample, need to clear the sound bite
//             if (location >= pSound->numSamples) {
//                 soundBites[i].pSound = nullptr;
//                 soundBites[i].location = 0;
//             } else {
//                 soundBites[i].location = location;
//             }
//         }
        
//     }
//     //  *
//     //  * Notes on "adding" PCM samples:
//     //  * - PCM is stored as signed shorts (between SHRT_MIN and SHRT_MAX).
//     //  * - When adding values, ensure there is not an overflow. Any values which would
//     //  *   greater than SHRT_MAX should be clipped to SHRT_MAX; likewise for underflow.
//     //  * - Don't overflow any arrays!
//     //  * - Efficiency matters here! The compiler may do quite a bit for you, but it doesn't
//     //  *   hurt to keep it in mind. Here are some tips for efficiency and readability:
//     //  *   * If, for each pass of the loop which "adds" you need to change a value inside
//     //  *     a struct inside an array, it may be faster to first load the value into a local
//     //  *      variable, increment this variable as needed throughout the loop, and then write it
//     //  *     back into the struct inside the array after. For example:
//     //  *           int offset = myArray[someIdx].value;
//     //  *           for (int i =...; i < ...; i++) {
//     //  *               offset ++;
//     //  *           }
//     //  *           myArray[someIdx].value = offset;
//     //  *   * If you need a value in a number of places, try loading it into a local variable
//     //  *          int someNum = myArray[someIdx].value;
//     //  *          if (someNum < X || someNum > Y || someNum != Z) {
//     //  *              someNum = 42;
//     //  *          }
//     //  *          ... use someNum vs myArray[someIdx].value;
//     //  *
// }


void AudioPlayer::doThread() {
    // TODO: Need to handle infinite loop if we want to implememnt stopping mechanism
    while (true) {
        // Generate next block of audio
        // fillPlaybackBuffer();

        if (playbackBuffer == nullptr) 
            continue;

        // Output the audio
        snd_pcm_sframes_t frames = snd_pcm_writei(handle, playbackBuffer, playbackBufferSize);

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

        delete[] playbackBuffer;
        playbackBuffer = nullptr;
    }
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
void Playback_playWithDelay(short* frame, int frameSize, long delayTime) {
    // Create a new thread for delayed queueing wavedata
    std::thread([=]{
        using namespace std;
        this_thread::sleep_for(chrono::milliseconds(delayTime));
        player->queueSound(frame); 
    }).detach();
}