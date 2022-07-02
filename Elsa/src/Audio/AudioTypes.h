/**
 * @file AudioTypes.h
 * @author Milo Heinrich (MikuoH15TH@gmail.com)
 * @brief This file contains type definitions regarding frontend audio data.
 * @version 1.0
 * @date 2022-07-02
 */
#ifndef ELSA_AUDIO_TYPES_H
#define ELSA_AUDIO_TYPES_H

#include <Defines.h>
#include <Math/Math.h>

/** @brief A structure representing an audio source in space. */
typedef struct AudioSource {
	/** @brief Whether or not the audio source should loop when it's finished. */
	b8 Looping;
	/** @brief The volume of the audio source. Ranges from 0.0f to 1.0f. */
	f32 Volume;
	
	/** @brief The position of the audio source in space. */
	v3f Position;
	/** @brief The velocity of the audio source in space. */
	v3f Velocity;
} AudioSource;

/** @brief A structure representing an audio listener. Only one listener is required per scene. */
typedef struct AudioListener {
	/** @brief The position of the listener. */
	v3f Position;
	/** @brief The velocity of the listener. */
	v3f Velocity;
	/** @brief The front orientation of the listener. */
	v3f OrientationFront;
	/** @brief The top orientation of the listener. */
	v3f OrientationTop;
} AudioListener;

#endif
