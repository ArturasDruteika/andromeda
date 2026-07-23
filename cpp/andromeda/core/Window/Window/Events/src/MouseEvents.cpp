#include "../include/MouseEvents.hpp"
#include <sstream>


namespace andromeda::Window
{
    // MouseMovedEvent

    MouseMovedEvent::MouseMovedEvent(float x, float y)
        : m_x{ x }
        , m_y{ y }
    {
    }

    float MouseMovedEvent::GetX() const
    {
        return m_x;
    }

    float MouseMovedEvent::GetY() const
    {
        return m_y;
    }

    bool MouseMovedEvent::IsInCategory(andromeda::EventCategory category)
    {
        return (GetCategoryFlags() & category) != 0;
    }

    int MouseMovedEvent::GetCategoryFlags() const
    {
        return andromeda::EventCategoryMouse |
            andromeda::EventCategoryInput;
    }

    std::string MouseMovedEvent::GetName() const
    {
        return "MouseMoved";
    }

    std::string MouseMovedEvent::ToString() const
    {
        std::stringstream ss;
        ss << "MouseMovedEvent: " << m_x << ", " << m_y;
        return ss.str();
    }

    andromeda::EventType MouseMovedEvent::GetEventType() const
    {
        return andromeda::EventType::MouseMoved;
    }

    // MouseScrolledEvent

    MouseScrolledEvent::MouseScrolledEvent(float xOffset, float yOffset)
        : m_xOffset{ xOffset }
        , m_yOffset{ yOffset }
    {
    }

    float MouseScrolledEvent::GetXOffset() const
    {
        return m_xOffset;
    }

    float MouseScrolledEvent::GetYOffset() const
    {
        return m_yOffset;
    }

    bool MouseScrolledEvent::IsInCategory(andromeda::EventCategory category)
    {
        return (GetCategoryFlags() & category) != 0;
    }

    int MouseScrolledEvent::GetCategoryFlags() const
    {
        return andromeda::EventCategoryMouse |
            andromeda::EventCategoryInput;
    }

    std::string MouseScrolledEvent::GetName() const
    {
        return "MouseScrolled";
    }

    std::string MouseScrolledEvent::ToString() const
    {
        std::stringstream ss;
        ss << "MouseScrolledEvent: " << m_xOffset << ", " << m_yOffset;
        return ss.str();
    }

    andromeda::EventType MouseScrolledEvent::GetEventType() const
    {
        return andromeda::EventType::MouseScrolled;
    }

    // MouseButtonEvent

    MouseButtonEvent::MouseButtonEvent(andromeda::MouseCode button)
        : m_button{ button }
    {
    }

    andromeda::MouseCode MouseButtonEvent::GetMouseButton() const
    {
        return m_button;
    }

    bool MouseButtonEvent::IsInCategory(andromeda::EventCategory category)
    {
        return (GetCategoryFlags() & category) != 0;
    }

    int MouseButtonEvent::GetCategoryFlags() const
    {
        return andromeda::EventCategoryMouse |
            andromeda::EventCategoryInput |
            andromeda::EventCategoryMouseButton;
    }

    // MouseButtonPressedEvent

    MouseButtonPressedEvent::MouseButtonPressedEvent(andromeda::MouseCode button)
        : MouseButtonEvent{ button }
    {
    }

    std::string MouseButtonPressedEvent::GetName() const
    {
        return "MouseButtonPressed";
    }

    std::string MouseButtonPressedEvent::ToString() const
    {
        std::stringstream ss;
        ss << "MouseButtonPressedEvent: " << static_cast<int>(m_button);
        return ss.str();
    }

    andromeda::EventType MouseButtonPressedEvent::GetEventType() const
    {
        return andromeda::EventType::MouseButtonPressed;
    }

    // MouseButtonReleasedEvent

    MouseButtonReleasedEvent::MouseButtonReleasedEvent(andromeda::MouseCode button)
        : MouseButtonEvent{ button }
    {
    }

    std::string MouseButtonReleasedEvent::GetName() const
    {
        return "MouseButtonReleased";
    }

    std::string MouseButtonReleasedEvent::ToString() const
    {
        std::stringstream ss;
        ss << "MouseButtonReleasedEvent: " << static_cast<int>(m_button);
        return ss.str();
    }

    andromeda::EventType MouseButtonReleasedEvent::GetEventType() const
    {
        return andromeda::EventType::MouseButtonReleased;
    }
}
