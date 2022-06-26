#include "RendererBackend.h"

#include <Platform/Platform.h>

#include "Metal/MetalBackend.h"
#include "Vulkan/VulkanBackend.h"

b8 RendererBackendCreate(RendererBackendAPI api, RendererBackend* out_renderer_backend)
{
    if (api == RENDERER_BACKEND_API_METAL) {
#if defined(ELSA_METAL)
        out_renderer_backend->API = RENDERER_BACKEND_API_METAL;
        out_renderer_backend->Init = MetalRendererBackendInit;
        out_renderer_backend->Shutdown = MetalRendererBackendShutdown;
        out_renderer_backend->Resized = MetalRendererBackendResized;
        out_renderer_backend->BeginFrame = MetalRendererBackendBeginFrame;
        out_renderer_backend->EndFrame = MetalRendererBackendEndFrame;

        return true;
#else 
        return false;
#endif
    } else if (api == RENDERER_BACKEND_API_VULKAN) {
#if defined(ELSA_VULKAN)
        out_renderer_backend->API = RENDERER_BACKEND_API_VULKAN;
        out_renderer_backend->Init = VulkanRendererBackendInit;
        out_renderer_backend->Shutdown = VulkanRendererBackendShutdown;
        out_renderer_backend->Resized = VulkanRendererBackendResized;
        out_renderer_backend->BeginFrame = VulkanRendererBackendBeginFrame;
        out_renderer_backend->EndFrame = VulkanRendererBackendEndFrame;

        return true;
#else
        return false;
#endif
    }

    return false;
}

void RendererBackendDestroy(RendererBackend* renderer_backend)
{
    PlatformZeroMemory(renderer_backend, sizeof(RendererBackend));
}