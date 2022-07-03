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
	AudioSourceCreate(&app.TestSource);
	AudioSourceLoad("Assets/Audio/SyncamoreTheme.wav", &app.TestSource);
	AudioSourceSetVolume(0.3f, &app.TestSource);
	AudioSourcePlay(&app.TestSource);
	
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