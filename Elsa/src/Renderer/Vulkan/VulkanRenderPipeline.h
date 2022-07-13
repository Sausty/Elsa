/**
 * @file RendererTypes.h
 * @author Milo Heinrich (MikuoH15TH@gmail.com)
 * @brief This file contains type definitions regarding renderer data.
 * @version 1.0
 * @date 2022-07-13
 */
#ifndef ELSA_VULKAN_RENDER_PIPELINE_H
#define ELSA_VULKAN_RENDER_PIPELINE_H

#include "VulkanTypes.h"

b8 VulkanRenderPipelineCreate(VulkanContext* context, ShaderPack* pack, RenderPipeline* pipeline);
void VulkanRenderPipelineDestroy(VulkanContext* context, RenderPipeline* pipeline);

#endif