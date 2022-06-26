#include "MetalBackend.h"

#if defined(ELSA_METAL)

b8 MetalRendererBackendInit(RendererBackend* backend)
{
    return true;
}

void MetalRendererBackendShutdown(RendererBackend* backend)
{

}

void MetalRendererBackendResized(RendererBackend* backend, u16 width, u16 height)
{

}

b8 MetalRendererBackendBeginFrame(RendererBackend* backend, f32 delta_time)
{
    return true;
}

b8 MetalRendererBackendEndFrame(RendererBackend* backend, f32 delta_time)
{
    return true;
}

#endif