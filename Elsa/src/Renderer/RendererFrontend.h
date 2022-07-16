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
* @brief Creates a render pipeline.
*
* @param pack The shader pack to use.
* @param map The descriptor map to use.
* @param pipeline A pointer that will hold the created pipeline.
* @returns True on success; otherwise false.
*/
ELSA_API b8 RendererFrontendRenderPipelineCreate(ShaderPack* pack, DescriptorMap* map, RenderPipeline* pipeline);

/**
* @brief Destroys a render pipeline.
*
* @param pipeline The render pipeline to destroy.
*/
ELSA_API void RendererFrontendRenderPipelineDestroy(RenderPipeline* pipeline);

/**
 * @brief Creates a backend for the descriptor map.
 * @param pack The shader pack that the descriptor map will use.
 * @param map A pointer to hold the resulting descriptor map.
 * @returns True on success; otherwise false.
 */
ELSA_API b8 RendererFrontendDescriptorMapCreate(ShaderPack* pack, DescriptorMap* map);

/**
  * @brief Destroys a descriptor map.
  * @param map The descriptor map to destroy.
  */
ELSA_API void RendererFrontendDescriptorMapDestroy(DescriptorMap* map);

/**
 * @brief Draws the frame.
 * 
 * @param delta_time The number of seconds past after the last drawn frame.
 * @returns True on success; otherwise false.
 */
ELSA_API b8 RendererFrontendDrawFrame(f32 delta_time);

#endif