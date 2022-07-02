extern "C" {
#include "XAudio2Backend.h"
#include <Core/Logger.h>
}

#if defined(ELSA_PLATFORM_WINDOWS)

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <XAudio2.h>
#include <x3daudio.h>

#define AUDIO_CHANNELS XAUDIO2_DEFAULT_CHANNELS
#define AUDIO_SAMPLE_RATE XAUDIO2_DEFAULT_SAMPLERATE

typedef struct XAudio2State {
	IXAudio2* Device;
	IXAudio2MasteringVoice* MasterVoice;
	X3DAUDIO_HANDLE X3DInstance;
} XAudio2State;

static XAudio2State state;

b8 XAudio2BackendInit(AudioBackend* backend)
{
	HRESULT hr = CoInitializeEx(NULL, COINIT_MULTITHREADED);
	if (FAILED(hr)) {
		ELSA_ERROR("Failed to initialize COM. Shutting down...");
		return false;
	}
	
	// Create XAudio2
	hr = XAudio2Create(&state.Device, 0, XAUDIO2_DEFAULT_PROCESSOR);
	if (FAILED(hr)) {
		ELSA_ERROR("XAudio2Create failed.");
		return false;
	}
	
	// Create Mastering Voice
	hr = state.Device->CreateMasteringVoice(&state.MasterVoice, AUDIO_CHANNELS, AUDIO_SAMPLE_RATE, 0, NULL, NULL, AudioCategory_GameMedia);
	if (FAILED(hr)) {
		ELSA_ERROR("Failed to create XAudio2 mastering voice!");
		return false;
	}
	
	// Initialize X3DAUDIO_HANDLE
	DWORD dwChannelMask;
	state.MasterVoice->GetChannelMask(&dwChannelMask);
	
	hr = X3DAudioInitialize(dwChannelMask, X3DAUDIO_SPEED_OF_SOUND, state.X3DInstance);
	if (FAILED(hr)) {
		ELSA_ERROR("Failed to initialize X3DAudio.");
		return false;
	}
	
	return true;
}

void XAudio2BackendShutdown(AudioBackend* backend)
{
	state.MasterVoice->DestroyVoice();
	state.Device->Release();
}

void XAudio2BackendUpdate(AudioBackend* backend)
{
	
}

#endif