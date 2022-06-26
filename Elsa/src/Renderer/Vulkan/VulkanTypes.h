/**
 * @file VulkanTypes.h
 * @author Milo Heinrich (MikuoH15TH@gmail.com)
 * @brief This file contains type definitions for the Vulkan backend.
 * @version 1.0
 * @date 2022-06-26
 */
#ifndef ELSA_VULKAN_TYPES_H
#define ELSA_VULKAN_TYPES_H

#include <Defines.h>

#include <vulkan/vulkan.h>

// TODO(milo): Add assertions
#define VK_CHECK(error) error

typedef struct VulkanDevice {
    VkPhysicalDevice PhysicalDevice;
    VkDevice LogicalDevice;

    i32 GraphicsQueueIndex;
    i32 ComputeQueueIndex;
    i32 TransferQueueIndex;

    VkQueue GraphicsQueue;
    VkQueue ComputeQueue;
    VkQueue TransferQueue;

    VkPhysicalDeviceProperties Properties;
    VkPhysicalDeviceFeatures Features;
    
    VkFormat DepthFormat;
} VulkanDevice;

typedef struct VulkanContext {
    f32 FrameDeltaTime;

    u32 FramebufferWidth;
    u32 FramebufferHeight;

    VkInstance Instance;
    VkSurfaceKHR Surface;
    VulkanDevice Device;
} VulkanContext;

#endif