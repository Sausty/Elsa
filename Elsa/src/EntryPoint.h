/**
 * @file EntryPoint.h
 * @author Milo Heinrich (MikuoH15TH@gmail.com)
 * @brief This file contains the main entry point to the application. 
 * It also contains a reference to an externally defined CreateGame
 * method, which should create and set a custom game object to the
 * location pointed to by out_game. This would be provided by the
 * consuming application, which is then hooked into the engine itself
 * during the bootstrapping phase.
 * @version 1.0
 * @date 2022-06-17
 */
#ifndef ELSA_ENTRY_POINT_H
#define ELSA_ENTRY_POINT_H

#include <ApplicationTypes.h>
#include <Core/Logger.h>
#include <Core/Application.h>

extern b8 CreateGame(Game* game, int argc, char** argv);

int main(i32 argc, char** argv) {
    Game game;
    if (!CreateGame(&game, argc, argv)) {
        ELSA_FATAL("Could not create game!");
        return -1;
    }

    if (!game.Render || !game.Init || !game.OnResize || !game.Update) {
        ELSA_FATAL("Game's function pointers must be set!");
        return -2;
    }

    if (!ApplicationCreate(&game)) {
        ELSA_FATAL("Application failed to create.");
        return 1;
    }

    if (!ApplicationRun()) {
        ELSA_INFO("Application did not terminate correctly.");
        return 2;
    }

    return 0;
}

#endif