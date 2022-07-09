/**
 * @file AudioFrontend.h
 * @author Milo Heinrich (MikuoH15TH@gmail.com)
 * @brief The audio frontend, which is the only thing the rest of the engine sees.
 * This is responsible for transferring any data to and from the audio backend
 * in an agnostic way.
 * @version 1.0
 * @date 2022-06-29
 */
#ifndef ELSA_AUDIO_FRONTEND_H
#define ELSA_AUDIO_FRONTEND_H

#include <Defines.h>
#include <Audio/Backend/AudioBackend.h>
#include <Audio/AudioTypes.h>

/**
 * @brief Initializes the renderer frontend.
 * 
 * @param application_name The name of the application.
 * @returns True on success; otherwise false.
 */
ELSA_API b8 AudioFrontendInit();

/**
 * @brief Shuts the renderer frontend down.
 */
ELSA_API void AudioFrontendShutdown();

/**
* @brief Updates the renderer frontend.
*/
ELSA_API void AudioFrontendUpdate();

#endif
