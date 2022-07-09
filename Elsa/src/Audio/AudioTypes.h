/**
 * @file AudioTypes.h
 * @author Milo Heinrich (MikuoH15TH@gmail.com)
 * @brief This file contains type definitions regarding frontend audio data.
 * @version 1.0
 * @date 2022-07-02
 */
#ifndef ELSA_AUDIO_FRONTEND_TYPES_H
#define ELSA_AUDIO_FRONTEND_TYPES_H

#include <Defines.h>
#include <Math/Math.h>

/** @brief Structure representing audio filter data. */
typedef struct AudioFilter {
	/** @brief The frequency of filter */
	f32 Frequency;
	/** @brief Reciprocal of Q factor */
	f32 OneOverQ;
} AudioFilter;

/** @brief A structure representing an audio source in space. */
typedef struct AudioSource {
	/** @brief Whether or not the audio source should loop when it's finished. */
	b8 Looping;
	/** @brief The volume of the audio source. Ranges from 0.0f to 1.0f. */
	f32 Volume;
	/** @brief The pitch of the audio source. Ranges from 1/1024 to 1024/1. */
	f32 Pitch;
	
	/** @brief Opaque structure holding all the audio filter data. */
	struct {
		AudioFilter LowPass;
		AudioFilter BandPass;
		AudioFilter HighPass;
		AudioFilter NotchPass;
	} Filters;
	
	/** @brief Opaque pointer that holds the backend data of the audio source. */
	void* BackendData;
} AudioSource;

#endif
