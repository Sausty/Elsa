#include "App.h"

#include <Core/Logger.h>
#include <Core/Event.h>
#include <Core/Input.h>
#include <Platform/Platform.h>
#include <Containers/Darray.h>
#include <Audio/AudioSource.h>
#include <Renderer/ShaderCompiler.h>
#include <Renderer/RendererFrontend.h>

typedef struct AppData {
    AudioSource TestSource;
	
	ShaderPack TestPack;
	RenderPipeline TestPipeline;
} AppData;

static AppData app;

b8 GameInit(Game* game)
{
	AudioSourceCreate(&app.TestSource);
	AudioSourceLoad("Assets/Audio/SyncamoreTheme.wav", &app.TestSource);
	AudioSourceSetVolume(1.0f, &app.TestSource);
	AudioSourceSetPitch(1.0f, &app.TestSource);
	AudioSourcePlay(&app.TestSource);
	
	if (!ShaderPackCreate("Assets/Shaders/Basic", &app.TestPack)) {
		ELSA_FATAL("Failed to load shader pack!");
		return false;
	}
	if (!RendererFrontendRenderPipelineCreate(&app.TestPack, &app.TestPipeline)) {
		ELSA_FATAL("Failed to create render pipeline!");
		return false;
	}
	
	return true;
}

b8 GameFree(Game* game)
{
	RendererFrontendRenderPipelineDestroy(&app.TestPipeline);
	ShaderPackDestroy(&app.TestPack);
	
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