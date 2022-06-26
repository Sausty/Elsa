#include "VulkanBackend.h"

#if defined(ELSA_VULKAN)

b8 VulkanRendererBackendInit(RendererBackend* backend)
{
    return true;
}

void VulkanRendererBackendShutdown(RendererBackend* backend)
{
    
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