#include "Platform.h"
#include "Core/Logger.h"
#include "Core/Event.h"

#if defined(ELSA_PLATFORM_WINDOWS)

#include <Windows.h>

typedef struct PlatformState {
    HINSTANCE hInstance;
    HWND hwnd;

    ApplicationState* app_state;
} PlatformState;

static PlatformState platform_state;

LRESULT CALLBACK PlatformProcessMessages(HWND hwnd, u32 msg, WPARAM w_param, LPARAM l_param);

b8 PlatformInit(ApplicationState* application_state)
{
    platform_state.hInstance = GetModuleHandle(NULL);
    platform_state.app_state = application_state;

    HICON icon = LoadIcon(platform_state.hInstance, IDI_APPLICATION);
    
    WNDCLASSA wc;
    PlatformSetMemory(&wc, 0, sizeof(wc));
    wc.style = CS_DBLCLKS;
    wc.lpfnWndProc = PlatformProcessMessages;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = platform_state.hInstance;
    wc.hIcon = icon;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = NULL;
    wc.lpszClassName = "ElsaWindowClass";

    if (!RegisterClassA(&wc)) {
        MessageBoxA(0, "Window registration failed", "Error", MB_ICONEXCLAMATION | MB_OK);
        return false;
    }

    // Create window
    u32 client_x = application_state->PosX;
    u32 client_y = application_state->PosY;
    u32 client_width = application_state->Width;
    u32 client_height = application_state->Height;

    u32 window_x = client_x;
    u32 window_y = client_y;
    u32 window_width = client_width;
    u32 window_height = client_height;

    u32 window_style = WS_OVERLAPPED | WS_SYSMENU | WS_CAPTION;
    u32 window_ex_style = WS_EX_APPWINDOW;

    window_style |= WS_MAXIMIZEBOX;
    window_style |= WS_MINIMIZEBOX;
    window_style |= WS_THICKFRAME;

    // Obtain the size of the border.
    RECT border_rect = {0, 0, 0, 0};
    AdjustWindowRectEx(&border_rect, window_style, 0, window_ex_style);

    // In this case, the border rectangle is negative.
    window_x += border_rect.left;
    window_y += border_rect.top;

    // Grow by the size of the OS border.
    window_width += border_rect.right - border_rect.left;
    window_height += border_rect.bottom - border_rect.top;

    HWND handle = CreateWindowExA(
        window_ex_style, "ElsaWindowClass", application_state->Name,
        window_style, window_x, window_y, window_width, window_height,
        0, 0, platform_state.hInstance, 0);

    if (handle == 0) {
        MessageBoxA(NULL, "Window creation failed!", "Error!", MB_ICONEXCLAMATION | MB_OK);

        ELSA_FATAL("Window creation failed!");
        return false;
    } else {
        platform_state.hwnd = handle;
    }

    b8 should_activate = true;  
    i32 show_window_command_flags = should_activate ? SW_SHOW : SW_SHOWNOACTIVATE;
    // If initially minimized, use SW_MINIMIZE : SW_SHOWMINNOACTIVE;
    // If initially maximized, use SW_SHOWMAXIMIZED : SW_MAXIMIZE
    ShowWindow(platform_state.hwnd, show_window_command_flags);

    return true;
}

void PlatformExit()
{
    if (platform_state.hwnd)
        DestroyWindow(platform_state.hwnd);
}

b8 PlatformPumpMessages()
{
    MSG msg;
    while (PeekMessageA(&msg, platform_state.hwnd, 0, 0, PM_REMOVE)) {
        TranslateMessage(&msg);
        DispatchMessageA(&msg);
    }

    return true;
}

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

LRESULT CALLBACK PlatformProcessMessages(HWND hwnd, u32 msg, WPARAM w_param, LPARAM l_param)
{
    switch (msg) {
        case WM_ERASEBKGND: {
            // Notify the OS that erasing will be handled by the application to prevent flicker.
            return 1;
        }
        case WM_CLOSE: {
            Event data = {};
            EventFire(EVENT_CODE_APPLICATION_QUIT, 0, data);
            return 0;
        }
        case WM_DESTROY: {
            PostQuitMessage(0);
            return 0;
        }
        case WM_SIZE: {
            RECT r;
            GetClientRect(hwnd, &r);
            u32 width = r.right - r.left;
            u32 height = r.bottom - r.top;

            Event data = {};
            data.data.u16[0] = (u16)width;
            data.data.u16[1] = (u16)height;
            EventFire(EVENT_CODE_RESIZED, 0, data);
        }
        // TODO(milo): Input
    }

    return DefWindowProcA(hwnd, msg, w_param, l_param);
}

#endif