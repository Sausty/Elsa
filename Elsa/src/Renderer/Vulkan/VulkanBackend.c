#include "VulkanBackend.h"

#if defined(ELSA_VULKAN)

#include <Core/Logger.h>
#include <Platform/Platform.h>
#include <Containers/Darray.h>
#include <string.h>

#include "VulkanTypes.h"
#include "VulkanDevice.h"

static VulkanContext context;

b8 VulkanRendererBackendInit(RendererBackend* backend)
{
    context.FramebufferWidth = 1280;
    context.FramebufferHeight = 720;

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
    VK_CHECK(vkEnumerateInstanceLayerProperties(&available_layer_count, 0));
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

    return true;
}

void VulkanRendererBackendShutdown(RendererBackend* backend)
{
    vkDeviceWaitIdle(context.Device.LogicalDevice);

    VulkanDeviceDestroy(&context);
    vkDestroySurfaceKHR(context.Instance, context.Surface, NULL);
    vkDestroyInstance(context.Instance, NULL);
}   

void VulkanRendererBackendResized(RendererBackend* backend, u16 width, u16 height)
{

}

b8 VulkanRendererBackendBeginFrame(RendererBackend* backend, f32 delta_time)
{
    return true;
}

b8 VulkanRendererBackendEndFrame(RendererBackend* backend, f32 delta_time)
{
    return true;
}

#endif