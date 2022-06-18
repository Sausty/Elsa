/**
 * @file Event.h
 * @author Milo Heinrich (MikuoH15TH@gmail.com)
 * @brief This file contains structures and logic pertaining to the event system.
 * @version 1.0
 * @date 2022-06-17
 */
#ifndef ELSA_EVENT_H
#define ELSA_EVENT_H

#include <Defines.h>

/**
 * @brief Represents event contextual data to be sent along with an
 * event code when an event is fired.
 * It is a union that is 128 bits in size, meaning data can be mixed
 * and matched as required by the developer.
 * */
typedef struct Event {
    // 128 bytes
    union {
         /** @brief An array of 2 64-bit signed integers. */
        i64 i64[2];
        /** @brief An array of 2 64-bit unsigned integers. */
        u64 u64[2];

        /** @brief An array of 2 64-bit floating-point numbers. */
        f64 f64[2];

        /** @brief An array of 4 32-bit signed integers. */
        i32 i32[4];
        /** @brief An array of 4 32-bit unsigned integers. */
        u32 u32[4];
        /** @brief An array of 4 32-bit floating-point numbers. */
        f32 f32[4];

        /** @brief An array of 8 16-bit signed integers. */
        i16 i16[8];

        /** @brief An array of 8 16-bit unsigned integers. */
        u16 u16[8];

        /** @brief An array of 16 8-bit signed integers. */
        i8 i8[16];
        /** @brief An array of 16 8-bit unsigned integers. */
        u8 u8[16];

        /** @brief An array of 16 characters. */
        char c[16];
    } data;
} Event;

/**
 * @brief A function pointer typedef which is used for event subscriptions by the subscriber.
 * @param code The event code to be sent.
 * @param sender A pointer to the sender of the event. Can be 0.
 * @param listener_inst A pointer to the listener of the event. Can be 0.
 * @param data The event context to be passed with the fired event.
 * @returns True if the message should be considered handled, which means that it will not
 * be sent to any other consumers; otherwise false.
 */
typedef b8 (*PFN_OnEvent)(u16 code, void* sender, void* listener_inst, Event data);

/**
 * @brief Initializes the event system.
 */
ELSA_API void EventSystemInit();

/**
 * @brief Shuts the event system down.
 */
ELSA_API void EventSystemExit();

/**
 * @brief Register to listen for when events are sent with the provided code. Events with duplicate
 * listener/callback combos will not be registered again and will cause this to return false.
 * @param code The event code to listen for.
 * @param listener A pointer to a listener instance. Can be 0/NULL.
 * @param on_event The callback function pointer to be invoked when the event code is fired.
 * @returns True if the event is successfully registered; otherwise false.
 */
ELSA_API b8 EventRegister(u16 code, void* listener, PFN_OnEvent on_event);

/**
 * @brief Unregister from listening for when events are sent with the provided code. If no matching
 * registration is found, this function returns false.
 * @param code The event code to stop listening for.
 * @param listener A pointer to a listener instance. Can be 0/NULL.
 * @param on_event The callback function pointer to be unregistered.
 * @returns True if the event is successfully unregistered; otherwise false.
 */
ELSA_API b8 EventUnregister(u16 code, void* listener, PFN_OnEvent on_event);

/**
 * @brief Fires an event to listeners of the given code. If an event handler returns 
 * true, the event is considered handled and is not passed on to any more listeners.
 * @param code The event code to fire.
 * @param sender A pointer to the sender. Can be 0/NULL.
 * @param data The event data.
 * @returns True if handled, otherwise false.
 */
ELSA_API b8 EventFire(u16 code, void* sender, Event data);

typedef enum EventCode {
     /** @brief Shuts the application down on the next frame. */
    EVENT_CODE_APPLICATION_QUIT = 0x01,

    /** @brief Keyboard key pressed.
     * Context usage:
     * u16 key_code = data.data.u16[0];
     */
    EVENT_CODE_KEY_PRESSED = 0x02,

    /** @brief Keyboard key released.
     * Context usage:
     * u16 key_code = data.data.u16[0];
     */
    EVENT_CODE_KEY_RELEASED = 0x03,

    /** @brief Mouse button pressed.
     * Context usage:
     * u16 button = data.data.u16[0];
     */
    EVENT_CODE_BUTTON_PRESSED = 0x04,

    /** @brief Mouse button released.
     * Context usage:
     * u16 button = data.data.u16[0];
     */
    EVENT_CODE_BUTTON_RELEASED = 0x05,

    /** @brief Mouse moved.
     * Context usage:
     * u16 x = data.data.u16[0];
     * u16 y = data.data.u16[1];
     */
    EVENT_CODE_MOUSE_MOVED = 0x06,

    /** @brief Mouse moved.
     * Context usage:
     * u8 z_delta = data.data.u8[0];
     */
    EVENT_CODE_MOUSE_WHEEL = 0x07,

    /** @brief Resized/resolution changed from the OS.
     * Context usage:
     * u16 width = data.data.u16[0];
     * u16 height = data.data.u16[1];
     */
    EVENT_CODE_RESIZED = 0x08,

    /** @brief The maximum event code that can be used internally. */
    MAX_EVENT_CODE = 0xFF
} EventCode;

#endif