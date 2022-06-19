#include "Event.h"

#include <Containers/Darray.h>
#include <Platform/Platform.h>
#include <Core/Logger.h>

typedef struct RegisteredEvent {
    void* Listener;
    PFN_OnEvent Callback;
} RegisteredEvent;

typedef struct EventCodeEntry {
    RegisteredEvent* Events;
} EventCodeEntry;

#define MAX_MESSAGE_CODES 16384

typedef struct EventSystemState {
    EventCodeEntry Registered[MAX_MESSAGE_CODES];
} EventSystemState;

static EventSystemState state;

void EventSystemInit()
{
    PlatformZeroMemory(&state, sizeof(EventSystemState));
}

void EventSystemExit()
{
    for (u16 i = 0; i < MAX_MESSAGE_CODES; i++) {
        if (state.Registered[i].Events != 0) {
            Darray_Destroy(state.Registered[i].Events);
            state.Registered[i].Events = 0;
        }
    }
}

b8 EventRegister(u16 code, void* listener, PFN_OnEvent on_event)
{
    if (state.Registered[code].Events == 0) {
        state.Registered[code].Events = Darray_Create(RegisteredEvent);
    }

    u64 registered_count = Darray_Length(state.Registered[code].Events);
    for (u64 i = 0; i < registered_count; i++) {
        if (state.Registered[code].Events[i].Listener == listener) {
            ELSA_WARN("Trying to register an event listener that is already registered! (Code: %u)", code);
            return false;
        }
    }

    RegisteredEvent event;
    event.Listener = listener;
    event.Callback = on_event;
    Darray_Push(state.Registered[code].Events, event);
    
    return true;
}

b8 EventUnregister(u16 code, void* listener, PFN_OnEvent on_event)
{
    if (state.Registered[code].Events == 0) {
        ELSA_WARN("Trying to unregister an event listener that isn't registered! (Code: %u)", code);
        return false;
    }

    u64 registered_count = Darray_Length(state.Registered[code].Events);
    for (u64 i = 0; i < registered_count; i++) {
        RegisteredEvent e = state.Registered[code].Events[i];
        if (e.Listener == listener && e.Callback == on_event) {
            RegisteredEvent popped_event;
            Darray_PopAt(state.Registered[code].Events, i, &popped_event);
            return true;
        }
    }

    return false;
}

b8 EventFire(u16 code, void* sender, Event data)
{
    if (state.Registered[code].Events == 0) {
        return false;
    }

    u64 registered_count = Darray_Length(state.Registered[code].Events);
    for (u64 i = 0; i < registered_count; i++) {
        RegisteredEvent e = state.Registered[code].Events[i];
        if (e.Callback(code, sender, e.Listener, data)) {
            return true;
        }
    }

    return false;
}