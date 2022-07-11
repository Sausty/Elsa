#include "VulkanDevice.h"

#include <Containers/Darray.h>
#include <Platform/Platform.h>
#include <Core/Logger.h>
#include <Core/MemTracker.h>

#include <string.h>

typedef struct VulkanPhysicalDeviceRequirements {
    b8 Graphics;
    b8 Compute;
    b8 Transfer;
    const char** DeviceExtensionNames;
    b8 SamplerAnisotropy;
    b8 PipelineStatisticsQuery;
    b8 FillModeNonSolid;
    b8 DiscreteGPU;
} VulkanPhysicalDeviceRequirements;

typedef struct VulkanPhysicalDeviceQueueFamilyInfo {
    u32 GraphicsFamilyIndex;
    u32 ComputeFamilyIndex;
    u32 TransferFamilyIndex;
} VulkanPhysicalDeviceQueueFamilyInfo;

b8 PhysicalDeviceMeetsRequirements(VkPhysicalDevice device, VkSurfaceKHR surface, const VkPhysicalDeviceProperties* properties, const VkPhysicalDeviceFeatures* features, const VulkanPhysicalDeviceRequirements* requirements, VulkanPhysicalDeviceQueueFamilyInfo* out_queue_info,
								   VulkanSwapchainSupport* out_swapchain_support)
{
	if (requirements->DiscreteGPU) {
        if (properties->deviceType != VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU) {
            ELSA_INFO("Device is not a discrete GPU, and one is required. Skipping.");
            return false;
        }
    }
	
    u32 queue_family_count = 0;
    vkGetPhysicalDeviceQueueFamilyProperties(device, &queue_family_count, 0);
    VkQueueFamilyProperties queue_families[32];
    vkGetPhysicalDeviceQueueFamilyProperties(device, &queue_family_count, queue_families);
	
    // Look at each queue and see what queues it supports
    u8 min_transfer_score = 255;
    for (u32 i = 0; i < queue_family_count; ++i) {
        u8 current_transfer_score = 0;
		
        // Graphics queue? 
        if (out_queue_info->GraphicsFamilyIndex == -1 && queue_families[i].queueFlags & VK_QUEUE_GRAPHICS_BIT) {
            out_queue_info->GraphicsFamilyIndex = i;
            ++current_transfer_score;
        }
		
        // Compute queue?
        if (queue_families[i].queueFlags & VK_QUEUE_COMPUTE_BIT) {
            out_queue_info->ComputeFamilyIndex = i;
            ++current_transfer_score;
        }
		
        // Transfer queue?
        if (queue_families[i].queueFlags & VK_QUEUE_TRANSFER_BIT) {
            // Take the index if it is the current lowest. This increases the
            // liklihood that it is a dedicated transfer queue.
            if (current_transfer_score <= min_transfer_score) {
                min_transfer_score = current_transfer_score;
                out_queue_info->TransferFamilyIndex = i;
            }
        }
    }
	
    // Print out some info about the device
    ELSA_INFO("<VulkanRendererBackendInit> Using GPU: %s", properties->deviceName);
	
    if (
        (!requirements->Graphics || (requirements->Graphics && out_queue_info->GraphicsFamilyIndex != -1)) &&
        (!requirements->Compute || (requirements->Compute && out_queue_info->ComputeFamilyIndex != -1)) &&
        (!requirements->Transfer || (requirements->Transfer && out_queue_info->TransferFamilyIndex != -1))) {
		
		VulkanDeviceQuerySwapchainSupport(
										  device,
										  surface,
										  out_swapchain_support);
		
        if (out_swapchain_support->FormatCount < 1 || out_swapchain_support->PresentModeCount < 1) {
            if (out_swapchain_support->Formats) {
                MemoryTrackerFree(out_swapchain_support->Formats, sizeof(VkSurfaceFormatKHR) * out_swapchain_support->FormatCount, MEMORY_TAG_RENDERER);
            }
            if (out_swapchain_support->PresentModes) {
                MemoryTrackerFree(out_swapchain_support->PresentModes, sizeof(VkPresentModeKHR) * out_swapchain_support->PresentModeCount, MEMORY_TAG_RENDERER);
            }
            return false;
        }
		
        // Device extensions.
        if (requirements->DeviceExtensionNames) {
            u32 available_extension_count = 0;
            VkExtensionProperties* available_extensions = 0;
            VK_CHECK(vkEnumerateDeviceExtensionProperties(
														  device,
														  0,
														  &available_extension_count,
														  0));
            if (available_extension_count != 0) {
                available_extensions = PlatformAlloc(sizeof(VkExtensionProperties) * available_extension_count);
                VK_CHECK(vkEnumerateDeviceExtensionProperties(
															  device,
															  0,
															  &available_extension_count,
															  available_extensions));
				
                u32 required_extension_count = Darray_Length(requirements->DeviceExtensionNames);
                for (u32 i = 0; i < required_extension_count; ++i) {
                    b8 found = false;
                    for (u32 j = 0; j < available_extension_count; ++j) {
                        if (!strcmp(requirements->DeviceExtensionNames[i], available_extensions[j].extensionName)) {
                            found = true;
                            break;
                        }
                    }
					
                    if (!found) {
                        PlatformFree(available_extensions);
                        return false;
                    }
                }
            }
            PlatformFree(available_extensions);
        }
		
        // Sampler anisotropy
        if (requirements->SamplerAnisotropy && !features->samplerAnisotropy) {
            ELSA_INFO("Device does not support samplerAnisotropy, skipping.");
            return false;
        }
		
        // Pipeline statistics query
        if (requirements->PipelineStatisticsQuery && !features->pipelineStatisticsQuery) {
            ELSA_INFO("Device does not support pipelineStaticsQuery, skipping.");
            return false;
        }
		
        // Fill mode non solid
        if (requirements->FillModeNonSolid && !features->fillModeNonSolid) {
            ELSA_INFO("Device does not support fillModeNonSolid, skipping.");
            return false;
        }
		
        // Device meets all requirements.
        return true;
    }
	
    return false;
}


b8 SelectPhysicalDevice(VulkanContext* context)
{
    u32 physical_device_count = 0;
    VK_CHECK(vkEnumeratePhysicalDevices(context->Instance, &physical_device_count, 0));
    if (physical_device_count == 0) {
        ELSA_FATAL("No devices which support Vulkan were found.");
        return false;
    }
	
    VkPhysicalDevice physical_devices[32];
    VK_CHECK(vkEnumeratePhysicalDevices(context->Instance, &physical_device_count, physical_devices));
    for (u32 i = 0; i < physical_device_count; ++i) {
        VkPhysicalDeviceProperties properties;
        vkGetPhysicalDeviceProperties(physical_devices[i], &properties);
		
        VkPhysicalDeviceFeatures features;
        vkGetPhysicalDeviceFeatures(physical_devices[i], &features);
		
        VkPhysicalDeviceMemoryProperties memory;
        vkGetPhysicalDeviceMemoryProperties(physical_devices[i], &memory);
        
        VulkanPhysicalDeviceRequirements requirements = {};
        requirements.Graphics = true;
        requirements.Compute = true;
        requirements.Transfer = true;
        requirements.SamplerAnisotropy = true;
#ifdef ELSA_PLATFORM_MACOS
		requirements.DiscreteGPU = false;
#else
		requirements.DiscreteGPU = true;
#endif
        requirements.DeviceExtensionNames = Darray_Create(const char*);
        Darray_Push(requirements.DeviceExtensionNames, &VK_KHR_SWAPCHAIN_EXTENSION_NAME);
		
        VulkanPhysicalDeviceQueueFamilyInfo queue_info = {};
        b8 result = PhysicalDeviceMeetsRequirements(
													physical_devices[i],
													context->Surface,
													&properties,
													&features,
													&requirements,
													&queue_info,
													&context->Device.SwapchainSupport);
		
        if (result) {
            context->Device.PhysicalDevice = physical_devices[i];
            context->Device.GraphicsQueueIndex = queue_info.GraphicsFamilyIndex;
            context->Device.ComputeQueueIndex = queue_info.ComputeFamilyIndex;
            context->Device.TransferQueueIndex = queue_info.TransferFamilyIndex;
			
            // Keep a copy of properties, features and memory info for later use.
            context->Device.Properties = properties;
            context->Device.Features = features;
            break;
        }
    }
	
    return true;
}

b8 VulkanDeviceCreate(VulkanContext* context)
{
    if (!SelectPhysicalDevice(context)) {
        return false;
    }
	
    u32 indices[32];
    u8 index = 0;
    indices[index++] = context->Device.GraphicsQueueIndex;
    indices[index++] = context->Device.TransferQueueIndex;
    indices[index++] = context->Device.ComputeQueueIndex;
	
    VkDeviceQueueCreateInfo queue_create_infos[32];
    for (u32 i = 0; i < index; ++i) {
        queue_create_infos[i].sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
        queue_create_infos[i].queueFamilyIndex = indices[i];
        queue_create_infos[i].queueCount = 1;
		
        queue_create_infos[i].flags = 0;
        queue_create_infos[i].pNext = 0;
        f32 queue_priority = 1.0f;
        queue_create_infos[i].pQueuePriorities = &queue_priority;
    }
	
    VkPhysicalDeviceFeatures device_features = {};
    device_features.samplerAnisotropy = VK_TRUE;  // Request anistrophy
    device_features.fillModeNonSolid = VK_TRUE;
    device_features.pipelineStatisticsQuery = VK_TRUE;
	
    u32 available_extension_count = 0;
    VkExtensionProperties* available_extensions = 0;
    VK_CHECK(vkEnumerateDeviceExtensionProperties(context->Device.PhysicalDevice, 0, &available_extension_count, 0));
    if (available_extension_count != 0) {
        available_extensions = MemoryTrackerAlloc(sizeof(VkExtensionProperties) * available_extension_count, MEMORY_TAG_RENDERER);
        VK_CHECK(vkEnumerateDeviceExtensionProperties(context->Device.PhysicalDevice, 0, &available_extension_count, available_extensions));
        for (u32 i = 0; i < available_extension_count; ++i) {
            // TODO: Add extensions
        }
    }
    MemoryTrackerFree(available_extensions, sizeof(VkExtensionProperties) * available_extension_count, MEMORY_TAG_RENDERER);
	
    const char** extension_names = (const char* [1]){VK_KHR_SWAPCHAIN_EXTENSION_NAME};
	
    VkDeviceCreateInfo device_create_info = {VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO};
    device_create_info.queueCreateInfoCount = index;
    device_create_info.pQueueCreateInfos = queue_create_infos;
    device_create_info.pEnabledFeatures = &device_features;
    device_create_info.enabledExtensionCount = 1;
    device_create_info.ppEnabledExtensionNames = extension_names;
	
    // Deprecated and ignored, so pass nothing.
    device_create_info.enabledLayerCount = 0;
    device_create_info.ppEnabledLayerNames = 0;
	
    // Create the device.
    VK_CHECK(vkCreateDevice(
							context->Device.PhysicalDevice,
							&device_create_info,
							NULL,
							&context->Device.LogicalDevice));
	
    // Get queues.
    vkGetDeviceQueue(
					 context->Device.LogicalDevice,
					 context->Device.GraphicsQueueIndex,
					 0,
					 &context->Device.GraphicsQueue);
	
    vkGetDeviceQueue(
					 context->Device.LogicalDevice,
					 context->Device.ComputeQueueIndex,
					 0,
					 &context->Device.ComputeQueue);
	
    vkGetDeviceQueue(
					 context->Device.LogicalDevice,
					 context->Device.TransferQueueIndex,
					 0,
					 &context->Device.TransferQueue);
	
	VkCommandPoolCreateInfo pool_create_info = {VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO};
    pool_create_info.queueFamilyIndex = context->Device.GraphicsQueueIndex;
    pool_create_info.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
    VK_CHECK(vkCreateCommandPool(
								 context->Device.LogicalDevice,
								 &pool_create_info,
								 NULL,
								 &context->Device.GraphicsCommandPool));
	
    return true;
}

void VulkanDeviceDestroy(VulkanContext* context)
{
	if (context->Device.SwapchainSupport.Formats)
		MemoryTrackerFree(context->Device.SwapchainSupport.Formats, sizeof(VkSurfaceFormatKHR) * context->Device.SwapchainSupport.FormatCount, MEMORY_TAG_RENDERER);
	if (context->Device.SwapchainSupport.PresentModes)
		MemoryTrackerFree(context->Device.SwapchainSupport.PresentModes, sizeof(VkPresentModeKHR) * context->Device.SwapchainSupport.PresentModeCount, MEMORY_TAG_RENDERER);
	
	vkDestroyCommandPool(context->Device.LogicalDevice, context->Device.GraphicsCommandPool, NULL);
    vkDestroyDevice(context->Device.LogicalDevice, NULL);
}

void VulkanDeviceQuerySwapchainSupport(VkPhysicalDevice physical_device, VkSurfaceKHR surface, VulkanSwapchainSupport* out_support_info)
{
	// Surface capabilities
    VK_CHECK(vkGetPhysicalDeviceSurfaceCapabilitiesKHR(
													   physical_device,
													   surface,
													   &out_support_info->Capabilities));
	
    // Surface formats
    VK_CHECK(vkGetPhysicalDeviceSurfaceFormatsKHR(
												  physical_device,
												  surface,
												  &out_support_info->FormatCount,
												  0));
	
    if (out_support_info->FormatCount != 0) {
        if (!out_support_info->Formats) {
            out_support_info->Formats = MemoryTrackerAlloc(sizeof(VkSurfaceFormatKHR) * out_support_info->FormatCount, MEMORY_TAG_RENDERER);
        }
        VK_CHECK(vkGetPhysicalDeviceSurfaceFormatsKHR(
													  physical_device,
													  surface,
													  &out_support_info->FormatCount,
													  out_support_info->Formats));
    }
	
    // Present modes
    VK_CHECK(vkGetPhysicalDeviceSurfacePresentModesKHR(
													   physical_device,
													   surface,
													   &out_support_info->PresentModeCount,
													   0));
    if (out_support_info->PresentModeCount != 0) {
        if (!out_support_info->PresentModes) {
            out_support_info->PresentModes = MemoryTrackerAlloc(sizeof(VkPresentModeKHR) * out_support_info->PresentModeCount, MEMORY_TAG_RENDERER);
        }
        VK_CHECK(vkGetPhysicalDeviceSurfacePresentModesKHR(
														   physical_device,
														   surface,
														   &out_support_info->PresentModeCount,
														   out_support_info->PresentModes));
    }
}