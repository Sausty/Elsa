#include "App.h"

#include <Core/Logger.h>
#include <Core/Event.h>
#include <Core/Input.h>

typedef struct AppData {
    
} AppData;

static AppData app;

b8 GameInit(Game* game)
{
    ELSA_DEBUG("GameInit() called");
	
    return true;
}

b8 GameFree(Game* game)
{
	
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