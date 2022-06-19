#ifndef APP_H
#define APP_H

#include <Defines.h>
#include <ApplicationTypes.h>

b8 GameInit(Game* game);
b8 GameFree(Game* game);
b8 GameUpdate(Game* game);
b8 GameRender(Game* game);
void GameResize(Game* game, u32 width, u32 height);

#endif