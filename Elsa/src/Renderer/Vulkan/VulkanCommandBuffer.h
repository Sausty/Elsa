/**
 * @file VulkanCommandBuffer.h
 * @author Milo Heinrich (MikuoH15TH@gmail.com)
 * @brief This file contains the Vulkan implementation of a command buffer.
 * @version 1.0
 * @date 2022-07-11
 */
#ifndef ELSA_VULKAN_COMMAND_BUFFER_H
#define ELSA_VULKAN_COMMAND_BUFFER_H

#include "VulkanTypes.h"

void VulkanCommandBufferAlloc(VulkanContext* context, VkCommandPool pool, b8 is_primary, VulkanCommandBuffer* out_command_buffer);
void VulkanCommandBufferFree(VulkanContext* context, VkCommandPool pool, VulkanCommandBuffer* command_buffer);
void VulkanCommandBufferBegin(VulkanCommandBuffer* command_buffer, b8 is_single_use);
void VulkanCommandBufferEnd(VulkanCommandBuffer* command_buffer);

#endif