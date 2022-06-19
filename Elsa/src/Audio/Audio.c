#include "Audio.h"

#include <Containers/Darray.h>
#include <Core/Logger.h>
#include <Platform/Platform.h>

#define MINIAUDIO_IMPLEMENTATION
#include <miniaudio/miniaudio.h>

#define SAMPLE_FORMAT ma_format_s16
#define CHANNEL_COUNT 2
#define SAMPLE_RATE 48000
#define MAX_AUDIO_CLIPS 1024

typedef struct AudioClip {
    ma_decoder Decoder;
    ma_decoder_config DecoderConfig;

    b8 Playing;
    b8 Looping;

    f32 Volume;

    u32 ID;

    drwav Wav;
} AudioClip;

typedef struct AudioContext {
    ma_device Device;
    ma_device_config DeviceConfig;

    AudioClip* Clips[MAX_AUDIO_CLIPS];
    u32 ClipCount;
} AudioContext;

static AudioContext state;

void DataCallback(ma_device* pDevice, void* pOutput, const void* pInput, ma_uint32 frameCount)
{
    for (i32 i = 0; i < state.ClipCount; i++) {
        if (pDevice->playback.format == SAMPLE_FORMAT) {
            drwav_read_pcm_frames_s16(&state.Clips[i]->Wav, frameCount, (drwav_int16*)pOutput);
            ma_apply_volume_factor_pcm_frames_s16((drwav_int16*)pOutput, frameCount, CHANNEL_COUNT, state.Clips[i]->Volume);
        } else if (pDevice->playback.format == ma_format_f32) {
            drwav_read_pcm_frames_f32(&state.Clips[i]->Wav, frameCount, (f32*)pOutput);
            ma_apply_volume_factor_pcm_frames_f32((f32*)pOutput, frameCount, CHANNEL_COUNT, state.Clips[i]->Volume);
        } else {
            ELSA_WARN("Unsupported audio format!");
        }
    }

    (void)pInput;
}

void AudioInit()
{
    state.DeviceConfig = ma_device_config_init(ma_device_type_playback);
    state.DeviceConfig.playback.format = SAMPLE_FORMAT;
    state.DeviceConfig.playback.channels = CHANNEL_COUNT;
    state.DeviceConfig.sampleRate = SAMPLE_RATE;
    state.DeviceConfig.dataCallback = DataCallback;
    state.DeviceConfig.pUserData = NULL;

    ma_device_init(NULL, &state.DeviceConfig, &state.Device);
    ma_device_start(&state.Device);
}

void AudioExit()
{
    ma_device_stop(&state.Device);
    ma_device_uninit(&state.Device);
}

void AudioUpdate()
{
    for (i32 i = 0; i < state.ClipCount; i++) {
        AudioClip* clip = state.Clips[i];

        if (!clip->Playing) {
            AudioStopClip(clip);
            if (clip->Looping) {
                AudioPlayClip(clip);
            }
        }
    }
}

AudioClip* AudioLoadClip(const char* path)
{
    AudioClip* out = PlatformAlloc(sizeof(AudioClip));

    if (!drwav_init_file(&out->Wav, path, NULL))
        ELSA_FATAL("Failed to load audio clip from path: %s", path);
    out->Volume = 1.0f;

    return out;
}

void AudioFreeClip(AudioClip* clip)
{
    if (clip->Playing) {
        AudioStopClip(clip);
    }

    ma_decoder_uninit(&clip->Decoder);
    drwav_uninit(&clip->Wav);

    PlatformFree(clip);
}

void AudioPlayClip(AudioClip* clip)
{
    for (i32 i = 0; i < state.ClipCount; i++) {
        if (state.Clips[i] == clip) {
            AudioStopClip(state.Clips[i]);
            break;
        }
    }

    ma_decoder_seek_to_pcm_frame(&clip->Decoder, 0);

    clip->Playing = 1;
    state.Clips[state.ClipCount] = clip;
    clip->ID = state.ClipCount++;
}

void AudioStopClip(AudioClip* clip)
{
    clip->Playing = 0;

    state.Clips[clip->ID] = state.Clips[state.ClipCount - 1];
    state.Clips[clip->ID]->ID = clip->ID;
    state.ClipCount--;
}

void AudioLoopClip(AudioClip* clip, b8 loop)
{
    clip->Looping = loop;
}

void AudioSetClipVolume(AudioClip* clip, f32 volume)
{
    clip->Volume = volume;
}