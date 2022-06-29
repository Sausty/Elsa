/**
 * @file XAudio2Backend.h
 * @author Milo Heinrich (MikuoH15TH@gmail.com)
 * @brief This file contains the audio backend for XAudio2.
 * @version 1.0
 * @date 2022-06-29
 */
#ifndef ELSA_XAUDIO2_BACKEND_H
#define ELSA_XAUDIO2_BACKEND_H

#include <Defines.h>
#include <Audio/Backend/AudioTypes.h>

b8 XAudio2BackendInit(AudioBackend* backend);
void XAudio2BackendShutdown(AudioBackend* backend);
void XAudio2BackendUpdate(AudioBackend* backend);

#endif
