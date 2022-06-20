#include "Platform.h"

#include "Core/Logger.h"
#include "Core/Event.h"
#include "Core/Input.h"

#if defined(ELSA_PLATFORM_WINDOWS)

#include <Windows.h>
#include <windowsx.h>
#include <xinput.h>
#include <shellapi.h>
#include <math.h>

typedef struct Gamepad {
    XINPUT_STATE State;
    b8 Connected;
} Gamepad;

typedef struct PlatformState {
    HINSTANCE hInstance;
    HWND hwnd;

    ApplicationState* app_state;
    HMODULE XInputLib;

    Gamepad Pads[4];
} PlatformState;

typedef DWORD (WINAPI* PFN_XINPUT_GET_STATE)(DWORD dwUserIndex, XINPUT_STATE* pState);
typedef DWORD (WINAPI* PFN_XINPUT_SET_STATE)(DWORD dwUserIndex, XINPUT_VIBRATION* pVibration);

PFN_XINPUT_GET_STATE XInputGetStateProc;
PFN_XINPUT_SET_STATE XInputSetStateProc;

static PlatformState platform_state;

LRESULT CALLBACK PlatformProcessMessages(HWND hwnd, u32 msg, WPARAM w_param, LPARAM l_param);

f32 Normalize(f32 input, f32 min, f32 max)
{
    f32 average = (min + max) / 2;
    f32 range = (max - min) / 2;
    return (input - average) / range;
}

f32 ApplyDeadzone(f32 value, f32 maxValue, f32 deadzone)
{
    if (value < -deadzone)
    {
        value += deadzone; 
    }
    else if (value > deadzone)
    {
        value -= deadzone; 
    }
    else
    {
        return 0; 
    }
    f32 normValue = (float)value / (float)(maxValue - deadzone);
    return max(-1.0f, min(normValue, 1.0f));
}

b8 PlatformInit(ApplicationState* application_state)
{
    platform_state.hInstance = GetModuleHandle(NULL);
    platform_state.app_state = application_state;

    platform_state.XInputLib = LoadLibraryA("xinput1_4.dll");
    if (!platform_state.XInputLib) {
        ELSA_FATAL("Failed to load XInput dll!");
        return false;
    }
    XInputGetStateProc = (PFN_XINPUT_GET_STATE)GetProcAddress(platform_state.XInputLib, "XInputGetState");
    if (!XInputGetStateProc) {
        ELSA_FATAL("Failed to load XInputGetState function!");
        return false;
    }
    XInputSetStateProc = (PFN_XINPUT_SET_STATE)GetProcAddress(platform_state.XInputLib, "XInputSetState");
    if (!XInputSetStateProc) {
        ELSA_FATAL("Failed to load XInputSetState function!");
        return false;
    }

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

    FreeLibrary(platform_state.XInputLib);
}

void PlatformUpdateGamepads()
{
    for (u16 i = 0; i < 4; i++)
    {
        XINPUT_STATE state;
        ZeroMemory(&state, sizeof(XINPUT_STATE));

        DWORD result = XInputGetStateProc(i, &state);
        b8 connected = ERROR_SUCCESS == result;

        if (connected != platform_state.Pads[i].Connected) {
            Event event;
            event.data.u16[0] = i;
            if (connected)
                EventFire(EVENT_CODE_GAMEPAD_CONNECTED, 0, event);
            else
                EventFire(EVENT_CODE_GAMEPAD_DISCONNECTED, 0, event);
        }

        platform_state.Pads[i].Connected = connected;

        if (connected)
        {
            InputProcessGamepadButton(i, GAMEPAD_A,              (state.Gamepad.wButtons & XINPUT_GAMEPAD_A) != 0);
            InputProcessGamepadButton(i, GAMEPAD_B,              (state.Gamepad.wButtons & XINPUT_GAMEPAD_B) != 0);
            InputProcessGamepadButton(i, GAMEPAD_X,              (state.Gamepad.wButtons & XINPUT_GAMEPAD_X) != 0);
            InputProcessGamepadButton(i, GAMEPAD_Y,              (state.Gamepad.wButtons & XINPUT_GAMEPAD_Y) != 0);
            InputProcessGamepadButton(i, GAMEPAD_DPAD_UP,        (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP) != 0);
            InputProcessGamepadButton(i, GAMEPAD_DPAD_DOWN,      (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN) != 0);
            InputProcessGamepadButton(i, GAMEPAD_DPAD_LEFT,      (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT) != 0);
            InputProcessGamepadButton(i, GAMEPAD_DPAD_RIGHT,     (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT) != 0);
            InputProcessGamepadButton(i, GAMEPAD_START,          (state.Gamepad.wButtons & XINPUT_GAMEPAD_START) != 0);
            InputProcessGamepadButton(i, GAMEPAD_BACK,           (state.Gamepad.wButtons & XINPUT_GAMEPAD_BACK) != 0);
            InputProcessGamepadButton(i, GAMEPAD_LEFT_THUMB,     (state.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_THUMB) != 0);
            InputProcessGamepadButton(i, GAMEPAD_LEFT_SHOULDER,  (state.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER) != 0);
            InputProcessGamepadButton(i, GAMEPAD_RIGHT_THUMB,    (state.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_THUMB) != 0);
            InputProcessGamepadButton(i, GAMEPAD_RIGHT_SHOULDER, (state.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER) != 0);

            f32 left_trigger = (f32)state.Gamepad.bLeftTrigger / 255;
            f32 right_trigger = (f32)state.Gamepad.bRightTrigger / 255;

            InputProcessGamepadTrigger(i, left_trigger, GAMEPAD_ANALOG_LEFT);
            InputProcessGamepadTrigger(i, right_trigger, GAMEPAD_ANALOG_RIGHT);

            f32 normLX = Normalize((f32)state.Gamepad.sThumbLX, -32767, 32767);
            f32 normLY = Normalize((f32)state.Gamepad.sThumbLY, -32767, 32767);

            f32 normRX = Normalize((f32)state.Gamepad.sThumbRX, -32767, 32767);
            f32 normRY = Normalize((f32)state.Gamepad.sThumbRY, -32767, 32767);

            f32 lx = 0.0f;
            f32 ly = 0.0f;

            f32 rx = 0.0f;
            f32 ry = 0.0f;

            if (XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE <= 1.0f || XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE <= 1.0f)
            {
                lx = ApplyDeadzone(normLX,  1.0f, XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE);
                ly = ApplyDeadzone(normLY,  1.0f, XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE);
                rx = ApplyDeadzone(normRX,  1.0f, XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE);
                ry = ApplyDeadzone(normRY,  1.0f, XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE);
            }
            else
            {
                lx = ApplyDeadzone(normLX,  1.0f, Normalize(XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE, SHRT_MIN, SHRT_MAX));
                ly = ApplyDeadzone(normLY,  1.0f, Normalize(XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE, SHRT_MIN, SHRT_MAX));
                rx = ApplyDeadzone(normRX,  1.0f, Normalize(XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE, SHRT_MIN, SHRT_MAX));
                ry = ApplyDeadzone(normRY,  1.0f, Normalize(XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE, SHRT_MIN, SHRT_MAX));
            }

            InputProcessGamepadJoystick(i, lx, ly, GAMEPAD_ANALOG_LEFT);
            InputProcessGamepadJoystick(i, rx, ry, GAMEPAD_ANALOG_RIGHT);

            XINPUT_VIBRATION vibration;
            InputGetGamepadVibration(i, &vibration.wRightMotorSpeed, &vibration.wLeftMotorSpeed);
            XInputSetStateProc(i, &vibration);

            platform_state.Pads[i].State = state;
        }
    }
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
        case WM_KEYDOWN:
        case WM_SYSKEYDOWN:
        case WM_KEYUP:
        case WM_SYSKEYUP: {
            b8 pressed = (msg == WM_KEYDOWN || msg == WM_SYSKEYDOWN);
            Keys key = (u16)w_param;

            b8 is_extended = (HIWORD(l_param) & KF_EXTENDED) == KF_EXTENDED;

            if (w_param == VK_MENU) {
                key = is_extended ? KEY_RALT : KEY_LALT;
            } else if (w_param == VK_SHIFT) {
                u32 left_shift = MapVirtualKey(VK_LSHIFT, MAPVK_VK_TO_VSC);
                u32 scancode = ((l_param & (0xFF << 16)) >> 16);
                key = scancode == left_shift ? KEY_LSHIFT : KEY_RSHIFT;
            } else if (w_param == VK_CONTROL) {
                key = is_extended ? KEY_RCONTROL : KEY_LCONTROL;
            }

            InputProcessKey(key, pressed);

            return 0;
        }
        case WM_MOUSEMOVE: {
            // Mouse move
            i32 x_position = GET_X_LPARAM(l_param);
            i32 y_position = GET_Y_LPARAM(l_param);

            InputProcessMouseMove(x_position, y_position);
        } break;
        case WM_MOUSEWHEEL: {
            i32 z_delta = GET_WHEEL_DELTA_WPARAM(w_param);
            if (z_delta != 0) {
                z_delta = (z_delta < 0) ? -1 : 1;
                InputProcessMouseWheel(z_delta);
            }
        } break;
        case WM_LBUTTONDOWN:
        case WM_MBUTTONDOWN:
        case WM_RBUTTONDOWN:
        case WM_LBUTTONUP:
        case WM_MBUTTONUP:
        case WM_RBUTTONUP: {
            b8 pressed = msg == WM_LBUTTONDOWN || msg == WM_RBUTTONDOWN || msg == WM_MBUTTONDOWN;
            Buttons mouse_button = BUTTON_MAX_BUTTONS;
            switch (msg) {
                case WM_LBUTTONDOWN:
                case WM_LBUTTONUP:
                    mouse_button = BUTTON_LEFT;
                    break;
                case WM_MBUTTONDOWN:
                case WM_MBUTTONUP:
                    mouse_button = BUTTON_MIDDLE;
                    break;
                case WM_RBUTTONDOWN:
                case WM_RBUTTONUP:
                    mouse_button = BUTTON_RIGHT;
                    break;
            }

            // Pass over to the input subsystem.
            if (mouse_button != BUTTON_MAX_BUTTONS) {
                InputProcessButton(mouse_button, pressed);
            }
        } break;
    }

    return DefWindowProcA(hwnd, msg, w_param, l_param);
}

#endif