/**
 * @file Application.h
 * @author Milo Heinrich (MikuoH15TH@gmail.com)
 * @brief This file contains structures and logic pertaining to the
 * overall engine application itself. 
 * The application is responsible for managing both the platform layers
 * as well as all systems within the engine.
 * @version 1.0
 * @date 2022-06-17
 */
#ifndef ELSA_APPLICATION_H
#define ELSA_APPLICATION_H

#include <ApplicationTypes.h>

struct Game;

/**
 * @brief Creates the application, standing up the platform layer and all
 * underlying subsystems.
 * @param game A pointer to the game instance associated with the application
 * @returns True on success; otherwise false.
 */
ELSA_API b8 ApplicationCreate(struct Game* game);

/**
 * @brief Starts the main application loop.
 * @returns True on success; otherwise false.
 */
ELSA_API b8 ApplicationRun();


#endif