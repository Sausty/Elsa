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

/** @brief Represents a game instance, with all it's function pointers. **/
typedef struct Game {
    struct {
        /** @brief The X position of the window. */
        i16 PosX;
        /** @brief The Y position of the window. */
        i16 PosY;
        /** @brief The width of the window. */
        i32 Width;
        /** @brief The height of the window. */
        i32 Height;
        /** @brief The title position of the window. */
        const char* Name;
    } AppConfig;

    /** @brief Called once at the beginning of the application. */
    b8 (*Init)(struct Game* game);
    /** @brief Called once at the end of the application. */
    b8 (*Free)(struct Game* game);
    /** @brief Called once every frame. */
    b8 (*Update)(struct Game* game);
    /** @brief Called once every frame after update. */
    b8 (*Render)(struct Game* game);
    /** @brief Called when the game window is resized. */
    void (*OnResize)(struct Game* game, u32 width, u32 height);
} Game;

/** @brief Represents the overall state of an Elsa application. */
typedef struct ApplicationState {
    /** @brief The game instance. */
    Game* game;

    /** @brief The X position of the window. */
    i16 PosX;
    /** @brief The Y position of the window. */
    i16 PosY;
    /** @brief The width of the window. */
    i32 Width;
    /** @brief The height of the window. */
    i32 Height;
    /** @brief The title of the window. */
    const char* Name;

    /** @brief Whether or not the application is running. */
    b8 Running;
} ApplicationState;

#endif