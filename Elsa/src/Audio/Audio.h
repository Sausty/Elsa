/**
 * @file Audio.h
 * @author Milo Heinrich (MikuoH15TH@gmail.com)
 * @brief This file contains functions and logic for the audio system.
 * @version 1.0
 * @date 2022-06-19
 */
#ifndef ELSA_AUDIO_H
#define ELSA_AUDIO_H

#include <Defines.h>

/** @brief Opaque object representing an audio clip. */
typedef struct AudioClip AudioClip;

/**
 * @brief Initialises the audio system.
 */
ELSA_API void AudioInit();

/**
 * @brief Terminates the audio system.
 */
ELSA_API void AudioExit();

/**
 * @brief Updates the audio system.
 */
ELSA_API void AudioUpdate();

/**
 * @brief Loads an audio clip from disk.
 * @param path The path of the audio clip to load.
 * @returns The generated audio clip.
 */
ELSA_API AudioClip* AudioLoadClip(const char* path);

/**
 * @brief Frees an audio clip.
 * @param clip The audio clip to free.
 */
ELSA_API void AudioFreeClip(AudioClip* clip);

/**
 * @brief Plays an audio clip.
 * @param clip The audio clip to play.
 */
ELSA_API void AudioPlayClip(AudioClip* clip);

/**
 * @brief Stops an audio clip. No effect if the clip isn't playing.
 * @param clip The audio clip to stop.
 */
ELSA_API void AudioStopClip(AudioClip* clip);

/**
 * @brief Loops the audio clip when it ends.
 * @param clip The audio clip to loop.
 * @param loop Boolean representing whether or not the audio clip should loop.
 */
ELSA_API void AudioLoopClip(AudioClip* clip, b8 loop);

/**
 * @brief Sets the volume of an audio clip.
 * @param clip The audio clip that will have its volume changed.
 * @param volume The volume of the audio clip.
 */
ELSA_API void AudioSetClipVolume(AudioClip* clip, f32 volume);

#endif