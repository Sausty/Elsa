/**
 * @file MetalBackend.h
 * @author Milo Heinrich (MikuoH15TH@gmail.com)
 * @brief This file contains the Metal implementation of the renderer backend.
 * All Metal calls are made behind this facade to keep the rest of the engine
 * unaware about the inner workings of Metal.
 * @version 1.0
 * @date 2022-06-26
 */
#ifndef ELSA_METAL_BACKEND_H
#define ELSA_METAL_BACKEND_H

#include <Defines.h>
#include <Renderer/RendererTypes.h>

b8 MetalRendererBackendInit(RendererBackend* backend);
void MetalRendererBackendShutdown(RendererBackend* backend);
void MetalRendererBackendResized(RendererBackend* backend, u16 width, u16 height);
b8 MetalRendererBackendBeginFrame(RendererBackend* backend, f32 delta_time);
b8 MetalRendererBackendEndFrame(RendererBackend* backend, f32 delta_time);

#endif