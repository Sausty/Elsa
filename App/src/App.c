#include "App.h"

#include <Core/Logger.h>
#include <Core/Event.h>
#include <Core/Input.h>
#include <Platform/Platform.h>
#include <Containers/Darray.h>
#include <Audio/AudioSource.h>
#include <Renderer/ShaderCompiler.h>

typedef struct AppData {
    AudioSource TestSource;
	
	ShaderModule TestVertex;
	ShaderModule TestFragment;
} AppData;

static AppData app;

b8 GameInit(Game* game)
{
	AudioSourceCreate(&app.TestSource);
	AudioSourceLoad("Assets/Audio/SyncamoreTheme.wav", &app.TestSource);
	AudioSourceSetVolume(1.0f, &app.TestSource);
	AudioSourceSetPitch(1.0f, &app.TestSource);
	AudioSourcePlay(&app.TestSource);
	
	char** filenames = Darray_Create(char*);
	PlatformGetDirectoryFiles("Assets/Shaders/Basic/*", &filenames);
	for (u32 i = 0; i < Darray_Length(filenames); i++) {
		ELSA_INFO("%s", filenames[i]);
		PlatformFree(filenames[i]);
	}
	Darray_Destroy(filenames);
	
	if (!ShaderCompile("Assets/Shaders/Basic/Vertex.vert", &app.TestVertex)) {
		ELSA_ERROR("Failed to compile vertex shader!");
		return false;
	}
	if (!ShaderCompile("Assets/Shaders/Basic/Fragment.frag", &app.TestFragment)) {
		ELSA_ERROR("Failed to compile fragment shader!");
		return false;
	}
	
	return true;
}

b8 GameFree(Game* game)
{
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