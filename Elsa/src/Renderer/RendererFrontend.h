/**
 * @file RendererFrontend.h
 * @author Milo Heinrich (MikuoH15TH@gmail.com)
 * @brief The renderer frontend, which is the only thing the rest of the engine sees.
 * This is responsible for transferring any data to and from the renderer backend
 * in an agnostic way.
 * @version 1.0
 * @date 2022-06-26
 */
#ifndef ELSA_RENDERER_FRONTEND_H
#define ELSA_RENDERER_FRONTEND_H

#include <Defines.h>
#include <Renderer/RendererTypes.h>

/**
 * @brief Initializes the renderer frontend.
 * 
 * @param application_name The name of the application.
 * @returns True on success; otherwise false.
 */
ELSA_API b8 RendererFrontendInit(const char* application_name);

/**
 * @brief Shuts the renderer frontend down.
 */
ELSA_API void RendererFrontendShutdown();

/**
 * @brief Handles resize events.
 * 
 * @param width The new window width.
 * @param height The new window height.
 */
ELSA_API void RendererFrontendResized(u16 width, u16 height);

/**
 * @brief Draws the frame.
 * 
 * @param delta_time The number of seconds past after the last drawn frame.
 * @returns True on success; otherwise false.
 */
ELSA_API b8 RendererFrontendDrawFrame(f32 delta_time);

#endif