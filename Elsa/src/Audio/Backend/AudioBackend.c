#include "AudioBackend.h"

#include <Platform/Platform.h>

#include "XAudio2/XAudio2Backend.h"
#include "AVFoundation/AVFoundationBackend.h"

b8 AudioBackendCreate(AudioBackendAPI api, AudioBackend* out_audio_backend)
{
	if (api == AUDIO_BACKEND_API_XAUDIO2) {
#if defined(ELSA_PLATFORM_WINDOWS)
		out_audio_backend->API = AUDIO_BACKEND_API_XAUDIO2;
        out_audio_backend->Init = XAudio2BackendInit;
        out_audio_backend->Shutdown = XAudio2BackendShutdown;
		out_audio_backend->Update = XAudio2BackendUpdate;
		return true;
#else
		return false;
#endif
	}
	if (api == AUDIO_BACKEND_API_AVFOUNDATION) {
#if defined(ELSA_PLATFORM_MACOS)
		out_audio_backend->API = AUDIO_BACKEND_API_AVFOUNDATION;
        out_audio_backend->Init = AVFoundationBackendInit;
        out_audio_backend->Shutdown = AVFoundationBackendShutdown;
		out_audio_backend->Update = AVFoundationBackendUpdate;
		return true;
#else
		return false;
#endif
	}
	
	return false;
}

void AudioBackendDestroy(AudioBackend* audio_backend)
{
	PlatformZeroMemory(audio_backend, sizeof(AudioBackend));
}