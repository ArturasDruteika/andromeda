#include "../include/frame_buffer_events.hpp"
#include <sstream>


namespace andromeda::window
{
    // WindowResizeEvent

    WindowResizeEvent::WindowResizeEvent(int width, int height)
        : m_width{ width }
        , m_height{ height }
    {
    }

    WindowResizeEvent::~WindowResizeEvent() = default;

    int WindowResizeEvent::get_width() const
    {
        return m_width;
    }

    int WindowResizeEvent::get_height() const
    {
        return m_height;
    }

    bool WindowResizeEvent::is_in_category(EventCategory category) const
    {
        return (get_category_flags() & category) != 0;
    }

    int WindowResizeEvent::get_category_flags() const
    {
        return EventCategoryApplication;
    }

    std::string WindowResizeEvent::get_name() const
    {
        return "WindowResize";
    }

    std::string WindowResizeEvent::to_string() const
    {
        std::stringstream ss;
        ss << "WindowResizeEvent: " << m_width << "x" << m_height;
        return ss.str();
    }

    EventType WindowResizeEvent::get_event_type() const
    {
        return EventType::WindowResize;
    }

    // WindowCloseEvent

    WindowCloseEvent::WindowCloseEvent() = default;

    WindowCloseEvent::~WindowCloseEvent() = default;

    bool WindowCloseEvent::is_in_category(EventCategory category) const
    {
        return (get_category_flags() & category) != 0;
    }

    int WindowCloseEvent::get_category_flags() const
    {
        return EventCategoryApplication;
    }

    std::string WindowCloseEvent::get_name() const
    {
        return "WindowClose";
    }

    std::string WindowCloseEvent::to_string() const
    {
        return "WindowCloseEvent";
    }

    EventType WindowCloseEvent::get_event_type() const
    {
        return EventType::WindowClose;
    }

    // FramebufferResizeEvent

    FramebufferResizeEvent::FramebufferResizeEvent(int width, int height)
        : m_width{ width }
        , m_height{ height }
    {
    }

    FramebufferResizeEvent::~FramebufferResizeEvent() = default;

    int FramebufferResizeEvent::get_width() const
    {
        return m_width;
    }

    int FramebufferResizeEvent::get_height() const
    {
        return m_height;
    }

    bool FramebufferResizeEvent::is_in_category(EventCategory category) const
    {
        return (get_category_flags() & category) != 0;
    }

    int FramebufferResizeEvent::get_category_flags() const
    {
        return EventCategoryApplication;
    }

    std::string FramebufferResizeEvent::get_name() const
    {
        return "FramebufferResize";
    }

    std::string FramebufferResizeEvent::to_string() const
    {
        std::stringstream ss;
        ss << "FramebufferResizeEvent: " << m_width << "x" << m_height;
        return ss.str();
    }

    EventType FramebufferResizeEvent::get_event_type() const
    {
        return EventType::WindowResize;
    }
}