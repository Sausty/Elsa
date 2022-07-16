#include "VulkanBackend.h"

#if defined(ELSA_VULKAN)

#include <Core/Logger.h>
#include <Containers/Darray.h>

#include <Platform/Platform.h>

#include <SPIRV/spirv_reflect.h>
#include <string.h>
#include <stdio.h>

#include "VulkanTypes.h"
#include "VulkanDevice.h"
#include "VulkanAllocator.h"
#include "VulkanSwapchain.h"
#include "VulkanCommandBuffer.h"
#include "VulkanRenderPipeline.h"
#include "VulkanDescriptorMap.h"

static VulkanContext context;

b8 VulkanRendererBackendInit(RendererBackend* backend)
{
    context.FramebufferWidth = 1280;
    context.FramebufferHeight = 720;
	context.ImageIndex = 0;
	
    VkApplicationInfo app_info = {VK_STRUCTURE_TYPE_APPLICATION_INFO};
    app_info.apiVersion = VK_API_VERSION_1_3;
    app_info.pApplicationName = "Elsa Application";
    app_info.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
    app_info.pEngineName = "Elsa Engine";
    app_info.engineVersion = VK_MAKE_VERSION(1, 0, 0);
	
    VkInstanceCreateInfo create_info = {VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO};
    create_info.pApplicationInfo = &app_info;
	
    // Obtain a list of required extensions
    const char** required_extensions = Darray_Create(const char*);
    Darray_Push(required_extensions, &VK_KHR_SURFACE_EXTENSION_NAME);  // Generic surface extension
    PlatformGetRequiredExtensionNames(&required_extensions);       // Platform-specific extension(s)
    create_info.enabledExtensionCount = Darray_Length(required_extensions);
    create_info.ppEnabledExtensionNames = required_extensions;
	
    const char** required_validation_layer_names = 0;
    u32 required_validation_layer_count = 0;
	
#if defined(_DEBUG)
    // The list of validation layers required.
    required_validation_layer_names = Darray_Create(const char*);
    Darray_Push(required_validation_layer_names, &"VK_LAYER_KHRONOS_validation");
    required_validation_layer_count = Darray_Length(required_validation_layer_names);
	
    // Obtain a list of available validation layers
    u32 available_layer_count = 0;
    VK_CHECK(vkEnumerateInstanceLayerProperties(&available_layer_count, NULL));
    VkLayerProperties* available_layers = Darray_Reserve(VkLayerProperties, available_layer_count);
    VK_CHECK(vkEnumerateInstanceLayerProperties(&available_layer_count, available_layers));
	
    // Verify all required layers are available.
    for (u32 i = 0; i < required_validation_layer_count; ++i) {
        b8 found = false;
        for (u32 j = 0; j < available_layer_count; ++j) {
            if (!strcmp(required_validation_layer_names[i], available_layers[j].layerName)) {
                found = true;
                break;
            }
        }
		
        if (!found) {
            return false;
        }
    }
#endif
    create_info.enabledLayerCount = required_validation_layer_count;
    create_info.ppEnabledLayerNames = required_validation_layer_names;
	
    VK_CHECK(vkCreateInstance(&create_info, NULL, &context.Instance));
	
    if (!PlatformCreateVulkanSurface(&context)) {
        ELSA_ERROR("PlatformCreateVulkanSurface failed. Shutting down...")
			return false;
    }
	
    if (!VulkanDeviceCreate(&context)) {
        ELSA_ERROR("VulkanDeviceCreate failed. Shutting down...");
        return false;
    }
	
	if (!VulkanAllocatorInit(&context.Allocator, &context)) {
		ELSA_ERROR("VulkanAllocatorInit failed. Shutting down...");
        return false;
	}
	
	VulkanSwapchainCreate(&context, context.FramebufferWidth, context.FramebufferHeight, &context.Swapchain);
	
	// Sync
	VkFenceCreateInfo fence_info = { 0 };
    fence_info.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
	fence_info.flags = VK_FENCE_CREATE_SIGNALED_BIT;
	
	for (u32 i = 0; i < context.Swapchain.ImageCount; i++) {
		VK_CHECK(vkCreateFence(context.Device.LogicalDevice, &fence_info, NULL, &context.ImageFences[i]));
	}
	
	VkSemaphoreCreateInfo semaphore_info = { 0 };
    semaphore_info.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;
	VK_CHECK(vkCreateSemaphore(context.Device.LogicalDevice, &semaphore_info, NULL, &context.ImageAvailableSemaphore));
	VK_CHECK(vkCreateSemaphore(context.Device.LogicalDevice, &semaphore_info, NULL, &context.ImageRenderedSemaphore));
	
	context.CommandBuffers = Darray_Reserve(VulkanCommandBuffer, context.Swapchain.ImageCount);
	for (u32 i = 0; i < context.Swapchain.ImageCount; i++) {
		VulkanCommandBufferAlloc(&context, context.Device.GraphicsCommandPool, true, &context.CommandBuffers[i]);
	}
	
	return true;
}

void VulkanRendererBackendShutdown(RendererBackend* backend)
{
    vkDeviceWaitIdle(context.Device.LogicalDevice);
	
	for (u32 i = 0; i < context.Swapchain.ImageCount; i++) {
		VulkanCommandBufferFree(&context, context.Device.GraphicsCommandPool, &context.CommandBuffers[i]);
	}
	Darray_Destroy(context.CommandBuffers);
	
	// Sync objects
    for (u8 i = 0; i < context.Swapchain.ImageCount; ++i) {
        vkDestroyFence(context.Device.LogicalDevice, context.ImageFences[i], NULL);
    }
	vkDestroySemaphore(context.Device.LogicalDevice, context.ImageAvailableSemaphore, NULL);
	vkDestroySemaphore(context.Device.LogicalDevice, context.ImageRenderedSemaphore, NULL);
	
	VulkanSwapchainDestroy(&context, &context.Swapchain);
	VulkanAllocatorFree(&context.Allocator, &context);
    VulkanDeviceDestroy(&context);
    vkDestroySurfaceKHR(context.Instance, context.Surface, NULL);
    vkDestroyInstance(context.Instance, NULL);
}   

void VulkanRendererBackendResized(RendererBackend* backend, u16 width, u16 height)
{
	context.FramebufferWidth = (u32)width;
	context.FramebufferHeight = (u32)height;
	
	VulkanSwapchainRecreate(&context, width, height, &context.Swapchain);
}

Buffer* VulkanRendererBackendBufferCreate(RendererBackend* backend, u64 size, BufferUsage usage)
{
	return VulkanAllocatorBufferCreate(&context.Allocator, size, usage);
}

void VulkanRendererBackendBufferUpload(RendererBackend* backend, void* data, u64 size, Buffer* buffer)
{
	VulkanAllocatorBufferUpload(&context.Allocator, size, data, buffer);
}

void VulkanRendererBackendBufferFree(RendererBackend* backend, Buffer* buffer)
{
	VulkanAllocatorBufferFree(&context.Allocator, buffer);
}

b8 VulkanRendererBackendDescriptorMapCreate(RendererBackend* backend, ShaderPack* pack, DescriptorMap* map)
{
	// Structure of a descriptor map:
	//
	// DESCRIPTOR_MAP
	// [
	// SHADER_STAGE (DescriptorSubmap):
	//    DescriptorSetLayout 1 (DescriptorLayout):
	//        Descriptor1 (Name, Binding, Count, Type) (DescriptorInfo)
	//        Descriptor2 (Name, Binding, Count, Type) (DescriptorInfo)
	//    DescriptorSetLayout 2 (DescriptorLayout):
	//        Descriptor1 (Name, Binding, Count, Type) (DescriptorInfo)
	//        Descriptor2 (Name, Binding, Count, Type) (DescriptorInfo)
	// ]
	//
	// A DescriptorSubmap is the descriptor set layouts of a shader stage.
	// A DescriptorLayout is the descriptors of a descriptor set layout.
	// A DescriptorInfo holds all the information about a descriptor (name, binding, count, type)
	// So basically:
	// [DescriptorMap -> [DescriptorSubmap -> DescriptorLayout -> [DescriptorInfo]]]
	
	CODE_BLOCK("Reflection")
	{
		for (u32 i = 0; i < Darray_Length(pack->Modules); i++) {
			ShaderModule* module = &pack->Modules[i];

			SpvReflectShaderModule reflect;
			SpvReflectResult result = spvReflectCreateShaderModule(module->ByteCodeSize, module->ByteCode, &reflect);
			if (result != SPV_REFLECT_RESULT_SUCCESS) {
				ELSA_ERROR("Failed to reflect descriptor map shader module!");
				return false;
			}

			u32 count = 0;
			result = spvReflectEnumerateDescriptorSets(&reflect, &count, NULL);
			if (result != SPV_REFLECT_RESULT_SUCCESS) {
				ELSA_ERROR("Failed to enumerate descriptor map sets!");
				return false;
			}

			SpvReflectDescriptorSet* sets = PlatformAlloc(sizeof(SpvReflectDescriptorSet) * count);
			result = spvReflectEnumerateDescriptorSets(&reflect, &count, &sets);
			if (result != SPV_REFLECT_RESULT_SUCCESS) {
				ELSA_ERROR("Failed to enumerate descriptor map sets!");
				return false;
			}

			DescriptorSubmap* submap = &map->Submaps[(u32)module->Stage];
			submap->Stage = module->Stage;

			for (u32 i = 0; i < count; i++) {
				SpvReflectDescriptorSet refl_set = sets[i];
				for (u32 j = 0; j < refl_set.binding_count; j++) {
					SpvReflectDescriptorBinding* refl_binding = refl_set.bindings[j];

					sprintf(submap->Layouts[i].Descriptors[j].Name, "%s", refl_binding->name);
					submap->Layouts[i].Descriptors[j].Binding = refl_binding->binding;
					submap->Layouts[i].Descriptors[j].Type = (DescriptorType)refl_binding->descriptor_type;
					submap->Layouts[i].Descriptors[j].Count = 1;
					for (u32 dim = 0; dim < refl_binding->array.dims_count; dim++) {
						submap->Layouts[i].Descriptors[j].Count *= refl_binding->array.dims[dim];
					}
					if (refl_binding->block.size) {
						submap->Layouts[i].Descriptors[j].BufferSize = refl_binding->block.size;
					}
					submap->Layouts[i].DescriptorCount++;
				}
				submap->LayoutCount++;
			}

			PlatformFree(sets);
			spvReflectDestroyShaderModule(&reflect);

			map->SubmapCount++;
		}
	}

	CODE_BLOCK("Backend creation")
	{
		if (!VulkanDescriptorMapCreate(&context, map)) {
			ELSA_ERROR("Failed to create Vulkan backend for descriptor map.");
			return false;
		}
	}

	return true;
}

void VulkanRendererBackendDescriptorMapDestroy(RendererBackend* backend, DescriptorMap* map)
{
	VulkanDescriptorMapDestroy(&context, map);
}

b8 VulkanRendererBackendBeginFrame(RendererBackend* backend, f32 delta_time)
{
	VulkanDevice* device = &context.Device;
	
	VkResult result = vkWaitForFences(context.Device.LogicalDevice, 1, &context.ImageFences[context.ImageIndex], true, UINT64_MAX);
	VK_CHECK(result);
	
	ELSA_ASSERT(VulkanSwapchainNextImage(&context, &context.Swapchain, UINT64_MAX, context.ImageAvailableSemaphore, 0, &context.ImageIndex));
	VulkanCommandBufferBegin(&context.CommandBuffers[context.ImageIndex], false);
	
	VkCommandBuffer cmd = context.CommandBuffers[context.ImageIndex].Handle;
	
	// Dynamic state
    VkViewport viewport;
    viewport.x = 0.0f;
    viewport.y = (f32)context.FramebufferHeight;
    viewport.width = (f32)context.FramebufferWidth;
    viewport.height = -(f32)context.FramebufferHeight;
    viewport.minDepth = 0.0f;
    viewport.maxDepth = 1.0f;
	
    // Scissor
    VkRect2D scissor;
    scissor.offset.x = scissor.offset.y = 0;
    scissor.extent.width = context.FramebufferWidth;
    scissor.extent.height = context.FramebufferHeight;
	
    vkCmdSetViewport(cmd, 0, 1, &viewport);
    vkCmdSetScissor(cmd, 0, 1, &scissor);
	
	{
		VkImageSubresourceRange range = { 0 };
		range.baseMipLevel = 0;
		range.levelCount = VK_REMAINING_MIP_LEVELS;
		range.baseArrayLayer = 0;
		range.layerCount = VK_REMAINING_ARRAY_LAYERS;
		range.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
		
		VkImageMemoryBarrier barrier = { 0 };
		barrier.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
		barrier.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
		barrier.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
		barrier.srcAccessMask = 0;
		barrier.dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;
		barrier.oldLayout = VK_IMAGE_LAYOUT_UNDEFINED;
		barrier.newLayout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
		barrier.image = context.Swapchain.RenderTextures[context.ImageIndex]->Image;
		barrier.subresourceRange = range;
		
		vkCmdPipelineBarrier(context.CommandBuffers[context.ImageIndex].Handle, VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT, VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT, 0, 0, NULL, 0, NULL, 1, &barrier);
	}
	
	return true;
}

b8 VulkanRendererBackendEndFrame(RendererBackend* backend, f32 delta_time)
{
	{
		VkImageSubresourceRange range = { 0 };
		range.baseMipLevel = 0;
		range.levelCount = VK_REMAINING_MIP_LEVELS;
		range.baseArrayLayer = 0;
		range.layerCount = VK_REMAINING_ARRAY_LAYERS;
		range.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
		
		VkImageMemoryBarrier barrier = { 0 };
		barrier.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
		barrier.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
		barrier.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
		barrier.srcAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;
		barrier.dstAccessMask = VK_ACCESS_MEMORY_READ_BIT;
		barrier.oldLayout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
		barrier.newLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;
		barrier.image = context.Swapchain.RenderTextures[context.ImageIndex]->Image;
		barrier.subresourceRange = range;
		
		vkCmdPipelineBarrier(context.CommandBuffers[context.ImageIndex].Handle, VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT, VK_PIPELINE_STAGE_BOTTOM_OF_PIPE_BIT, 0, 0, NULL, 0, NULL, 1, &barrier);
	}
	
	VulkanCommandBufferEnd(&context.CommandBuffers[context.ImageIndex]);
	
	VK_CHECK(vkResetFences(context.Device.LogicalDevice, 1, &context.ImageFences[context.ImageIndex]));
	
	// Begin queue submission
    VkSubmitInfo submit_info = {VK_STRUCTURE_TYPE_SUBMIT_INFO};
    submit_info.commandBufferCount = 1;
    submit_info.pCommandBuffers = &context.CommandBuffers[context.ImageIndex].Handle;
    submit_info.signalSemaphoreCount = 1;
    submit_info.pSignalSemaphores = &context.ImageRenderedSemaphore;
    submit_info.waitSemaphoreCount = 1;
    submit_info.pWaitSemaphores = &context.ImageAvailableSemaphore;
    VkPipelineStageFlags flags[1] = {VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT};
    submit_info.pWaitDstStageMask = flags;
	
	VkResult result = vkQueueSubmit(context.Device.GraphicsQueue, 1, &submit_info, context.ImageFences[context.ImageIndex]);
    if (result != VK_SUCCESS) {
		return false;
	}
	
	VulkanSwapchainPresent(&context, &context.Swapchain, context.Device.GraphicsQueue, context.ImageRenderedSemaphore, context.ImageIndex);
	
	return true;
}

b8 VulkanRendererBackendRenderPipelineCreate(RendererBackend* backend, ShaderPack* pack, DescriptorMap* map, RenderPipeline* pipeline)
{
	if (!VulkanRenderPipelineCreate(&context, pack, map, pipeline)) {
		ELSA_FATAL("Failed to create render pipeline!");
		return false;
	}
	
	return true;
}

void VulkanRendererBackendRenderPipelineDestroy(RendererBackend* backend, RenderPipeline* pipeline)
{
	VulkanRenderPipelineDestroy(&context, pipeline);
}

#endif