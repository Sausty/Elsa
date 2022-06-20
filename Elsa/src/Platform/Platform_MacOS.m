#include "Platform.h"

#if defined(ELSA_PLATFORM_MACOS)

#include <Core/Logger.h>
#include <Core/Event.h>
#include <Core/Input.h>

#include <stdlib.h>

#include <Foundation/Foundation.h>
#include <Cocoa/Cocoa.h>
#include <QuartzCore/QuartzCore.h>

@class ApplicationDelegate;
@class WindowDelegate;
@class ContentView;

typedef struct PlatformState {
    ApplicationState* State;
    ApplicationDelegate* AppDelegate;
    WindowDelegate* WinDelegate;
    NSWindow* Window;
    ContentView* View;

    CAMetalLayer* Layer;

    b8 QuitFlagged;
} PlatformState;

static PlatformState platform_state;

Keys TranslateKeycode(u32 ns_keycode);

@interface WindowDelegate : NSObject <NSWindowDelegate> {
    PlatformState state;
}

- (instancetype)initWithState:(PlatformState)init_state;

@end

@implementation WindowDelegate

- (instancetype)initWithState:(PlatformState)init_state {
    self = [super init];

    if (self != nil) {
        state = init_state;
        platform_state.QuitFlagged = false;
    }

    return self;
}

- (BOOL)windowShouldClose:(id)sender {
    platform_state.QuitFlagged = true;

    Event event = {};
    EventFire(EVENT_CODE_APPLICATION_QUIT, 0, event);

    return YES;
}

- (void)windowDidResize:(NSNotification*)notification {
    Event event;
    const NSRect contentRect = [platform_state.View frame];
    const NSRect framebufferRect = [platform_state.View convertRectToBacking:contentRect];
    event.data.u16[0] = (u16)framebufferRect.size.width;
    event.data.u16[1] = (u16)framebufferRect.size.height;
    EventFire(EVENT_CODE_RESIZED, 0, event);
}

- (void)windowDidMiniaturize:(NSNotification*)notification {
    Event event;
    event.data.u16[0] = 0;
    event.data.u16[1] = 0;
    EventFire(EVENT_CODE_RESIZED, 0, event);

    [platform_state.Window miniaturize:nil];
}

- (void)windowDidDeminiaturize:(NSNotification*)notification {
    Event event;
    const NSRect contentRect = [platform_state.View frame];
    const NSRect framebufferRect = [platform_state.View convertRectToBacking:contentRect];
    event.data.u16[0] = (u16)framebufferRect.size.width;
    event.data.u16[1] = (u16)framebufferRect.size.height;
    EventFire(EVENT_CODE_RESIZED, 0, event);

    [platform_state.Window deminiaturize:nil];
}

@end

@interface ContentView : NSView<NSTextInputClient> {
    NSWindow* window;
    NSTrackingArea* trackingArea;
    NSMutableAttributedString* markedText;
}

- (instancetype)initWithWindow:(NSWindow*)initWindow;

@end

@implementation ContentView

- (instancetype)initWithWindow:(NSWindow*)initWindow {
    self = [super init];
    if (self != nil) {
        window = initWindow;
    }

    return self;
}

- (BOOL)canBecomeKeyView {
    return YES;
}

- (BOOL)acceptsFirstResponder {
    return YES;
}

- (BOOL)wantsUpdateLayer {
    return YES;
}

- (BOOL)acceptsFirstMouse:(NSEvent*)event {
    return YES;
}

- (void)mouseDown:(NSEvent*)event {
    InputProcessButton(BUTTON_LEFT, true);
}

- (void)mouseDragged:(NSEvent*)event {
    [self mouseMoved:event];
}

- (void)mouseUp:(NSEvent*)event {
    InputProcessButton(BUTTON_LEFT, false);
}

- (void)mouseMoved:(NSEvent*)event {
    const NSPoint pos = [event locationInWindow];

    InputProcessMouseMove((i16)pos.x, (i16)pos.y);
}

- (void)rightMouseDown:(NSEvent*)event {
    InputProcessButton(BUTTON_RIGHT, true);
}

- (void)rightMouseDragged:(NSEvent*)event {
    [self mouseMoved:event];
}

- (void)rightMouseUp:(NSEvent*)event {
    InputProcessButton(BUTTON_RIGHT, false);
}

- (void)otherMouseDown:(NSEvent*)event {
    InputProcessButton(BUTTON_MIDDLE, true);
}

- (void)otherMouseDragged:(NSEvent*)event {
    [self mouseMoved:event];
}

- (void)otherMouseUp:(NSEvent*)event {
    InputProcessButton(BUTTON_MIDDLE, false);
}

- (void)keyDown:(NSEvent*)event {
    Keys key = TranslateKeycode((u32)[event keyCode]);

    InputProcessKey(key, true);

    [self interpretKeyEvents:@[event]];
}

- (void)keyUp:(NSEvent*)event {
    Keys key = TranslateKeycode((u32)[event keyCode]);

    InputProcessKey(key, false);
}

- (void)scrollWheel:(NSEvent*)event {
    InputProcessMouseWheel((i8)[event scrollingDeltaY]);
}

- (void)insertText:(id)string replacementRange:(NSRange)replacementRange {
    return;
}

- (void)setMarkedText:(id)string selectedRange:(NSRange)selectedRanged replacementRange:(NSRange)replacementRange {
    return;
}

- (void)unmarkText {
    return;
}

static const NSRange kEmptyRange = { NSNotFound, 0 };

- (NSRange)selectedRange { 
    return kEmptyRange; 
}

- (NSRange)markedRange { 
    return kEmptyRange; 
}

- (BOOL)hasMarkedText { 
    return false; 
}

- (nullable NSAttributedString*)attributedSubstringForProposedRange:(NSRange)range actualRange:(nullable NSRangePointer)actualRange { 
    return nil; 
}

- (NSArray<NSAttributedStringKey>*)validAttributesForMarkedText { 
    return [NSArray array]; 
}

- (NSRect)firstRectForCharacterRange:(NSRange)range actualRange:(nullable NSRangePointer)actualRange { 
    return NSMakeRect(0, 0, 0, 0); 
}

- (NSUInteger)characterIndexForPoint:(NSPoint)point { 
    return 0; 
}

@end

@interface ApplicationDelegate : NSObject <NSApplicationDelegate> {}

@end

@implementation ApplicationDelegate

- (void)applicationDidFinishLaunching:(NSNotification*)notification {
    @autoreleasepool {
        NSEvent* event = [NSEvent otherEventWithType:NSEventTypeApplicationDefined
                                  location:NSMakePoint(0, 0)
                                  modifierFlags:0
                                  timestamp:0
                                  windowNumber:0
                                  context:nil
                                  subtype:0
                                  data1:0
                                  data2:0];

        [NSApp postEvent:event atStart: YES];
    }

    [NSApp stop:nil];
}

@end

b8 PlatformInit(ApplicationState* app_state)
{
    platform_state.State = app_state;

    @autoreleasepool {
        [NSApplication sharedApplication];

        platform_state.AppDelegate = [[ApplicationDelegate alloc] init];
        if (!platform_state.AppDelegate) {
            ELSA_FATAL("Failed to create application delegate!");
            return false;
        }
        [NSApp setDelegate:platform_state.AppDelegate];

        platform_state.WinDelegate = [[WindowDelegate alloc] initWithState:platform_state];
        if (!platform_state.WinDelegate) {
            ELSA_FATAL("Failed to create window delegate!");
            return false;
        }

        platform_state.Window = [[NSWindow alloc]
            initWithContentRect:NSMakeRect(app_state->PosX, app_state->PosY, app_state->Width, app_state->Height)
            styleMask:NSWindowStyleMaskMiniaturizable|NSWindowStyleMaskTitled|NSWindowStyleMaskClosable|NSWindowStyleMaskResizable
            backing:NSBackingStoreBuffered
            defer:NO];
        if (!platform_state.Window) {
            ELSA_FATAL("Failed to create window!");
            return false;
        }

        platform_state.Layer = [CAMetalLayer layer];
        if (!platform_state.Layer) {
            ELSA_FATAL("Failed to create Metal layer!");
            return false;
        }

        platform_state.View = [[ContentView alloc] initWithWindow:platform_state.Window];
        [platform_state.View setLayer:platform_state.Layer];
        [platform_state.View setWantsLayer:YES];

        [platform_state.Window setLevel:NSNormalWindowLevel];
        [platform_state.Window setContentView:platform_state.View];
        [platform_state.Window makeFirstResponder:platform_state.View];
        [platform_state.Window setTitle:@(app_state->Name)];
        [platform_state.Window setDelegate:platform_state.WinDelegate];
        [platform_state.Window setAcceptsMouseMovedEvents:YES];
        [platform_state.Window setRestorable:NO];

        if (![[NSRunningApplication currentApplication] isFinishedLaunching])
            [NSApp run];

        [NSApp setActivationPolicy:NSApplicationActivationPolicyRegular];

        [NSApp activateIgnoringOtherApps:YES];
        [platform_state.Window makeKeyAndOrderFront:nil];

        return true;
    }

   return true;
}

void PlatformExit()
{
    @autoreleasepool {
        if (platform_state.AppDelegate) {
            [NSApp setDelegate:nil];
            [platform_state.AppDelegate release];
        }

        if (platform_state.WinDelegate) {
            [platform_state.WinDelegate release];
        }

        if (platform_state.View) {
            [platform_state.View release];
        }
   }
}

void PlatformUpdateGamepads()
{
  
}

b8 PlatformPumpMessages()
{
    @autoreleasepool {
        NSEvent* event;

        for (;;) {
            event = [NSApp
                    nextEventMatchingMask:NSEventMaskAny
                    untilDate:[NSDate distantPast]
                    inMode:NSDefaultRunLoopMode
                    dequeue:YES];

            if (!event)
                break;

            [NSApp sendEvent:event];
        }

        return !platform_state.QuitFlagged;
    }

    return true;
}

void* PlatformAlloc(u64 size)
{
    return malloc(size);
}

void PlatformFree(void* block)
{
    free(block);
}

void PlatformZeroMemory(void* block, u64 size)
{
   memset(block, 0, size);
}

void PlatformSetMemory(void* block, i32 value, u64 size)
{
    memset(block, value, size);
}

void PlatformCopyMemory(void* dest, const void* source, u64 size)
{
    memcpy(dest, source, size);
}

void PlatformMoveMemory(void* dest, const void* source, u64 size)
{
    memmove(dest, source, size);
}

void PlatformConsoleWrite(const char* message, u8 colour)
{
    const char* colour_strings[] = {"0;41", "1;31", "1;33", "1;32", "1;34", "1;30"};
    printf("\033[%sm%s\033[0m", colour_strings[colour], message);
}

void PlatformConsoleWriteError(const char* message, u8 colour)
{
    const char* colour_strings[] = {"0;41", "1;31", "1;33", "1;32", "1;34", "1;30"};
    printf("\033[%sm%s\033[0m", colour_strings[colour], message);
}

Keys TranslateKeycode(u32 ns_keycode) { 
    switch (ns_keycode) {
        case 0x1D:
            return KEY_NUMPAD0;
        case 0x12:
            return KEY_NUMPAD1;
        case 0x13:
            return KEY_NUMPAD2;
        case 0x14:
            return KEY_NUMPAD3;
        case 0x15:
            return KEY_NUMPAD4;
        case 0x17:
            return KEY_NUMPAD5;
        case 0x16:
            return KEY_NUMPAD6;
        case 0x1A:
            return KEY_NUMPAD7;
        case 0x1C:
            return KEY_NUMPAD8;
        case 0x19:
            return KEY_NUMPAD9;

        case 0x00:
            return KEY_A;
        case 0x0B:
            return KEY_B;
        case 0x08:
            return KEY_C;
        case 0x02:
            return KEY_D;
        case 0x0E:
            return KEY_E;
        case 0x03:
            return KEY_F;
        case 0x05:
            return KEY_G;
        case 0x04:
            return KEY_H;
        case 0x22:
            return KEY_I;
        case 0x26:
            return KEY_J;
        case 0x28:
            return KEY_K;
        case 0x25:
            return KEY_L;
        case 0x2E:
            return KEY_M;
        case 0x2D:
            return KEY_N;
        case 0x1F:
            return KEY_O;
        case 0x23:
            return KEY_P;
        case 0x0C:
            return KEY_Q;
        case 0x0F:
            return KEY_R;
        case 0x01:
            return KEY_S;
        case 0x11:
            return KEY_T;
        case 0x20:
            return KEY_U;
        case 0x09:
            return KEY_V;
        case 0x0D:
            return KEY_W;
        case 0x07:
            return KEY_X;
        case 0x10:
            return KEY_Y;
        case 0x06:
            return KEY_Z;

        case 0x27:
            return KEYS_MAX_KEYS; // Apostrophe
        case 0x2A:
            return KEYS_MAX_KEYS; // Backslash
        case 0x2B:
            return KEY_COMMA;
        case 0x18:
            return KEYS_MAX_KEYS; // Equal
        case 0x32:
            return KEY_GRAVE;
        case 0x21:
            return KEYS_MAX_KEYS; // Left bracket
        case 0x1B:
            return KEY_MINUS;
        case 0x2F:
            return KEY_PERIOD;
        case 0x1E:
            return KEYS_MAX_KEYS; // Right bracket
        case 0x29:
            return KEY_SEMICOLON;
        case 0x2C:
            return KEY_SLASH;
        case 0x0A:
            return KEYS_MAX_KEYS; // ?

        case 0x33:
            return KEY_BACKSPACE;
        case 0x39:
            return KEY_CAPITAL;
        case 0x75:
            return KEY_DELETE;
        case 0x7D:
            return KEY_DOWN;
        case 0x77:
            return KEY_END;
        case 0x24:
            return KEY_ENTER;
        case 0x35:
            return KEY_ESCAPE;
        case 0x7A:
            return KEY_F1;
        case 0x78:
            return KEY_F2;
        case 0x63:
            return KEY_F3;
        case 0x76:
            return KEY_F4;
        case 0x60:
            return KEY_F5;
        case 0x61:
            return KEY_F6;
        case 0x62:
            return KEY_F7;
        case 0x64:
            return KEY_F8;
        case 0x65:
            return KEY_F9;
        case 0x6D:
            return KEY_F10;
        case 0x67:
            return KEY_F11;
        case 0x6F:
            return KEY_F12;
        case 0x69:
            return KEY_PRINT;
        case 0x6B:
            return KEY_F14;
        case 0x71:
            return KEY_F15;
        case 0x6A:
            return KEY_F16;
        case 0x40:
            return KEY_F17;
        case 0x4F:
            return KEY_F18;
        case 0x50:
            return KEY_F19;
        case 0x5A:
            return KEY_F20;
        case 0x73:
            return KEY_HOME;
        case 0x72:
            return KEY_INSERT;
        case 0x7B:
            return KEY_LEFT;
        case 0x3A:
            return KEY_LALT;
        case 0x3B:
            return KEY_LCONTROL;
        case 0x38:
            return KEY_LSHIFT;
        case 0x37:
            return KEY_LWIN;
        case 0x6E:
            return KEYS_MAX_KEYS; // Menu
        case 0x47:
            return KEY_NUMLOCK;
        case 0x79:
            return KEYS_MAX_KEYS; // Page down
        case 0x74:
            return KEYS_MAX_KEYS; // Page up
        case 0x7C:
            return KEY_RIGHT;
        case 0x3D:
            return KEY_RALT;
        case 0x3E:
            return KEY_RCONTROL;
        case 0x3C:
            return KEY_RSHIFT;
        case 0x36:
            return KEY_RWIN;
        case 0x31:
            return KEY_SPACE;
        case 0x30:
            return KEY_TAB;
        case 0x7E:
            return KEY_UP;

        case 0x52:
            return KEY_NUMPAD0;
        case 0x53:
            return KEY_NUMPAD1;
        case 0x54:
            return KEY_NUMPAD2;
        case 0x55:
            return KEY_NUMPAD3;
        case 0x56:
            return KEY_NUMPAD4;
        case 0x57:
            return KEY_NUMPAD5;
        case 0x58:
            return KEY_NUMPAD6;
        case 0x59:
            return KEY_NUMPAD7;
        case 0x5B:
            return KEY_NUMPAD8;
        case 0x5C:
            return KEY_NUMPAD9;
        case 0x45:
            return KEY_ADD;
        case 0x41:
            return KEY_DECIMAL;
        case 0x4B:
            return KEY_DIVIDE;
        case 0x4C:
            return KEY_ENTER;
        case 0x51:
            return KEY_NUMPAD_EQUAL;
        case 0x43:
            return KEY_MULTIPLY;
        case 0x4E:
            return KEY_SUBTRACT;

        default:
            return KEYS_MAX_KEYS;
    }
}

#endif