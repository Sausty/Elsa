#include "App.h"

#include <Core/Logger.h>
#include <Core/Event.h>
#include <Core/Input.h>
#include <Audio/AudioSource.h>

typedef struct AppData {
    AudioSource TestSource;
} AppData;

static AppData app;

b8 GameInit(Game* game)
{
	if (!AudioSourceCreate(&app.TestSource))
		ELSA_ERROR("Failed to create audio source!");
	
    return true;
}

b8 GameFree(Game* game)
{
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