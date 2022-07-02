extern "C" {
#include "XAudio2Backend.h"
#include <Audio/AudioSource.h>
#include <Core/Logger.h>
#include <Core/MemTracker.h>
}

#if defined(ELSA_PLATFORM_WINDOWS)

/*
TODO(milo): Load audio files and play them

TODO(milo): Loop and volume modifiers

TODO(milo): Sound effects (high pass, low pass, reverb)

TODO(milo): 3D spatialized audio (badass)
*/

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <XAudio2.h>
#include <x3daudio.h>

#define AUDIO_CHANNELS XAUDIO2_DEFAULT_CHANNELS
#define AUDIO_SAMPLE_RATE XAUDIO2_DEFAULT_SAMPLERATE

typedef HRESULT (WINAPI* PFN_XAUDIO2_CREATE)(IXAudio2** ppXAudio2, UINT32 Flags, XAUDIO2_PROCESSOR XAudio2Processor);
typedef HRESULT (WINAPI* PFN_X3DAUDIO_INITIALIZE)(UINT32 SpeakerChannelMask, FLOAT32 SpeedOfSound, X3DAUDIO_HANDLE Instance);

using namespace DirectX;

typedef struct XAudio2State {
	HMODULE XAudioLib;
	
	IXAudio2* Device;
	IXAudio2MasteringVoice* MasterVoice;
	X3DAUDIO_HANDLE X3DInstance;
	
	u32 SampleRate;
	u32 ChannelCount;
} XAudio2State;

typedef struct XAudio2Source {
	IXAudio2SourceVoice* SourceVoice;
	X3DAUDIO_EMITTER AudioEmitter;
} XAudio2Source;

static XAudio2State state;

PFN_XAUDIO2_CREATE XAudio2CreateProc;
PFN_X3DAUDIO_INITIALIZE X3DAudioInitializeProc;

b8 XAudio2BackendInit(AudioBackend* backend)
{
	HRESULT hr = CoInitializeEx(NULL, COINIT_MULTITHREADED);
	if (FAILED(hr)) {
		ELSA_ERROR("Failed to initialize COM. Shutting down...");
		return false;
	}
	
	// Load XAudio2
	state.XAudioLib = LoadLibraryA("xaudio2_9.dll");
	if (!state.XAudioLib) {
		ELSA_ERROR("Failed to load XAudio dll!");
		return false;
	}
	XAudio2CreateProc = (PFN_XAUDIO2_CREATE)GetProcAddress(state.XAudioLib, "XAudio2Create");
	if (!XAudio2CreateProc) {
		ELSA_ERROR("Failed to load XAudio2Create!");
		return false;
	}
	X3DAudioInitializeProc = (PFN_X3DAUDIO_INITIALIZE)GetProcAddress(state.XAudioLib, "X3DAudioInitialize");
	if (!X3DAudioInitializeProc) {
		ELSA_ERROR("Failed to load X3DAudioInitialize!");
		return false;
	}
	
	u32 flags = 0;
#if defined(_DEBUG)
	flags |= XAUDIO2_DEBUG_ENGINE;
#endif
	
	// Create XAudio2
	hr = XAudio2CreateProc(&state.Device, flags, XAUDIO2_DEFAULT_PROCESSOR);
	if (FAILED(hr)) {
		ELSA_ERROR("XAudio2Create failed.");
		return false;
	}
	
#if defined(_DEBUG)
	XAUDIO2_DEBUG_CONFIGURATION debug_config = {};
	debug_config.TraceMask = XAUDIO2_LOG_ERRORS | XAUDIO2_LOG_WARNINGS;
	debug_config.BreakMask = XAUDIO2_LOG_ERRORS;
	state.Device->SetDebugConfiguration(&debug_config, 0);
#endif
	
	// Create Mastering Voice
	hr = state.Device->CreateMasteringVoice(&state.MasterVoice, AUDIO_CHANNELS, AUDIO_SAMPLE_RATE, 0, NULL, NULL, AudioCategory_GameMedia);
	if (FAILED(hr)) {
		ELSA_ERROR("Failed to create XAudio2 mastering voice!");
		return false;
	}
	
	// Initialize X3DAUDIO_HANDLE
	DWORD dwChannelMask;
	state.MasterVoice->GetChannelMask(&dwChannelMask);
	
	XAUDIO2_VOICE_DETAILS details;
	state.MasterVoice->GetVoiceDetails(&details);
	
	backend->Details.SampleRate = details.InputSampleRate;
	backend->Details.ChannelCount = details.InputChannels;
	state.SampleRate = details.InputSampleRate;
	state.ChannelCount = details.InputChannels;
	
	hr = X3DAudioInitializeProc(dwChannelMask, X3DAUDIO_SPEED_OF_SOUND, state.X3DInstance);
	if (FAILED(hr)) {
		ELSA_ERROR("Failed to initialize X3DAudio.");
		return false;
	}
	
	// Launch message
	ELSA_INFO("<XAudio2BackendInit> Using audio device with sample rate of %d and channel count of %d", details.InputSampleRate, details.InputChannels);
	
	return true;
}

void XAudio2BackendShutdown(AudioBackend* backend)
{
	state.MasterVoice->DestroyVoice();
	state.Device->StopEngine();
	state.Device->Release();
	
	FreeLibrary(state.XAudioLib);
	CoUninitialize();
}

void XAudio2BackendUpdate(AudioBackend* backend)
{
	
}

b8 AudioSourceCreate(AudioSource* out_source)
{
	out_source->Looping = false;
	out_source->Volume = 1.0f;
	
	out_source->Position = V3Zero();
	out_source->Velocity = V3Zero();
	
	out_source->BackendData = MemoryTrackerAlloc(sizeof(XAudio2Source), MEMORY_TAG_AUDIO);
	XAudio2Source* source = (XAudio2Source*)out_source->BackendData;
	
	// Wave format
	WAVEFORMATEX wave_format = {};
	wave_format.wFormatTag = WAVE_FORMAT_PCM; // PCM audio format
	wave_format.wBitsPerSample = 16; // s16
	wave_format.nChannels = state.ChannelCount; // 2 channels commonly
	wave_format.nSamplesPerSec = state.SampleRate; // 48khz or 48000 sample rate commonly
	wave_format.nAvgBytesPerSec = (wave_format.wBitsPerSample * wave_format.nSamplesPerSec * wave_format.nChannels) / 8;
	wave_format.nBlockAlign = (wave_format.nChannels * wave_format.wBitsPerSample) / 8; // 4 bytes commonly
	wave_format.cbSize = 0;
	
	HRESULT hr = state.Device->CreateSourceVoice(&source->SourceVoice, (WAVEFORMATEX*)&wave_format, XAUDIO2_VOICE_USEFILTER, 1.0, NULL, NULL, NULL);
	if (FAILED(hr))
		return false;
	
	// Emitter
	source->AudioEmitter.Position = XMFLOAT3(out_source->Position.x, out_source->Position.y, out_source->Position.z);
	source->AudioEmitter.Velocity = XMFLOAT3(out_source->Velocity.x, out_source->Velocity.y, out_source->Velocity.z);
	
	return true;
}

void AudioSourceDestroy(AudioSource* source)
{
	XAudio2Source* backend = (XAudio2Source*)source->BackendData;
	if (backend->SourceVoice)
		backend->SourceVoice->DestroyVoice();
	
	MemoryTrackerFree(source->BackendData, sizeof(XAudio2Source), MEMORY_TAG_AUDIO);
}

#endif