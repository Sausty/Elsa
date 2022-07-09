/**
 * @file AudioTypes.h
 * @author Milo Heinrich (MikuoH15TH@gmail.com)
 * @brief This file contains type definitions regarding backend audio data.
 * @version 1.0
 * @date 2022-06-29
 */
#ifndef ELSA_AUDIO_TYPES_H
#define ELSA_AUDIO_TYPES_H

#include <Defines.h>
#include <Audio/AudioTypes.h>

typedef enum AudioBackendAPI {
	/** @brief (SUPPORTED: WIN32) The XAudio2 backend */
	AUDIO_BACKEND_API_XAUDIO2,
	/** @brief (SUPPORTED: MACOS) The AVFoundation backend */
	AUDIO_BACKEND_API_AVFOUNDATION
} AudioBackendAPI;

/**
* @brief A structure containing details about the audio device.
*/
typedef struct AudioDetails {
	/** @brief The sample rate of the device */
	u32 SampleRate;
	/** @brief The channel count of the device */
	u32 ChannelCount;
} AudioDetails;

/**
 * @brief A generic "interface" for the backend. The audio backend
 * is what is responsible for making calls to the audio API such as
 * XAudio2 or AVFoundation. Each of these should implement this interface.
 * The frontend only interacts via this structure and has no knowledge of
 * the way things actually work on the backend.
 */
typedef struct AudioBackend {
	AudioBackendAPI API;
	AudioDetails Details;
	
	/**
     * @brief Initializes the audio backend.
     *
     * @param backend A pointer to the generic backend interface.
     * @returns True if initialized successfully; otherwise false.
     */
    b8 (*Init)(struct AudioBackend* backend);
	
    /**
     * @brief Shuts the audio backend down.
     *
     * @param backend A pointer to the generic backend interface.
     */
    void (*Shutdown)(struct AudioBackend* backend);
	
	/**
* @brief Updates the audio backend.
*
* @param backend A pointer to the generic backend interface.
*/
	void (*Update)(struct AudioBackend* backend);
} AudioBackend;

#endif