#include "AudioFrontend.h"

#include <Audio/Backend/AudioBackend.h>

#include <Core/Logger.h>

typedef struct AudioFrontend {
	AudioBackend Backend;
} AudioFrontend;

static AudioFrontend Frontend;

b8 AudioFrontendInit()
{
#if defined(ELSA_PLATFORM_WINDOWS)
	if (!AudioBackendCreate(AUDIO_BACKEND_API_XAUDIO2, &Frontend.Backend)) {
		ELSA_ERROR("AudioBackendCreate <AUDIO_BACKEND_API_XAUDIO2> failed. Shutting down...");
		return false;
	}
#elif defined(ELSA_PLATFORM_MACOS)
	if (!AudioBackendCreate(AUDIO_BACKEND_API_AVFOUNDATION, &Frontend.Backend)) {
		ELSA_ERROR("AudioBackendCreate <AUDIO_BACKEND_API_AVFOUNDATION> failed. Shutting down...");
		return false;
	}
#endif
	
	if (!Frontend.Backend.Init(&Frontend.Backend))
		ELSA_FATAL("Failed to initialize audio backend...");
	
	return true;
}

void AudioFrontendShutdown()
{
	Frontend.Backend.Shutdown(&Frontend.Backend);
}

void AudioFrontendUpdate()
{
	Frontend.Backend.Update(&Frontend.Backend);
}