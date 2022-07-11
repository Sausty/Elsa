/**
 * @file VulkanTypes.h
 * @author Milo Heinrich (MikuoH15TH@gmail.com)
 * @brief This file contains type functions for swapchain stuff.
 * @version 1.0
 * @date 2022-07-11
 */
#ifndef ELSA_VULKAN_SWAPCHAIN_H
#define ELSA_VULKAN_SWAPCHAIN_H

#include "VulkanTypes.h"

void VulkanSwapchainCreate(VulkanContext* context, u32 width, u32 height, VulkanSwapchain* out);
void VulkanSwapchainRecreate(VulkanContext* context, u32 width, u32 height, VulkanSwapchain* swapchain);
void VulkanSwapchainDestroy(VulkanContext* context, VulkanSwapchain* swapchain);
b8 VulkanSwapchainNextImage(VulkanContext* context, VulkanSwapchain* swapchain, u64 timeout_ns, VkSemaphore semaphore, VkFence fence, u32* out_image_index);
void VulkanSwapchainPresent(VulkanContext* context, VulkanSwapchain* swapchain, VkQueue graphics_queue, VkSemaphore semaphore, u32 present_image_index);

#endif
