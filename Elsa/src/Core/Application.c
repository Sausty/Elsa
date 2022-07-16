#include "Application.h"

#include <Core/Event.h>
#include <Core/Logger.h>
#include <Core/MemTracker.h>
#include <Audio/AudioFrontend.h>
#include <Platform/Platform.h>
#include <Renderer/RendererFrontend.h>

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
            RendererFrontendResized(width, height);
        }
    }
	
    return false;
}

b8 ApplicationOnControllerConnect(u16 code, void* sender, void* listener, Event event)
{
    ELSA_INFO("Controller Connected at port %u", event.data.u16[0]);
	
    return false;
}

b8 ApplicationOnControllerDisconnect(u16 code, void* sender, void* listener, Event event)
{
    ELSA_INFO("Controller disconnected at port %u", event.data.u16[0]);
	
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
	
	if (!MemoryTrackerInit()) {
		ELSA_FATAL("MemoryTrackerInit failed. Shutting down...");
		return false;
	}
    if (!PlatformInit(&app_state)) {
        ELSA_FATAL("PlatformInit failed. Shutting down...");
        return false;
    }
    if (!AudioFrontendInit()) {
        ELSA_FATAL("AudioFrontendInit failed. Shutting down...");
        return false;
    }
    if (!RendererFrontendInit(app_state.Name)) {
        ELSA_FATAL("RendererFrontendInit failed. Shutting down...");
        return false;
    }
	
    if (!app_state.game->Init(app_state.game)) {
        ELSA_FATAL("Game failed to initialize.");
        return false;
    }
	
	EventRegister(EVENT_CODE_APPLICATION_QUIT, 0, ApplicationOnEvent);
    EventRegister(EVENT_CODE_RESIZED, 0, ApplicationOnResize);
    EventRegister(EVENT_CODE_GAMEPAD_CONNECTED, 0, ApplicationOnControllerConnect);
    EventRegister(EVENT_CODE_GAMEPAD_DISCONNECTED, 0, ApplicationOnControllerDisconnect);
	
    return true;
}

b8 ApplicationRun()
{
    app_state.Running = true;
	
    while (app_state.Running) {
        if (!PlatformPumpMessages()) {
            app_state.Running = false;
        }
		
        PlatformUpdateGamepads();
		AudioFrontendUpdate();
		
        if (!app_state.game->Update(app_state.game)) {
            ELSA_ERROR("app_state.game->Update failed.");
            return false;
        }

        if (!RendererFrontendBeginFrame(1.0f)) {
            ELSA_ERROR("RendererFrontendBeginFrame failed.");
            return false;
        }

        if (!app_state.game->Render(app_state.game)) {
            ELSA_ERROR("app_state.game->Render failed.");
            return false;
        }

        if (!RendererFrontendEndFrame(1.0f)) {
            ELSA_ERROR("RendererFrontendEndFrame failed.");
            return false;
        }
    }
	
    if (!app_state.game->Free(app_state.game))
        ELSA_ERROR("Game failed to terminate.");
	
    app_state.Running = false;
	
    EventUnregister(EVENT_CODE_GAMEPAD_CONNECTED, 0, ApplicationOnControllerConnect);
    EventUnregister(EVENT_CODE_GAMEPAD_DISCONNECTED, 0, ApplicationOnControllerDisconnect);
    EventUnregister(EVENT_CODE_RESIZED, 0, ApplicationOnResize);
    EventUnregister(EVENT_CODE_APPLICATION_QUIT, 0, ApplicationOnEvent);
	
    RendererFrontendShutdown();
    AudioFrontendShutdown();
    PlatformExit();
	MemoryTrackerShutdown();
	
    return true;
}