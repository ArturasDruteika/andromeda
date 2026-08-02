#include "../include/mouse_events.hpp"
#include <sstream>


namespace andromeda::window
{
    // MouseMovedEvent

    MouseMovedEvent::MouseMovedEvent(float x, float y)
        : m_x{ x }
        , m_y{ y }
    {
    }

    float MouseMovedEvent::get_x() const
    {
        return m_x;
    }

    float MouseMovedEvent::get_y() const
    {
        return m_y;
    }

    bool MouseMovedEvent::is_in_category(EventCategory category) const
    {
        return (get_category_flags() & category) != 0;
    }

    int MouseMovedEvent::get_category_flags() const
    {
        return EventCategoryMouse |
            EventCategoryInput;
    }

    std::string MouseMovedEvent::get_name() const
    {
        return "MouseMoved";
    }

    std::string MouseMovedEvent::to_string() const
    {
        std::stringstream ss;
        ss << "MouseMovedEvent: " << m_x << ", " << m_y;
        return ss.str();
    }

    EventType MouseMovedEvent::get_event_type() const
    {
        return EventType::MouseMoved;
    }

    // MouseScrolledEvent

    MouseScrolledEvent::MouseScrolledEvent(float x_offset, float y_offset)
        : m_x_offset{ x_offset }
        , m_y_offset{ y_offset }
    {
    }

    float MouseScrolledEvent::get_x_offset() const
    {
        return m_x_offset;
    }

    float MouseScrolledEvent::get_y_offset() const
    {
        return m_y_offset;
    }

    bool MouseScrolledEvent::is_in_category(EventCategory category) const
    {
        return (get_category_flags() & category) != 0;
    }

    int MouseScrolledEvent::get_category_flags() const
    {
        return EventCategoryMouse |
            EventCategoryInput;
    }

    std::string MouseScrolledEvent::get_name() const
    {
        return "MouseScrolled";
    }

    std::string MouseScrolledEvent::to_string() const
    {
        std::stringstream ss;
        ss << "MouseScrolledEvent: " << m_x_offset << ", " << m_y_offset;
        return ss.str();
    }

    EventType MouseScrolledEvent::get_event_type() const
    {
        return EventType::MouseScrolled;
    }

    // MouseButtonEvent

    MouseButtonEvent::MouseButtonEvent(MouseCode button)
        : m_button{ button }
    {
    }

    MouseCode MouseButtonEvent::get_mouse_button() const
    {
        return m_button;
    }

    bool MouseButtonEvent::is_in_category(EventCategory category) const
    {
        return (get_category_flags() & category) != 0;
    }

    int MouseButtonEvent::get_category_flags() const
    {
        return EventCategoryMouse |
            EventCategoryInput |
            EventCategoryMouseButton;
    }

    // MouseButtonPressedEvent

    MouseButtonPressedEvent::MouseButtonPressedEvent(MouseCode button)
        : MouseButtonEvent{ button }
    {
    }

    std::string MouseButtonPressedEvent::get_name() const
    {
        return "MouseButtonPressed";
    }

    std::string MouseButtonPressedEvent::to_string() const
    {
        std::stringstream ss;
        ss << "MouseButtonPressedEvent: " << static_cast<int>(m_button);
        return ss.str();
    }

    EventType MouseButtonPressedEvent::get_event_type() const
    {
        return EventType::MouseButtonPressed;
    }

    // MouseButtonReleasedEvent

    MouseButtonReleasedEvent::MouseButtonReleasedEvent(MouseCode button)
        : MouseButtonEvent{ button }
    {
    }

    std::string MouseButtonReleasedEvent::get_name() const
    {
        return "MouseButtonReleased";
    }

    std::string MouseButtonReleasedEvent::to_string() const
    {
        std::stringstream ss;
        ss << "MouseButtonReleasedEvent: " << static_cast<int>(m_button);
        return ss.str();
    }

    EventType MouseButtonReleasedEvent::get_event_type() const
    {
        return EventType::MouseButtonReleased;
    }
}