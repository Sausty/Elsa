#include "VulkanCommandBuffer.h"

void VulkanCommandBufferAlloc(VulkanContext* context, VkCommandPool pool, b8 is_primary, VulkanCommandBuffer* out_command_buffer)
{
    VkCommandBufferAllocateInfo allocate_info = {VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO};
    allocate_info.commandPool = pool;
    allocate_info.level = is_primary ? VK_COMMAND_BUFFER_LEVEL_PRIMARY : VK_COMMAND_BUFFER_LEVEL_SECONDARY;
    allocate_info.commandBufferCount = 1;
    allocate_info.pNext = 0;
	
    VK_CHECK(vkAllocateCommandBuffers(
									  context->Device.LogicalDevice,
									  &allocate_info,
									  &out_command_buffer->Handle));
}

void VulkanCommandBufferFree(VulkanContext* context, VkCommandPool pool, VulkanCommandBuffer* command_buffer)
{
	vkFreeCommandBuffers(
						 context->Device.LogicalDevice,
						 pool,
						 1,
						 &command_buffer->Handle);
}

void VulkanCommandBufferBegin(VulkanCommandBuffer* command_buffer, b8 is_single_use)
{
	VkCommandBufferBeginInfo begin_info = {VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO};
    begin_info.flags = 0;
    if (is_single_use) {
        begin_info.flags |= VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;
    }
	VK_CHECK(vkBeginCommandBuffer(command_buffer->Handle, &begin_info));
}

void VulkanCommandBufferEnd(VulkanCommandBuffer* command_buffer)
{
	VK_CHECK(vkEndCommandBuffer(command_buffer->Handle));
}