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
#include <Renderer/RendererTypes.h>
#include <Core/Asserts.h>

#include <vulkan/vulkan.h>
#include <VMA/vk_mem_alloc.h>

// TODO(milo): Image
// TODO(milo): Swapchain
// TODO(milo): Render passes
// TODO(milo): Graphics and compute pipelines
// TODO(milo): Shader system

#define VK_CHECK(error) ELSA_ASSERT(error == VK_SUCCESS)

typedef struct VulkanAllocator {
	VmaAllocator Allocator;
} VulkanAllocator;

typedef struct Buffer {
	VkBuffer Buffer;
	VmaAllocation Allocation;
	u64 Size;
	BufferUsage Usage;
} Buffer;

typedef struct Texture {
	VkImage Image;
	VkImageView ImageView;
	VkFormat Format;
	VkImageLayout Layout;
	
	u32 Width;
	u32 Height;
} Texture;

typedef struct VulkanShader {
	VkShaderModule Module;
	VkShaderStageFlagBits Stage;
} VulkanShader;

typedef struct VulkanRenderPipeline {
	VkPipeline Pipeline;
	VkPipelineLayout PipelineLayout;
} VulkanRenderPipeline;

typedef struct VulkanCommandBuffer {
	VkCommandBuffer Handle;
} VulkanCommandBuffer;

typedef struct VulkanSwapchain {
	VkSurfaceFormatKHR ImageFormat;
	u8 MaxFramesInFlight;
	VkSwapchainKHR Handle;
	u32 ImageCount;
	Texture* RenderTextures[3];
} VulkanSwapchain;

typedef struct VulkanSwapchainSupport {
	VkSurfaceCapabilitiesKHR Capabilities;
	u32 FormatCount;
	VkSurfaceFormatKHR* Formats;
	u32 PresentModeCount;
	VkPresentModeKHR* PresentModes;
} VulkanSwapchainSupport;

typedef struct VulkanDevice {
    VkPhysicalDevice PhysicalDevice;
    VkDevice LogicalDevice;
	VulkanSwapchainSupport SwapchainSupport;
	
    i32 GraphicsQueueIndex;
    i32 ComputeQueueIndex;
    i32 TransferQueueIndex;
	
    VkQueue GraphicsQueue;
    VkQueue ComputeQueue;
    VkQueue TransferQueue;
	
	VkCommandPool GraphicsCommandPool;
	
    VkPhysicalDeviceProperties Properties;
    VkPhysicalDeviceFeatures2 Features;
    
    VkFormat DepthFormat;
} VulkanDevice;

typedef struct VulkanContext {
    f32 FrameDeltaTime;
	
    u32 FramebufferWidth;
    u32 FramebufferHeight;
	u32 ImageIndex;
	
    VkInstance Instance;
    VkSurfaceKHR Surface;
    VulkanDevice Device;
	
	VulkanAllocator Allocator;
	VulkanSwapchain Swapchain;
	
	VkFence ImageFences[3];
	VkSemaphore ImageAvailableSemaphore;
	VkSemaphore ImageRenderedSemaphore;
	
	VulkanCommandBuffer* CommandBuffers;
} VulkanContext;

#endif