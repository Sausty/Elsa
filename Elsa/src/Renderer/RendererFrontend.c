#include "RendererFrontend.h"

#include "RendererBackend.h"

#include <Core/Logger.h>

typedef struct RendererFrontend {
    RendererBackend backend;
    
    u32 FramebufferWidth;
    u32 FramebufferHeight;
} RendererFrontend;

static RendererFrontend frontend;

b8 RendererFrontendInit(const char* application_name)
{
    frontend.FramebufferWidth = 1280;
    frontend.FramebufferHeight = 720;
	
#if defined(ELSA_VULKAN)
    if (!RendererBackendCreate(RENDERER_BACKEND_API_VULKAN, &frontend.backend)) {
        ELSA_ERROR("RendererBackendCreate <RENDERER_BACKEND_API_VULKAN> failed. Shutting down...");
        return false;
    }
#elif defined(ELSA_METAL)
    if (!RendererBackendCreate(RENDERER_BACKEND_API_METAL, &frontend.backend)) {
        ELSA_ERROR("RendererBackendCreate <RENDERER_BACKEND_API_METAL> failed. Shutting down...");
        return false;
    }
#endif
	
    if (!frontend.backend.Init(&frontend.backend))
        ELSA_FATAL("Failed to initialize renderer backend!");
	
    return true;
}

void RendererFrontendShutdown()
{
    frontend.backend.Shutdown(&frontend.backend);
}

void RendererFrontendResized(u16 width, u16 height)
{
    frontend.FramebufferWidth = (u32)width;
    frontend.FramebufferHeight = (u32)height;
    if (frontend.backend.Resized)
        frontend.backend.Resized(&frontend.backend, width, height);
}

Buffer* RendererFrontendBufferCreate(u64 size, BufferUsage usage)
{
    return frontend.backend.BufferCreate(&frontend.backend, size, usage);
}

void RendererFrontendBufferUpload(void* data, u64 size, Buffer* buffer)
{
    frontend.backend.BufferUpload(&frontend.backend, data, size, buffer);
}

void RendererFrontendBufferFree(Buffer* buffer)
{
    frontend.backend.BufferFree(&frontend.backend, buffer);
}

b8 RendererFrontendRenderPipelineCreate(ShaderPack* pack, DescriptorMap* map, RenderPipeline* pipeline)
{
	return frontend.backend.RenderPipelineCreate(&frontend.backend, pack, map, pipeline);
}

void RendererFrontendRenderPipelineDestroy(RenderPipeline* pipeline)
{
	frontend.backend.RenderPipelineDestroy(&frontend.backend, pipeline);
}

b8 RendererFrontendDescriptorMapCreate(ShaderPack* pack, DescriptorMap* map)
{
    return frontend.backend.DescriptorMapCreate(&frontend.backend, pack, map);
}

void RendererFrontendDescriptorMapDestroy(DescriptorMap* map)
{
    frontend.backend.DescriptorMapDestroy(&frontend.backend, map);
}

b8 RendererFrontendBeginFrame(f32 delta_time)
{
    return frontend.backend.BeginFrame(&frontend.backend, delta_time);
}

b8 RendererFrontendEndFrame(f32 delta_time)
{
    return frontend.backend.EndFrame(&frontend.backend, delta_time);
}