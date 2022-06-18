#include "App.h"

#include <EntryPoint.h>

b8 CreateGame(Game* out_game, int argc, char** argv)
{
    out_game->AppConfig.PosX = 100;
    out_game->AppConfig.PosY = 100;
    out_game->AppConfig.Width = 1280;
    out_game->AppConfig.Height = 720;
    out_game->AppConfig.Name = "Elsa Application";
    out_game->Init = GameInit;
    out_game->Render = GameRender;
    out_game->Update = GameUpdate;
    out_game->OnResize = GameResize;

    return true;
}