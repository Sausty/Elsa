/**
 * @file AudioBackend.h
 * @author Milo Heinrich (MikuoH15TH@gmail.com)
 * @brief This file contains functions for the audio backend.
 * @version 1.0
 * @date 2022-06-29
 */
#ifndef ELSA_AUDIO_BACKEND_H
#define ELSA_AUDIO_BACKEND_H

#include <Audio/Backend/AudioTypes.h>

/**
 * @brief Creates a new audio backend of the given type.
 * 
 * @param type The type of backend to create (e.g. XAudio2, AVFoundation)
 * @param out_audio_backend A pointer to hold the newly-created audio backend.
 * @return True if successful; otherwise false.
 */
ELSA_API b8 AudioBackendCreate(AudioBackendAPI api, AudioBackend* out_audio_backend);

/**
 * @brief Destroys the given audio backend.
 * 
 * @param audio_backend A pointer to the backend to be destroyed.
 */
ELSA_API void AudioBackendDestroy(AudioBackend* audio_backend);

#endif
