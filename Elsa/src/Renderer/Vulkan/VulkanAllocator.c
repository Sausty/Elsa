#include "VulkanAllocator.h"

b8 VulkanAllocatorInit(VulkanAllocator* allocator, VulkanContext* context)
{
	VmaAllocatorCreateInfo allocator_info = { 0 };
    allocator_info.device = context->Device.LogicalDevice;
    allocator_info.instance = context->Instance;
    allocator_info.physicalDevice = context->Device.PhysicalDevice;
    allocator_info.vulkanApiVersion = VK_API_VERSION_1_2;
	
    VkResult result = vmaCreateAllocator(&allocator_info, &allocator->Allocator);
	return result == VK_SUCCESS;
}

void VulkanAllocatorFree(VulkanAllocator* allocator, VulkanContext* context)
{
	vmaDestroyAllocator(allocator->Allocator);
}