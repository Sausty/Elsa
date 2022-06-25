/**
 * @file Input.h
 * @author Milo Heinrich (MikuoH15TH@gmail.com)
 * @brief This file contains everything having to do with input on deskop
 * environments from keyboards and mice. Touch controls will
 * likely be handled separately at a future date.
 * @version 1.0
 * @date 2022-06-19
 */
#ifndef ELSA_INPUT_H
#define ELSA_INPUT_H

#include <Defines.h>

/**
 * @brief Represents available controller buttons.
 */
typedef enum GamepadButtons {
    /** @brief The up direction on the DPad */
    GAMEPAD_DPAD_UP,
    /** @brief The down direction on the DPad */
    GAMEPAD_DPAD_DOWN,
    /** @brief The left direction on the DPad */
    GAMEPAD_DPAD_LEFT,
    /** @brief The right direction on the DPad */
    GAMEPAD_DPAD_RIGHT,
    /** @brief The start button */
    GAMEPAD_START,
    /** @brief The back button */
    GAMEPAD_BACK,
    /** @brief The left thumb */
    GAMEPAD_LEFT_THUMB,
    /** @brief The right thumb */
    GAMEPAD_RIGHT_THUMB,
    /** @brief The left shoulder */
    GAMEPAD_LEFT_SHOULDER,
    /** @brief The right shoulder */
    GAMEPAD_RIGHT_SHOULDER,
    /** @brief The A button */
    GAMEPAD_A,
    /** @brief The B button */
    GAMEPAD_B,
    /** @brief The X button */
    GAMEPAD_X,
    /** @brief The Y button */
    GAMEPAD_Y,
    GAMEPAD_MAX_BUTTONS
} GamepadButtons;

/**
 * @brief Represents analog gamepad inputs for triggers and analog sticks.
 */
typedef enum GamepadAnalog {
    /** @brief The left analog input */
    GAMEPAD_ANALOG_LEFT,
    /** @brief The right analog input */
    GAMEPAD_ANALOG_RIGHT
} GamepadAnalog;

/**
 * @brief Represents available mouse buttons.
 */
typedef enum Buttons {
    /** @brief The left mouse button */
    BUTTON_LEFT,
    /** @brief The right mouse button */
    BUTTON_RIGHT,
    /** @brief The middle mouse button (typically the wheel) */
    BUTTON_MIDDLE,
    BUTTON_MAX_BUTTONS
} Buttons;

/**
 * @brief Represents available keyboard keys.
 */
typedef enum Keys {
    /** @brief The backspace key. */
    KEY_BACKSPACE = 0x08,
    /** @brief The enter key. */
    KEY_ENTER = 0x0D,
    /** @brief The tab key. */
    KEY_TAB = 0x09,
    /** @brief The shift key. */
    KEY_SHIFT = 0x10,
    /** @brief The Control/Ctrl key. */
    KEY_CONTROL = 0x11,

    /** @brief The pause key. */
    KEY_PAUSE = 0x13,
    /** @brief The Caps Lock key. */
    KEY_CAPITAL = 0x14,

    /** @brief The Escape key. */
    KEY_ESCAPE = 0x1B,

    KEY_CONVERT = 0x1C,
    KEY_NONCONVERT = 0x1D,
    KEY_ACCEPT = 0x1E,
    KEY_MODECHANGE = 0x1F,

    /** @brief The spacebar key. */
    KEY_SPACE = 0x20,
    KEY_PRIOR = 0x21,
    KEY_NEXT = 0x22,
    /** @brief The end key. */
    KEY_END = 0x23,
    /** @brief The home key. */
    KEY_HOME = 0x24,
    /** @brief The left arrow key. */
    KEY_LEFT = 0x25,
    /** @brief The up arrow key. */
    KEY_UP = 0x26,
    /** @brief The right arrow key. */
    KEY_RIGHT = 0x27,
    /** @brief The down arrow key. */
    KEY_DOWN = 0x28,
    KEY_SELECT = 0x29,
    KEY_PRINT = 0x2A,
    KEY_EXECUTE = 0x2B,
    KEY_SNAPSHOT = 0x2C,
    /** @brief The insert key. */
    KEY_INSERT = 0x2D,
    /** @brief The delete key. */
    KEY_DELETE = 0x2E,
    KEY_HELP = 0x2F,

    /** @brief The 0 key */
    KEY_0 = 0x30,
    /** @brief The 1 key */
    KEY_1 = 0x31,
    /** @brief The 2 key */
    KEY_2 = 0x32,
    /** @brief The 3 key */
    KEY_3 = 0x33,
    /** @brief The 4 key */
    KEY_4 = 0x34,
    /** @brief The 5 key */
    KEY_5 = 0x35,
    /** @brief The 6 key */
    KEY_6 = 0x36,
    /** @brief The 7 key */
    KEY_7 = 0x37,
    /** @brief The 8 key */
    KEY_8 = 0x38,
    /** @brief The 9 key */
    KEY_9 = 0x39,

    /** @brief The A key. */
    KEY_A = 0x41,
    /** @brief The B key. */
    KEY_B = 0x42,
    /** @brief The C key. */
    KEY_C = 0x43,
    /** @brief The D key. */
    KEY_D = 0x44,
    /** @brief The E key. */
    KEY_E = 0x45,
    /** @brief The F key. */
    KEY_F = 0x46,
    /** @brief The G key. */
    KEY_G = 0x47,
    /** @brief The H key. */
    KEY_H = 0x48,
    /** @brief The I key. */
    KEY_I = 0x49,
    /** @brief The J key. */
    KEY_J = 0x4A,
    /** @brief The K key. */
    KEY_K = 0x4B,
    /** @brief The L key. */
    KEY_L = 0x4C,
    /** @brief The M key. */
    KEY_M = 0x4D,
    /** @brief The N key. */
    KEY_N = 0x4E,
    /** @brief The O key. */
    KEY_O = 0x4F,
    /** @brief The P key. */
    KEY_P = 0x50,
    /** @brief The Q key. */
    KEY_Q = 0x51,
    /** @brief The R key. */
    KEY_R = 0x52,
    /** @brief The S key. */
    KEY_S = 0x53,
    /** @brief The T key. */
    KEY_T = 0x54,
    /** @brief The U key. */
    KEY_U = 0x55,
    /** @brief The V key. */
    KEY_V = 0x56,
    /** @brief The W key. */
    KEY_W = 0x57,
    /** @brief The X key. */
    KEY_X = 0x58,
    /** @brief The Y key. */
    KEY_Y = 0x59,
    /** @brief The Z key. */
    KEY_Z = 0x5A,

    /** @brief The left Windows/Super key. */
    KEY_LWIN = 0x5B,
    /** @brief The right Windows/Super key. */
    KEY_RWIN = 0x5C,
    KEY_APPS = 0x5D,

    /** @brief The sleep key. */
    KEY_SLEEP = 0x5F,

    /** @brief The numberpad 0 key. */
    KEY_NUMPAD0 = 0x60,
    /** @brief The numberpad 1 key. */
    KEY_NUMPAD1 = 0x61,
    /** @brief The numberpad 2 key. */
    KEY_NUMPAD2 = 0x62,
    /** @brief The numberpad 3 key. */
    KEY_NUMPAD3 = 0x63,
    /** @brief The numberpad 4 key. */
    KEY_NUMPAD4 = 0x64,
    /** @brief The numberpad 5 key. */
    KEY_NUMPAD5 = 0x65,
    /** @brief The numberpad 6 key. */
    KEY_NUMPAD6 = 0x66,
    /** @brief The numberpad 7 key. */
    KEY_NUMPAD7 = 0x67,
    /** @brief The numberpad 8 key. */
    KEY_NUMPAD8 = 0x68,
    /** @brief The numberpad 9 key. */
    KEY_NUMPAD9 = 0x69,
    /** @brief The numberpad multiply key. */
    KEY_MULTIPLY = 0x6A,
    /** @brief The numberpad add key. */
    KEY_ADD = 0x6B,
    /** @brief The numberpad separator key. */
    KEY_SEPARATOR = 0x6C,
    /** @brief The numberpad subtract key. */
    KEY_SUBTRACT = 0x6D,
    /** @brief The numberpad decimal key. */
    KEY_DECIMAL = 0x6E,
    /** @brief The numberpad divide key. */
    KEY_DIVIDE = 0x6F,

    /** @brief The F1 key. */
    KEY_F1 = 0x70,
    /** @brief The F2 key. */
    KEY_F2 = 0x71,
    /** @brief The F3 key. */
    KEY_F3 = 0x72,
    /** @brief The F4 key. */
    KEY_F4 = 0x73,
    /** @brief The F5 key. */
    KEY_F5 = 0x74,
    /** @brief The F6 key. */
    KEY_F6 = 0x75,
    /** @brief The F7 key. */
    KEY_F7 = 0x76,
    /** @brief The F8 key. */
    KEY_F8 = 0x77,
    /** @brief The F9 key. */
    KEY_F9 = 0x78,
    /** @brief The F10 key. */
    KEY_F10 = 0x79,
    /** @brief The F11 key. */
    KEY_F11 = 0x7A,
    /** @brief The F12 key. */
    KEY_F12 = 0x7B,
    /** @brief The F13 key. */
    KEY_F13 = 0x7C,
    /** @brief The F14 key. */
    KEY_F14 = 0x7D,
    /** @brief The F15 key. */
    KEY_F15 = 0x7E,
    /** @brief The F16 key. */
    KEY_F16 = 0x7F,
    /** @brief The F17 key. */
    KEY_F17 = 0x80,
    /** @brief The F18 key. */
    KEY_F18 = 0x81,
    /** @brief The F19 key. */
    KEY_F19 = 0x82,
    /** @brief The F20 key. */
    KEY_F20 = 0x83,
    /** @brief The F21 key. */
    KEY_F21 = 0x84,
    /** @brief The F22 key. */
    KEY_F22 = 0x85,
    /** @brief The F23 key. */
    KEY_F23 = 0x86,
    /** @brief The F24 key. */
    KEY_F24 = 0x87,

    /** @brief The number lock key. */
    KEY_NUMLOCK = 0x90,

    /** @brief The scroll lock key. */
    KEY_SCROLL = 0x91,

    /** @brief The numberpad equal key. */
    KEY_NUMPAD_EQUAL = 0x92,

    /** @brief The left shift key. */
    KEY_LSHIFT = 0xA0,
    /** @brief The right shift key. */
    KEY_RSHIFT = 0xA1,
    /** @brief The left control key. */
    KEY_LCONTROL = 0xA2,
    /** @brief The right control key. */
    KEY_RCONTROL = 0xA3,
    /** @brief The left alt key. */
    KEY_LALT = 0xA4,
    /** @brief The right alt key. */
    KEY_RALT = 0xA5,

    /** @brief The semicolon key. */
    KEY_SEMICOLON = 0xBA,
    /** @brief The plus key. */
    KEY_PLUS = 0xBB,
    /** @brief The comma key. */
    KEY_COMMA = 0xBC,
    /** @brief The minus key. */
    KEY_MINUS = 0xBD,
    /** @brief The period key. */
    KEY_PERIOD = 0xBE,
    /** @brief The slash key. */
    KEY_SLASH = 0xBF,

    /** @brief The grave key. */
    KEY_GRAVE = 0xC0,

    KEYS_MAX_KEYS
} Keys;

/**
 * @brief Updates the input system every frame.
 */
ELSA_API void InputUpdate();

/**
 * @brief Indicates if the given key is currently pressed down.
 * @param key They key to be checked.
 * @returns True if currently pressed; otherwise false.
 */
ELSA_API b8 InputIsKeyDown(Keys key);

/**
 * @brief Indicates if the given key is NOT currently pressed down.
 * @param key They key to be checked.
 * @returns True if currently released; otherwise false.
 */
ELSA_API b8 InputIsKeyUp(Keys key);

/**
 * @brief Indicates if the given key was previously pressed down on the last frame.
 * @param key They key to be checked.
 * @returns True if was previously pressed; otherwise false.
 */
ELSA_API b8 InputWasKeyDown(Keys key);

/**
 * @brief Indicates if the given key was previously pressed down in the last frame.
 * @param key They key to be checked.
 * @returns True if was previously pressed; otherwise false.
 */
ELSA_API b8 InputWasKeyUp(Keys key);

/**
 * @brief Sets the state for the given key.
 * @param key The key to be processed.
 * @param pressed Indicates whether the key is currently pressed.
 */
ELSA_API void InputProcessKey(Keys key, b8 pressed);

/**
 * @brief Indicates if the given mouse button is currently pressed.
 * @param button The button to check.
 * @returns True if currently pressed; otherwise false.
 */
ELSA_API b8 InputIsButtonDown(Buttons button);

/**
 * @brief Indicates if the given mouse button is currently released.
 * @param button The button to check.
 * @returns True if currently released; otherwise false.
 */
ELSA_API b8 InputIsButtonUp(Buttons button);

/**
 * @brief Indicates if the given mouse button was previously pressed in the last frame.
 * @param button The button to check.
 * @returns True if previously pressed; otherwise false.
 */
ELSA_API b8 InputWasButtonDown(Buttons button);

/**
 * @brief Indicates if the given mouse button was previously released in the last frame.
 * @param button The button to check.
 * @returns True if previously released; otherwise false.
 */
ELSA_API b8 InputWasButtonUp(Buttons button);

/** 
 * @brief Obtains the current mouse position.
 * @param x A pointer to hold the current mouse position on the x-axis.
 * @param y A pointer to hold the current mouse position on the y-axis.
 */
ELSA_API void InputGetMousePosition(i32* x, i32* y);

/** 
 * @brief Obtains the previous mouse position.
 * @param x A pointer to hold the previous mouse position on the x-axis.
 * @param y A pointer to hold the previous mouse position on the y-axis.
 */
ELSA_API void InputGetPreviousMousePosition(i32* x, i32* y);

/**
 * @brief Sets the press state of the given mouse button.
 * @param button The mouse button whose state to set.
 * @param pressed Indicates if the mouse button is currently pressed.
 */
ELSA_API void InputProcessButton(Buttons button, b8 pressed);

/**
 * @brief Sets the current position of the mouse to the given x and y positions.
 * Also updates the previous position beforehand.
 */
ELSA_API void InputProcessMouseMove(i16 x, i16 y);

/**
 * @brief Processes mouse wheel scrolling.
 * @param z_delta The amount of scrolling which occurred on the z axis (mouse wheel)
 */
ELSA_API void InputProcessMouseWheel(i8 z_delta);

/**
 * @brief Indicates if the given gamepad button is currently pressed.
 * @param index The index of the gamepad.
 * @param button The button to check.
 * @returns True if currently pressed; otherwise false.
 */
ELSA_API b8 InputIsGamepadButtonPressed(i32 index, GamepadButtons button);

/**
 * @brief Indicates if the given gamepad button is currently released.
 * @param index The index of the gamepad.
 * @param button The button to check.
 * @returns True if currently released; otherwise false.
 */
ELSA_API b8 InputIsGamepadButtonReleased(i32 index, GamepadButtons button);

/**
 * @brief Indicates if the given gamepad button was pressed in the last frame.
 * @param index The index of the gamepad.
 * @param button The button to check.
 * @returns True if was pressed; otherwise false.
 */
ELSA_API b8 InputWasGamepadButtonPressed(i32 index, GamepadButtons button);

/**
 * @brief Indicates if the given gamepad button was released in the last frame.
 * @param index The index of the gamepad.
 * @param button The button to check.
 * @returns True if was released; otherwise false.
 */
ELSA_API b8 InputWasGamepadButtonReleased(i32 index, GamepadButtons button);

/**
 * @brief Returns the analog value of the requested trigger.
 * @param index The index of the gamepad.
 * @param analog The position of the trigger.
 * @returns The analog value of the trigger.
 */
ELSA_API f32 InputGetGamepadTrigger(i32 index, GamepadAnalog analog);

/**
 * @brief Gets the joystick values of the requested gamepad.
 * @param index The index of the gamepad.
 * @param analog The position of the joystick.
 * @param x A pointer to hold the X value of the joystick.
 * @param y A pointer to hold the Y value of the joystick.
 */
ELSA_API void InputGetGamepadJoystick(i32 index, GamepadAnalog analog, f32* x, f32* y);

/**
 * @brief Sets the vibration values of the requested gamepad.
 * @param index The index of the gamepad.
 * @param right The speed of the right motor.
 * @param left The speed of the left motor.
 */
ELSA_API void InputSetGamepadVibration(i32 index, f32 right, f32 left);

/**
 * @brief Resets the vibration of the requested gamepad.
 * @param index The index of the gamepad.
 */
ELSA_API void InputResetGamepadVibration(i32 index);

/**
 * @brief Gets the vibration values of the requested gamepad.
 * @param index The index of the gamepad.
 * @param right A pointer to hold the right motor value.
 * @param left A pointer to hold the left motor value.
 */
ELSA_API void InputGetGamepadVibration(i32 index, f32* right, f32* left);

/**
 * @brief Sets the press state of the given gamepad button.
 * @param index The gamepad index whose state to set.
 * @param button The gamepad button whose state to set.
 * @param pressed Indicates if the gamepad button is currently pressed.
 */
ELSA_API void InputProcessGamepadButton(i32 index, GamepadButtons button, b8 pressed);

/**
 * @brief Sets the battery information of the given gamepad.
 * @param index The gamepad index whose state to set.
 * @param value The battery value.
 */
ELSA_API void InputProcessGamepadBattery(i32 index, f32 value);

/**
 * @brief Gets the battery level of the given gamepad.
 * @param index The index of the gamepad.
 * @returns The battery level of the gamepad.
 */
ELSA_API f32 InputGetGamepadBattery(i32 index);

/**
 * @brief Sets the analog value of the given trigger.
 * @param index The gamepad index whose state to set.
 * @param value The analog value to set.
 * @param analog The analog position of the trigger.
 */
ELSA_API void InputProcessGamepadTrigger(i32 index, f32 value, GamepadAnalog analog);

/**
 * @brief Sets the analog values of the given joystick.
 * @param index The gamepad index whose state to set.
 * @param x The X value of the joystick.
 * @param y The Y value of the joystick.
 * @param analog The position of the joystick.
 */
ELSA_API void InputProcessGamepadJoystick(i32 index, f32 x, f32 y, GamepadAnalog analog);

#endif