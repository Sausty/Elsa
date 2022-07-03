/**
 * @file AudioSource.h
 * @author Milo Heinrich (MikuoH15TH@gmail.com)
 * @brief This file contains functions regarding audio sources.
 * @version 1.0
 * @date 2022-07-02
 */
#ifndef ELSA_AUDIO_SOURCE_H
#define ELSA_AUDIO_SOURCE_H

#include <Audio/AudioTypes.h>

/**
* @brief Creates an audio source.
*
* @param out_source A pointer to the audio source.
* @returns True on success; otherwise false.
*/
ELSA_API b8 AudioSourceCreate(AudioSource* out_source);

/**
* @brief Loads a .wav file to an audio source.
*
* @param path The path of the file to load.
* @param source A pointer to the audio source.
* @returns True on success; otherwise false;
*/
ELSA_API b8 AudioSourceLoad(const char* path, AudioSource* source);

/**
* @brief Plays an audio source.
*
* @param source The audio source to play.
* @returns True on success; otherwise false.
*/
ELSA_API b8 AudioSourcePlay(AudioSource* source);

/**
* @brief Stops an audio source.
*
* @param source The audio source to stop.
*/
ELSA_API void AudioSourceStop(AudioSource* source);

/**
* @brief Sets the volume of an audio source.
*
* @param volume The volume of the source.
* @param source A pointer to the audio source.
*/
ELSA_API void AudioSourceSetVolume(f32 volume, AudioSource* source);

/**
* @brief Sets the pitch of an audio source.
*
* @param pitch The pitch of the source.
* @param source A pointer to the audio source.
*/
ELSA_API void AudioSourceSetPitch(f32 pitch, AudioSource* source);

/**
* @brief Sets the low pass filter of an audio source.
*
* @param frequency The frequency of the low pass filter.
* @param one_over_q The reciprocal Q factor of the low pass filter.
* @param source A pointer to the audio source.
*/
ELSA_API void AudioSourceSetLowPassFilter(f32 frequency, f32 one_over_q, AudioSource* source);

/**
* @brief Destroys an audio source.
*
* @param source A pointer to the audio source.
*/
ELSA_API void AudioSourceDestroy(AudioSource* source);

#endif