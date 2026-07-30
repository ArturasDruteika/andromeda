#ifndef WINDOW__MOUSE_EVENTS__HPP
#define WINDOW__MOUSE_EVENTS__HPP


#include "event_base.hpp"
#include "andromeda/window/events/event_type.hpp"
#include "andromeda/window/mouse_and_key_codes/mouse_codes.hpp"
#include "andromeda/window/events/i_mouse_events.hpp"
#include "pch.hpp"


namespace andromeda::window
{
    class MouseMovedEvent
        : public EventBase
        , public virtual IMouseMovedEvent
    {
    public:
        MouseMovedEvent(float x, float y);
        ~MouseMovedEvent() override = default;

        float get_x() const override;
        float get_y() const override;

        bool is_in_category(EventCategory category) const override;
        int get_category_flags() const override;
        std::string get_name() const override;
        std::string to_string() const override;
        EventType get_event_type() const override;

    private:
        float m_x;
        float m_y;
    };

    class MouseScrolledEvent
        : public EventBase
        , public virtual IMouseScrolledEvent
    {
    public:
        MouseScrolledEvent(float x_offset, float y_offset);
        ~MouseScrolledEvent() override = default;

        float get_x_offset() const override;
        float get_y_offset() const override;

        bool is_in_category(EventCategory category) const override;
        int get_category_flags() const override;
        std::string get_name() const override;
        std::string to_string() const override;
        EventType get_event_type() const override;

    private:
        float m_x_offset;
        float m_y_offset;
    };

    class MouseButtonEvent
        : public EventBase
        , public virtual IMouseButtonEvent
    {
    public:
        explicit MouseButtonEvent(MouseCode button);
        ~MouseButtonEvent() override = default;

        MouseCode get_mouse_button() const override;

        bool is_in_category(EventCategory category) const override;
        int get_category_flags() const override;

    protected:
        MouseCode m_button;
    };

    class MouseButtonPressedEvent
        : public MouseButtonEvent
        , public virtual IMouseButtonPressedEvent
    {
    public:
        explicit MouseButtonPressedEvent(MouseCode button);
        ~MouseButtonPressedEvent() override = default;

        std::string get_name() const override;
        std::string to_string() const override;
        EventType get_event_type() const override;
    };

    class MouseButtonReleasedEvent
        : public MouseButtonEvent
        , public virtual IMouseButtonReleasedEvent
    {
    public:
        explicit MouseButtonReleasedEvent(MouseCode button);
        ~MouseButtonReleasedEvent() override = default;

        std::string get_name() const override;
        std::string to_string() const override;
        EventType get_event_type() const override;
    };
}


#endif // WINDOW__MOUSE_EVENTS__HPP