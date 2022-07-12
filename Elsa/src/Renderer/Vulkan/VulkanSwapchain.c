#include "VulkanSwapchain.h"

#include <Core/Logger.h>
#include <Core/MemTracker.h>
#include "VulkanDevice.h"

void Create(VulkanContext* context, u32 width, u32 height, VulkanSwapchain* swapchain);
void Destroy(VulkanContext* context, VulkanSwapchain* swapchain);

void VulkanSwapchainCreate(VulkanContext* context, u32 width, u32 height, VulkanSwapchain* out)
{
	Create(context, width, height, out);
}

void VulkanSwapchainRecreate(VulkanContext* context, u32 width, u32 height, VulkanSwapchain* swapchain)
{
	Destroy(context, swapchain);
	Create(context, width, height, swapchain);
}

void VulkanSwapchainDestroy(VulkanContext* context, VulkanSwapchain* swapchain)
{
	Destroy(context, swapchain);
}

b8 VulkanSwapchainNextImage(VulkanContext* context, VulkanSwapchain* swapchain, u64 timeout_ns, VkSemaphore semaphore, VkFence fence, u32* out_image_index)
{
	VkResult result = vkAcquireNextImageKHR(context->Device.LogicalDevice, swapchain->Handle, timeout_ns, semaphore, fence, out_image_index);
	
	if (result == VK_ERROR_OUT_OF_DATE_KHR) {
        VulkanSwapchainRecreate(context, context->FramebufferWidth, context->FramebufferHeight, swapchain);
        return false;
    } else if (result != VK_SUCCESS && result != VK_SUBOPTIMAL_KHR) {
        ELSA_FATAL("Failed to acquire swapchain image!");
        return false;
    }
	
    return true;
}

void VulkanSwapchainPresent(VulkanContext* context, VulkanSwapchain* swapchain, VkQueue graphics_queue, VkSemaphore semaphore, u32 present_image_index)
{
	VkPresentInfoKHR present_info = {VK_STRUCTURE_TYPE_PRESENT_INFO_KHR};
    present_info.waitSemaphoreCount = 1;
    present_info.pWaitSemaphores = &semaphore;
    present_info.swapchainCount = 1;
    present_info.pSwapchains = &swapchain->Handle;
    present_info.pImageIndices = &present_image_index;
    present_info.pResults = 0;
	
	VkResult result = vkQueuePresentKHR(graphics_queue, &present_info);
	if (result == VK_ERROR_OUT_OF_DATE_KHR || result == VK_SUBOPTIMAL_KHR) {
        VulkanSwapchainRecreate(context, context->FramebufferWidth, context->FramebufferHeight, swapchain);
        ELSA_DEBUG("Swapchain recreated because swapchain returned out of date or suboptimal.");
    } else if (result != VK_SUCCESS) {
        ELSA_FATAL("Failed to present swap chain image!");
    }
}

void Create(VulkanContext* context, u32 width, u32 height, VulkanSwapchain* swapchain)
{
	VkExtent2D swapchain_extent = {width, height};
	
    // Choose a swap surface format.
    b8 found = false;
    for (u32 i = 0; i < context->Device.SwapchainSupport.FormatCount; ++i) {
        VkSurfaceFormatKHR format = context->Device.SwapchainSupport.Formats[i];
        // Preferred formats
        if (format.format == VK_FORMAT_B8G8R8A8_UNORM &&
            format.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR) {
            swapchain->ImageFormat = format;
            found = true;
            break;
        }
    }
	
    if (!found) {
        swapchain->ImageFormat = context->Device.SwapchainSupport.Formats[0];
    }
	
    VkPresentModeKHR present_mode = VK_PRESENT_MODE_FIFO_KHR;
    for (u32 i = 0; i < context->Device.SwapchainSupport.PresentModeCount; ++i) {
        VkPresentModeKHR mode = context->Device.SwapchainSupport.PresentModes[i];
        if (mode == VK_PRESENT_MODE_MAILBOX_KHR) {
            present_mode = mode;
            break;
        }
    }
	
    // Requery swapchain support.
    VulkanDeviceQuerySwapchainSupport(context->Device.PhysicalDevice, context->Surface, &context->Device.SwapchainSupport);
	
    // Swapchain extent
    if (context->Device.SwapchainSupport.Capabilities.currentExtent.width != UINT32_MAX) {
        swapchain_extent =context->Device.SwapchainSupport.Capabilities.currentExtent;
    }
	
    // Clamp to the value allowed by the GPU.
    VkExtent2D min = context->Device.SwapchainSupport.Capabilities.minImageExtent;
    VkExtent2D max = context->Device.SwapchainSupport.Capabilities.maxImageExtent;
    swapchain_extent.width = ELSA_CLAMP(swapchain_extent.width, min.width, max.width);
    swapchain_extent.height = ELSA_CLAMP(swapchain_extent.height, min.height, max.height);
	
    u32 image_count = context->Device.SwapchainSupport.Capabilities.minImageCount + 1;
    if (context->Device.SwapchainSupport.Capabilities.maxImageCount > 0 && image_count > context->Device.SwapchainSupport.Capabilities.maxImageCount) {
        image_count = context->Device.SwapchainSupport.Capabilities.maxImageCount;
    }
	
    swapchain->MaxFramesInFlight = image_count - 1;
	
    // Swapchain create info
    VkSwapchainCreateInfoKHR swapchain_create_info = {VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR};
    swapchain_create_info.surface = context->Surface;
    swapchain_create_info.minImageCount = image_count;
    swapchain_create_info.imageFormat = swapchain->ImageFormat.format;
    swapchain_create_info.imageColorSpace = swapchain->ImageFormat.colorSpace;
    swapchain_create_info.imageExtent = swapchain_extent;
    swapchain_create_info.imageArrayLayers = 1;
    swapchain_create_info.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
    swapchain_create_info.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
	swapchain_create_info.queueFamilyIndexCount = 0;
	swapchain_create_info.pQueueFamilyIndices = 0;
    swapchain_create_info.preTransform = context->Device.SwapchainSupport.Capabilities.currentTransform;
    swapchain_create_info.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
    swapchain_create_info.presentMode = present_mode;
    swapchain_create_info.clipped = VK_TRUE;
    swapchain_create_info.oldSwapchain = 0;
	
    VK_CHECK(vkCreateSwapchainKHR(context->Device.LogicalDevice, &swapchain_create_info, NULL, &swapchain->Handle));
	
	// Allocate textures
	for (i32 i = 0; i < 3; i++) {
		swapchain->RenderTextures[i] = MemoryTrackerAlloc(sizeof(Texture), MEMORY_TAG_RENDERER);
	}
	
    // Start with a zero frame index.
    context->ImageIndex = 0;
	
    // Images
    swapchain->ImageCount = 0;
    VK_CHECK(vkGetSwapchainImagesKHR(context->Device.LogicalDevice, swapchain->Handle, &swapchain->ImageCount, NULL));
    
    VkImage swapchain_images[32];
    VK_CHECK(vkGetSwapchainImagesKHR(context->Device.LogicalDevice, swapchain->Handle, &swapchain->ImageCount, swapchain_images));
    for (u32 i = 0; i < swapchain->ImageCount; ++i) {
        Texture* image = swapchain->RenderTextures[i];
        image->Image = swapchain_images[i];
        image->Width = swapchain_extent.width;
        image->Height = swapchain_extent.height;
    }
	
    // Views
    for (u32 i = 0; i < swapchain->ImageCount; ++i) {
        Texture* image = swapchain->RenderTextures[i];
		
        VkImageViewCreateInfo view_info = {VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO};
        view_info.image = image->Image;
        view_info.viewType = VK_IMAGE_VIEW_TYPE_2D;
        view_info.format = swapchain->ImageFormat.format;
        view_info.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
        view_info.subresourceRange.baseMipLevel = 0;
        view_info.subresourceRange.levelCount = 1;
        view_info.subresourceRange.baseArrayLayer = 0;
        view_info.subresourceRange.layerCount = 1;
		
        VK_CHECK(vkCreateImageView(context->Device.LogicalDevice, &view_info, NULL, &image->ImageView));
    }
}

void Destroy(VulkanContext* context, VulkanSwapchain* swapchain)
{
	vkDeviceWaitIdle(context->Device.LogicalDevice);
	
	for (u32 i = 0; i < swapchain->ImageCount; ++i) {
        Texture* image = swapchain->RenderTextures[i];
        vkDestroyImageView(context->Device.LogicalDevice, image->ImageView, NULL);
		MemoryTrackerFree(image, sizeof(Texture), MEMORY_TAG_RENDERER);
	}
	vkDestroySwapchainKHR(context->Device.LogicalDevice, swapchain->Handle, NULL);
}