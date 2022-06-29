#include "Audio.h"

#include <Containers/Darray.h>
#include <Core/Logger.h>
#include <Platform/Platform.h>

typedef struct AudioClip {
    
} AudioClip;

b8 AudioInit()
{
    
    return true; 
}  

void AudioExit()
{
    
}

void AudioUpdate()
{
    
}

AudioClip* AudioLoadClip(const char* path)
{
    AudioClip* out = PlatformAlloc(sizeof(AudioClip));
    PlatformZeroMemory(out, sizeof(AudioClip));
	
    
	
    return out;
}

void AudioFreeClip(AudioClip* clip)
{
    PlatformFree(clip);
}

void AudioPlayClip(AudioClip* clip)
{
    
}

void AudioStopClip(AudioClip* clip)
{
    
}

void AudioLoopClip(AudioClip* clip, b8 loop)
{
    
}

void AudioSetClipVolume(AudioClip* clip, f32 volume)
{
    
}