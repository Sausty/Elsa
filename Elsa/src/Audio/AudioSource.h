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
* @brief Destroys an audio source.
*
* @param source A pointer to the audio source.
*/
ELSA_API void AudioSourceDestroy(AudioSource* source);

#endif