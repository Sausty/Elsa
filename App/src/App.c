#include "App.h"

#include <Core/Logger.h>
#include <Core/Event.h>
#include <Core/Input.h>
#include <Audio/Audio.h>

typedef struct AppData {
    AudioClip* BGM;
} AppData;

static AppData app;

b8 GameInit(Game* game)
{
    app.BGM = AudioLoadClip("Assets/Audio/SyncamoreTheme.wav");
    AudioSetClipVolume(app.BGM, 0.3f);
    AudioLoopClip(app.BGM, true);
    AudioPlayClip(app.BGM);

    ELSA_DEBUG("GameInit() called");

    return true;
}

b8 GameFree(Game* game)
{
    AudioFreeClip(app.BGM);

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