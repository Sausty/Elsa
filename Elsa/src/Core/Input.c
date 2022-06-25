#include "Input.h"

#include <Platform/Platform.h>
#include <Core/Event.h>

typedef struct KeyboardState {
    b8 Keys[256];
} KeyboardState;

typedef struct MouseState {
    i16 X;
    i16 Y;
    u8 Buttons[BUTTON_MAX_BUTTONS];
} MouseState;

typedef struct ControllerState {
    u8 Buttons[GAMEPAD_MAX_BUTTONS];

    f32 Triggers[2];
    f32 Joysticks[2][2]; // [analog][x/y]
    f32 Vibration[2];
} ControllerState;

typedef struct InputState {
    KeyboardState KeyboardCurrent;
    KeyboardState KeyboardPrevious;
    MouseState MouseCurrent;
    MouseState MousePrevious;
    ControllerState GamepadCurrent[4];
    ControllerState GamepadPrevious[4];
} InputState;

static InputState state;

void InputUpdate()
{
    PlatformCopyMemory(&state.KeyboardPrevious, &state.KeyboardCurrent, sizeof(KeyboardState));
    PlatformCopyMemory(&state.MousePrevious, &state.MouseCurrent, sizeof(MouseState));

    for (i32 i = 0; i < 4; i++) {
        PlatformCopyMemory(&state.GamepadPrevious[i], &state.GamepadCurrent[i], sizeof(ControllerState));
    }
}

void InputProcessKey(Keys key, b8 pressed)
{
    if (state.KeyboardCurrent.Keys[key] != pressed) {
        state.KeyboardCurrent.Keys[key] = pressed;

        Event event;
        event.data.u16[0] = key;
        EventFire(pressed ? EVENT_CODE_KEY_PRESSED : EVENT_CODE_KEY_RELEASED, 0, event);
    }
}

void InputProcessButton(Buttons button, b8 pressed)
{
    if (state.MouseCurrent.Buttons[button] != pressed) {
        state.MouseCurrent.Buttons[button] = pressed;

        Event event;
        event.data.u16[0] = button;
        EventFire(pressed ? EVENT_CODE_BUTTON_PRESSED : EVENT_CODE_BUTTON_RELEASED, 0, event);
    }
}

void InputProcessMouseMove(i16 x, i16 y)
{
    if (state.MouseCurrent.X != x || state.MouseCurrent.Y != y)
    {
        state.MouseCurrent.X = x;
        state.MouseCurrent.Y = y;

        Event event;
        event.data.u16[0] = x;
        event.data.u16[1] = y;
        EventFire(EVENT_CODE_MOUSE_MOVED, 0, event);
    }
}

void InputProcessMouseWheel(i8 z_delta)
{
    Event event;
    event.data.u8[0] = z_delta;
    EventFire(EVENT_CODE_MOUSE_WHEEL, 0, event);
}

b8 InputIsKeyDown(Keys key)
{
    return state.KeyboardCurrent.Keys[key] == true;
}

b8 InputIsKeyUp(Keys key)
{
    return state.KeyboardCurrent.Keys[key] == false;
}

b8 InputWasKeyDown(Keys key)
{
    return state.KeyboardPrevious.Keys[key] == true;
}

b8 InputWasKeyUp(Keys key)
{
    return state.KeyboardPrevious.Keys[key] == false;
}

b8 InputIsButtonDown(Buttons button)
{
    return state.MouseCurrent.Buttons[button] == true;
}

b8 InputIsButtonUp(Buttons button)
{
    return state.MouseCurrent.Buttons[button] == false;
}

b8 InputWasButtonDown(Buttons button)
{
    return state.MousePrevious.Buttons[button] == true;
}

b8 InputWasButtonUp(Buttons button)
{
    return state.MousePrevious.Buttons[button] == false;
}

void InputGetMousePosition(i32* x, i32* y)
{
    *x = state.MouseCurrent.X;
    *y = state.MouseCurrent.Y;
}

void InputGetPreviousMousePosition(i32* x, i32* y)
{
    *x = state.MousePrevious.X;
    *y = state.MousePrevious.Y;
}

b8 InputIsGamepadButtonPressed(i32 index, GamepadButtons button)
{
    return state.GamepadCurrent[index].Buttons[button] == true;
}

b8 InputIsGamepadButtonReleased(i32 index, GamepadButtons button)
{
    return state.GamepadCurrent[index].Buttons[button] == false;
}

b8 InputWasGamepadButtonPressed(i32 index, GamepadButtons button)
{
    return state.GamepadPrevious[index].Buttons[button] == true;
}

b8 InputWasGamepadButtonReleased(i32 index, GamepadButtons button)
{
    return state.GamepadPrevious[index].Buttons[button] == false;
}

f32 InputGetGamepadTrigger(i32 index, GamepadAnalog analog)
{
    return state.GamepadCurrent[index].Triggers[analog];
}

void InputGetGamepadJoystick(i32 index, GamepadAnalog analog, f32* x, f32* y)
{
    *x = state.GamepadCurrent[index].Joysticks[analog][0];
    *y = state.GamepadCurrent[index].Joysticks[analog][1];
}

void InputSetGamepadVibration(i32 index, f32 right, f32 left)
{
    state.GamepadCurrent[index].Vibration[0] = right;
    state.GamepadCurrent[index].Vibration[1] = left;
}

void InputResetGamepadVibration(i32 index)
{
    InputSetGamepadVibration(index, 0, 0);
}

void InputGetGamepadVibration(i32 index, f32* right, f32* left)
{
    *right = state.GamepadCurrent[index].Vibration[0];
    *left = state.GamepadCurrent[index].Vibration[1];
}

void InputProcessGamepadButton(i32 index, GamepadButtons button, b8 pressed)
{
    state.GamepadCurrent[index].Buttons[button] = pressed;

    Event event;
    event.data.u16[0] = button;
    EventFire(pressed ? EVENT_CODE_GAMEPAD_BUTTON_PRESSED : EVENT_CODE_GAMEPAD_BUTTON_RELEASED, 0, event);
}

void InputProcessGamepadTrigger(i32 index, f32 value, GamepadAnalog analog)
{
    state.GamepadCurrent[index].Triggers[analog] = value;
}

void InputProcessGamepadJoystick(i32 index, f32 x, f32 y, GamepadAnalog analog)
{
    state.GamepadCurrent[index].Joysticks[analog][0] = x;
    state.GamepadCurrent[index].Joysticks[analog][1] = y;
}