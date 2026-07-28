#ifndef API__WINDOW__EVENTS__I_KEY_EVENTS_HPP
#define API__WINDOW__EVENTS__I_KEY_EVENTS_HPP


#include "i_event.hpp"
#include "../mouse_and_key_codes/key_codes.hpp"


namespace andromeda
{
    // Base interface for all key-related events
    class IKeyEvent
        : public virtual IEvent
    {
    public:
        virtual ~IKeyEvent() = default;
        virtual KeyCode get_key_code() const = 0;
    };

    // Key pressed (may repeat)
    class IKeyPressedEvent
        : public virtual IKeyEvent
    {
    public:
        virtual ~IKeyPressedEvent() = default;
        virtual bool is_repeat() const = 0;
    };

    // Key released
    class IKeyReleasedEvent
        : public virtual IKeyEvent
    {
    public:
        virtual ~IKeyReleasedEvent() = default;
    };

    // Key typed (character input)
    class IKeyTypedEvent
        : public virtual IKeyEvent
    {
    public:
        virtual ~IKeyTypedEvent() = default;
    };
}

#endif // API__WINDOW__EVENTS__I_KEY_EVENTS_HPP