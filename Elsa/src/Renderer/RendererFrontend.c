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

b8 RendererFrontendRenderPipelineCreate(ShaderPack* pack, RenderPipeline* pipeline)
{
	return frontend.backend.RenderPipelineCreate(&frontend.backend, pack, pipeline);
}

void RendererFrontendRenderPipelineDestroy(RenderPipeline* pipeline)
{
	frontend.backend.RenderPipelineDestroy(&frontend.backend, pipeline);
}

b8 RendererFrontendDrawFrame(f32 delta_time)
{
    if (frontend.backend.BeginFrame(&frontend.backend, delta_time)) {
		
        b8 result = frontend.backend.EndFrame(&frontend.backend, delta_time);
        if (!result) {
            ELSA_ERROR("RendererBackendEndFrame failed. Application shutting down...");
            return false;
        }
    }
	
    return true;
}