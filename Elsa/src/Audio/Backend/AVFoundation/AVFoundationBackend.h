/**
 * @file XAudio2Backend.h
 * @author Milo Heinrich (MikuoH15TH@gmail.com)
 * @brief This file contains the audio backend for AVFoundation.
 * @version 1.0
 * @date 2022-06-29
 */
#ifndef ELSA_AVFOUNDATION_BACKEND_H
#define ELSA_AVFOUNDATION_BACKEND_H

#include <Defines.h>
#include <Audio/Backend/AudioTypes.h>

b8 AVFoundationBackendInit(AudioBackend* backend);
void AVFoundationBackendShutdown(AudioBackend* backend);
void AVFoundationBackendUpdate(AudioBackend* backend);

#endif
