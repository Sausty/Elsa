/**
 * @file ApplicationTypes.h
 * @author Milo Heinrich (MikuoH15TH@gmail.com)
 * @brief This file contains type definitions regarding application data.
 * @version 1.0
 * @date 2022-06-17
 */

#ifndef ELSA_APPLICATION_TYPES_H
#define ELSA_APPLICATION_TYPES_H

#include <Defines.h>

typedef struct Game {
    struct {
        i16 PosX;
        i16 PosY;
        i32 Width;
        i32 Height;
        const char* Name;
    } AppConfig;

    b8 (*Init)(struct Game* game);
    b8 (*Free)(struct Game* game);
    b8 (*Update)(struct Game* game);
    b8 (*Render)(struct Game* game);
    void (*OnResize)(struct Game* game, u32 width, u32 height);
} Game;

typedef struct ApplicationState {
    Game* game;

    i16 PosX;
    i16 PosY;
    i32 Width;
    i32 Height;
    const char* Name;

    b8 Running;
} ApplicationState;

#endif