#include "Platform.h"

#if defined(ELSA_PLATFORM_WINDOWS)

#include <Windows.h>

void* PlatformAlloc(u64 size)
{
    return VirtualAlloc(0, size, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
}

void PlatformFree(void* block)
{
    VirtualFree(block, 0, MEM_RELEASE);
}

void PlatformZeroMemory(void* block, u64 size)
{
    ZeroMemory(block, size);
}

void PlatformSetMemory(void* block, i32 value, u64 size)
{
    FillMemory(block, size, value);
}

void PlatformCopyMemory(void* dest, const void* source, u64 size)
{
    CopyMemory(dest, source, size);
}

void PlatformMoveMemory(void* dest, const void* source, u64 size)
{
    MoveMemory(dest, source, size);
}

#endif