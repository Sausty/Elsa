/**
 * @file VulkanBackend.h
 * @author Milo Heinrich (MikuoH15TH@gmail.com)
 * @brief This file contains the Vulkan implementation of the renderer backend.
 * All Vulkan calls are made behind this facade to keep the rest of the engine
 * unaware about the inner workings of Vulkan.
 * @version 1.0
 * @date 2022-06-26
 */
#ifndef ELSA_VULKAN_BACKEND_H
#define ELSA_VULKAN_BACKEND_H

#include <Defines.h>
#include <Renderer/RendererTypes.h>

b8 VulkanRendererBackendInit(RendererBackend* backend);
void VulkanRendererBackendShutdown(RendererBackend* backend);
void VulkanRendererBackendResized(RendererBackend* backend, u16 width, u16 height);
b8 VulkanRendererBackendBeginFrame(RendererBackend* backend, f32 delta_time);
b8 VulkanRendererBackendEndFrame(RendererBackend* backend, f32 delta_time);

#endif