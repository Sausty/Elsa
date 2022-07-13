# Elsa Engine

I am making this engine in order to learn more about engine architecture and overall programming tricks in C. This engine follows
the tutorial series of the Kohi Game Engine (https://www.youtube.com/watch?v=dHPuU-DJoBM&list=PLv8Ddw9K0JPg1BEO-RS-0MYs423cvLVtj)

## Platform specific features

|         | Renderer             | Audio                                | Platform Interface |
|---------|----------------------|--------------------------------------|--------------------|
| Windows | Supported (Vulkan)   | Supported (XAudio2)                  | Supported (Win32)  |
| MacOS   | Unsupported (Metal)  | Unsupported (AVFoundation/CoreAudio) | Unsupported (Cocoa)  |
| Linux   | Unsupported (Vulkan) | Unsupported (OpenSound)              | Unsupported (XCB)  |

## Dependencies

- [dr_wav](https://github.com/mackron/dr_libs/blob/master/dr_wav.h)
- [VMA](https://github.com/GPUOpen-LibrariesAndSDKs/VulkanMemoryAllocator)
- [SPIRV-Reflect](https://github.com/KhronosGroup/SPIRV-Reflect)