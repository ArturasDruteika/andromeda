#ifndef API__WINDOW__EVENTS__I_MOUSE_EVENTS_HPP
#define API__WINDOW__EVENTS__I_MOUSE_EVENTS_HPP


#include "i_event.hpp"
#include "../mouse_and_key_codes/mouse_codes.hpp"


namespace andromeda
{
    class IMouseMovedEvent
        : public virtual IEvent
    {
    public:
        virtual ~IMouseMovedEvent() = default;
        virtual float get_x() const = 0;
        virtual float get_y() const = 0;
    };

    class IMouseScrolledEvent
        : public virtual IEvent
    {
    public:
        virtual ~IMouseScrolledEvent() = default;

        // You already use Y in engine for zoom; keep this.
        virtual float get_y_offset() const = 0;

        // Optional but useful for completeness; you already store it in Window.
        virtual float get_x_offset() const = 0;
    };

    class IMouseButtonEvent
        : public virtual IEvent
    {
    public:
        virtual ~IMouseButtonEvent() = default;
        virtual MouseCode get_mouse_button() const = 0;
    };

    class IMouseButtonPressedEvent
        : public virtual IMouseButtonEvent
    {
    public:
        virtual ~IMouseButtonPressedEvent() = default;
    };

    class IMouseButtonReleasedEvent
        : public virtual IMouseButtonEvent
    {
    public:
        virtual ~IMouseButtonReleasedEvent() = default;
    };
}

#endif // API__WINDOW__EVENTS__I_MOUSE_EVENTS_HPP