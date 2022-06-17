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

void PlatformConsoleWrite(const char* message, u8 colour)
{
    HANDLE console_handle = GetStdHandle(STD_OUTPUT_HANDLE);
    // FATAL,ERROR,WARN,INFO,DEBUG,TRACE
    static u8 levels[6] = {64, 4, 6, 2, 1, 8};
    SetConsoleTextAttribute(console_handle, levels[colour]);
    OutputDebugStringA(message);
    u64 length = strlen(message);
    LPDWORD number_written = 0;
    WriteConsoleA(GetStdHandle(STD_OUTPUT_HANDLE), message, (DWORD)length, number_written, 0);
}

void PlatformConsoleWriteError(const char* message, u8 colour)
{
    HANDLE console_handle = GetStdHandle(STD_ERROR_HANDLE);
    // FATAL,ERROR,WARN,INFO,DEBUG,TRACE
    static u8 levels[6] = {64, 4, 6, 2, 1, 8};
    SetConsoleTextAttribute(console_handle, levels[colour]);
    OutputDebugStringA(message);
    u64 length = strlen(message);
    LPDWORD number_written = 0;
    WriteConsoleA(GetStdHandle(STD_ERROR_HANDLE), message, (DWORD)length, number_written, 0);
}

#endif