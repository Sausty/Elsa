#include "MetalBackend.h"

#include <Platform/Platform.h>
#include <Core/Logger.h>

#if defined(ELSA_METAL)

#include "MetalTypes.h"

#include <Foundation/Foundation.h>
#include <Cocoa/Cocoa.h>
#include <QuartzCore/QuartzCore.h>

static MetalContext context;

b8 MetalRendererBackendInit(RendererBackend* backend)
{
    context.Layer = (CAMetalLayer*)PlatformGetWindowView();
    context.Device = MTLCreateSystemDefaultDevice();
    if (!context.Device) {
        ELSA_ERROR("MTLCreateSystemDefaultDevice failed. Shutting down...");
        return false;
    }

    context.Layer.device = context.Device;
    context.Layer.pixelFormat = MTLPixelFormatBGRA8Unorm;

    NSString* device_name = context.Device.name;
    ELSA_DEBUG("<MetalRendererBackendInit> Using GPU: %s", [device_name UTF8String]);

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