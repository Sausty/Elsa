/**
 * @file RendererBackend.h
 * @author Milo Heinrich (MikuoH15TH@gmail.com)
 * @brief Hosts creation and destruction methods for the renderer backend.
 * @version 1.0
 * @date 2022-06-26
 */
#ifndef ELSA_RENDERER_BACKEND_H
#define ELSA_RENDERER_BACKEND_H

#include <Defines.h>
#include <Renderer/RendererTypes.h>

/**
 * @brief Creates a new renderer backend of the given type.
 * 
 * @param type The type of backend to create (e.g. Vulkan, OpenGL, DirectX)
 * @param out_renderer_backend A pointer to hold the newly-created renderer backend.
 * @return True if successful; otherwise false.
 */
ELSA_API b8 RendererBackendCreate(RendererBackendAPI api, RendererBackend* out_renderer_backend);

/**
 * @brief Destroys the given renderer backend.
 * 
 * @param renderer_backend A pointer to the backend to be destroyed.
 */
ELSA_API void RendererBackendDestroy(RendererBackend* renderer_backend);

#endif