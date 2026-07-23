#include "../include/FrameBufferEvents.hpp"
#include <sstream>


namespace andromeda::Window
{
    // WindowResizeEvent

    WindowResizeEvent::WindowResizeEvent(int width, int height)
        : m_width{ width }
        , m_height{ height }
    {
    }

    WindowResizeEvent::~WindowResizeEvent() = default;

    int WindowResizeEvent::GetWidth() const
    {
        return m_width;
    }

    int WindowResizeEvent::GetHeight() const
    {
        return m_height;
    }

    bool WindowResizeEvent::IsInCategory(andromeda::EventCategory category)
    {
        return (GetCategoryFlags() & category) != 0;
    }

    int WindowResizeEvent::GetCategoryFlags() const
    {
        return andromeda::EventCategoryApplication;
    }

    std::string WindowResizeEvent::GetName() const
    {
        return "WindowResize";
    }

    std::string WindowResizeEvent::ToString() const
    {
        std::stringstream ss;
        ss << "WindowResizeEvent: " << m_width << "x" << m_height;
        return ss.str();
    }

    andromeda::EventType WindowResizeEvent::GetEventType() const
    {
        return andromeda::EventType::WindowResize;
    }

    // WindowCloseEvent

    WindowCloseEvent::WindowCloseEvent() = default;

    WindowCloseEvent::~WindowCloseEvent() = default;

    bool WindowCloseEvent::IsInCategory(andromeda::EventCategory category)
    {
        return (GetCategoryFlags() & category) != 0;
    }

    int WindowCloseEvent::GetCategoryFlags() const
    {
        return andromeda::EventCategoryApplication;
    }

    std::string WindowCloseEvent::GetName() const
    {
        return "WindowClose";
    }

    std::string WindowCloseEvent::ToString() const
    {
        return "WindowCloseEvent";
    }

    andromeda::EventType WindowCloseEvent::GetEventType() const
    {
        return andromeda::EventType::WindowClose;
    }

    // FramebufferResizeEvent

    FramebufferResizeEvent::FramebufferResizeEvent(int width, int height)
        : m_width{ width }
        , m_height{ height }
    {
    }

    FramebufferResizeEvent::~FramebufferResizeEvent() = default;

    int FramebufferResizeEvent::GetWidth() const
    {
        return m_width;
    }

    int FramebufferResizeEvent::GetHeight() const
    {
        return m_height;
    }

    bool FramebufferResizeEvent::IsInCategory(andromeda::EventCategory category)
    {
        return (GetCategoryFlags() & category) != 0;
    }

    int FramebufferResizeEvent::GetCategoryFlags() const
    {
        return andromeda::EventCategoryApplication;
    }

    std::string FramebufferResizeEvent::GetName() const
    {
        return "FramebufferResize";
    }

    std::string FramebufferResizeEvent::ToString() const
    {
        std::stringstream ss;
        ss << "FramebufferResizeEvent: " << m_width << "x" << m_height;
        return ss.str();
    }

    EventType FramebufferResizeEvent::GetEventType() const
    {
        return EventType::WindowResize;
    }
}
