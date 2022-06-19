#include "Application.h"

#include <Core/Event.h>
#include <Core/Logger.h>
#include <Platform/Platform.h>

static ApplicationState app_state;

b8 ApplicationOnEvent(u16 code, void* sender, void* listener, Event event)
{
    switch (code) {
        case EVENT_CODE_APPLICATION_QUIT: {
            ELSA_INFO("EVENT_CODE_APPLICATION_QUIT received, shutting down.\n");
            app_state.Running = false;
            return true;
        }
    }

    return false;
}

b8 ApplicationOnKey(u16 code, void* sender, void* listene, Event event)
{
    return false;
}

b8 ApplicationOnResize(u16 code, void* sender, void* listener, Event event)
{
    if (code == EVENT_CODE_RESIZED) {
        u16 width = event.data.u16[0];
        u16 height = event.data.u16[1];

        if (width != app_state.Width || height != app_state.Height) {
            app_state.Width = width;
            app_state.Height = height;

            ELSA_DEBUG("Window Resized: %i, %i", width, height);

            app_state.game->OnResize(app_state.game, width, height);
        }
    }

    return false;
}

b8 ApplicationCreate(struct Game* game)
{
    app_state.game = game;
    app_state.Running = false;
    app_state.PosX = game->AppConfig.PosX;
    app_state.PosY = game->AppConfig.PosY;
    app_state.Width = game->AppConfig.Width;
    app_state.Height = game->AppConfig.Height;
    app_state.Name = game->AppConfig.Name;

    EventRegister(EVENT_CODE_APPLICATION_QUIT, 0, ApplicationOnEvent);
    EventRegister(EVENT_CODE_RESIZED, 0, ApplicationOnResize);
    EventRegister(EVENT_CODE_KEY_PRESSED, 0, ApplicationOnKey);
    EventRegister(EVENT_CODE_KEY_RELEASED, 0, ApplicationOnKey);

    PlatformInit(&app_state);

    if (!app_state.game->Init(app_state.game)) {
        ELSA_FATAL("Game failed to initialize.");
        return false;
    }

    return true;
}

b8 ApplicationRun()
{
    app_state.Running = true;

    while (app_state.Running) {
        if (!PlatformPumpMessages()) {
            app_state.Running = false;
        }

        app_state.game->Update(app_state.game);
        app_state.game->Render(app_state.game);
    }

    app_state.Running = false;

    EventUnregister(EVENT_CODE_RESIZED, 0, ApplicationOnResize);
    EventUnregister(EVENT_CODE_APPLICATION_QUIT, 0, ApplicationOnEvent);
    EventUnregister(EVENT_CODE_KEY_PRESSED, 0, ApplicationOnKey);
    EventUnregister(EVENT_CODE_KEY_RELEASED, 0, ApplicationOnKey);

    return true;
}