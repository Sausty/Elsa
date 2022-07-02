#include "App.h"

#include <Defines.h>
#include <EntryPoint.h>

b8 CreateGame(Game* out_game, int argc, char** argv)
{
    out_game->AppConfig.PosX = 100;
    out_game->AppConfig.PosY = 100;
    out_game->AppConfig.Width = 1280;
    out_game->AppConfig.Height = 720;
#ifdef ELSA_PLATFORM_WINDOWS
	out_game->AppConfig.Name = "Elsa Engine | <VK> | <XAUDIO2>";
#elif ELSA_PLATFORM_MACOS
	out_game->AppConfig.Name = "Elsa Engine | <MTL> | <AVFOUNDATION>";
#endif
    out_game->Init = GameInit;
    out_game->Free = GameFree;
    out_game->Render = GameRender;
    out_game->Update = GameUpdate;
    out_game->OnResize = GameResize;
	
    return true;
}