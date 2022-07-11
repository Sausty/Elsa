#include "VulkanAllocator.h"

#include <Core/MemTracker.h>
#include <Core/Logger.h>

VkBufferUsageFlagBits BufferUsageToVulkan(BufferUsage usage)
{
	switch (usage)
	{
		case BUFFER_USAGE_VERTEX:
		return VK_BUFFER_USAGE_VERTEX_BUFFER_BIT;
		case BUFFER_USAGE_INDEX:
		return VK_BUFFER_USAGE_INDEX_BUFFER_BIT;
		case BUFFER_USAGE_STORAGE:
		return VK_BUFFER_USAGE_STORAGE_BUFFER_BIT;
		case BUFFER_USAGE_UNIFORM:
		return VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT;
	}
	
	return VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT;
}

VmaMemoryUsage BufferUsageToVMA(BufferUsage usage)
{
	switch (usage)
	{
		case BUFFER_USAGE_VERTEX:
		return VMA_MEMORY_USAGE_CPU_TO_GPU;
		case BUFFER_USAGE_INDEX:
		return VMA_MEMORY_USAGE_CPU_TO_GPU;
		case BUFFER_USAGE_STORAGE:
		return VMA_MEMORY_USAGE_GPU_ONLY;
		case BUFFER_USAGE_UNIFORM:
		return VMA_MEMORY_USAGE_CPU_ONLY;
	}
}

b8 VulkanAllocatorInit(VulkanAllocator* allocator, VulkanContext* context)
{
	VmaAllocatorCreateInfo allocator_info = { 0 };
    allocator_info.device = context->Device.LogicalDevice;
    allocator_info.instance = context->Instance;
    allocator_info.physicalDevice = context->Device.PhysicalDevice;
    allocator_info.vulkanApiVersion = VK_API_VERSION_1_3;
	
    VkResult result = vmaCreateAllocator(&allocator_info, &allocator->Allocator);
	return result == VK_SUCCESS;
}

void VulkanAllocatorFree(VulkanAllocator* allocator, VulkanContext* context)
{
	vmaDestroyAllocator(allocator->Allocator);
}

Buffer* VulkanAllocatorBufferCreate(VulkanAllocator* allocator, u64 size, BufferUsage usage)
{
	Buffer* buffer = MemoryTrackerAlloc(sizeof(Buffer), MEMORY_TAG_RENDERER);
	
	VkBufferCreateInfo buffer_create_info = {0};
	buffer_create_info.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
	buffer_create_info.size = size;
	buffer_create_info.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
	buffer_create_info.usage = BufferUsageToVulkan(usage);
	
	VmaAllocationCreateInfo allocation_create_info = {0};
	allocation_create_info.usage = BufferUsageToVMA(usage);
	
	VkResult result = vmaCreateBuffer(allocator->Allocator, &buffer_create_info, &allocation_create_info, &buffer->Buffer, &buffer->Allocation, NULL);
	if (result != VK_SUCCESS) {
		ELSA_ERROR("Failed to create GPU buffer!");
		MemoryTrackerFree(buffer, sizeof(Buffer), MEMORY_TAG_RENDERER);
		return NULL;
	}
	
	return buffer;
}

void VulkanAllocatorBufferFree(VulkanAllocator* allocator, Buffer* buffer)
{
	vmaDestroyBuffer(allocator->Allocator, buffer->Buffer, buffer->Allocation);
	MemoryTrackerFree(buffer, sizeof(Buffer), MEMORY_TAG_RENDERER);
}