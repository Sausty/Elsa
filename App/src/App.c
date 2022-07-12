#include "App.h"

#include <Core/Logger.h>
#include <Core/Event.h>
#include <Core/Input.h>
#include <Audio/AudioSource.h>
#include <Renderer/ShaderCompiler.h>

typedef struct AppData {
    AudioSource TestSource;
	
	ShaderModule TestModule;
} AppData;

static AppData app;

b8 GameInit(Game* game)
{
	AudioSourceCreate(&app.TestSource);
	AudioSourceLoad("Assets/Audio/SyncamoreTheme.wav", &app.TestSource);
	AudioSourceSetVolume(1.0f, &app.TestSource);
	AudioSourceSetPitch(1.0f, &app.TestSource);
	AudioSourcePlay(&app.TestSource);
	
	if (!ShaderCompile("Assets/Shaders/Basic/Vertex.vert", &app.TestModule)) {
		ELSA_ERROR("Failed to compile shader!");
		return false;
	}
	
	return true;
}

b8 GameFree(Game* game)
{
	ShaderFree(&app.TestModule);
	AudioSourceStop(&app.TestSource);
	AudioSourceDestroy(&app.TestSource);
	
    return true;
}

b8 GameUpdate(Game* game)
{
	
    return true;
}

b8 GameRender(Game* game)
{
    return true;
}

void GameResize(Game* game, u32 width, u32 height)
{
    return;
}