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
    ELSA_DEBUG("GameInit() called");

    app.BGM = AudioLoadClip("Assets/Audio/SyncamoreTheme.wav");
    AudioSetClipVolume(app.BGM, 0.3f);
    AudioLoopClip(app.BGM, true);
    AudioPlayClip(app.BGM);

    return true;
}

b8 GameFree(Game* game)
{
    AudioFreeClip(app.BGM);

    return true;
}

b8 GameUpdate(Game* game)
{
    if (InputIsGamepadButtonPressed(0, GAMEPAD_A))
        ELSA_INFO("Controller 0: Gamepad A");
    if (InputIsGamepadButtonPressed(0, GAMEPAD_B))
        ELSA_INFO("Controller 0: Gamepad B");
    if (InputIsGamepadButtonPressed(0, GAMEPAD_X))
        ELSA_INFO("Controller 0: Gamepad X");
    if (InputIsGamepadButtonPressed(0, GAMEPAD_Y))
        ELSA_INFO("Controller 0: Gamepad Y");

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