#ifndef WINDOW__FRAMEBUFFER_EVENTS__HPP
#define WINDOW__FRAMEBUFFER_EVENTS__HPP


#include "EventBase.hpp"
#include "andromeda/window/events/event_type.hpp"
#include "andromeda/window/events/i_frame_buffer_events.hpp"

#include <string>


namespace andromeda::Window
{
    class WindowResizeEvent
        : public EventBase
        , public virtual andromeda::IWindowResizeEvent
    {
    public:
        WindowResizeEvent(int width, int height);
        ~WindowResizeEvent() override;

        int GetWidth() const override;
        int GetHeight() const override;

        bool IsInCategory(EventCategory category) override;
        int GetCategoryFlags() const override;
        std::string GetName() const override;
        std::string ToString() const override;
        EventType GetEventType() const override;

    private:
        int m_width;
        int m_height;
    };

    class WindowCloseEvent
        : public EventBase
        , public virtual andromeda::IWindowCloseEvent
    {
    public:
        WindowCloseEvent();
        ~WindowCloseEvent() override;

        bool IsInCategory(EventCategory category) override;
        int GetCategoryFlags() const override;
        std::string GetName() const override;
        std::string ToString() const override;
        EventType GetEventType() const override;
    };

    class FramebufferResizeEvent
        : public EventBase
        , public virtual andromeda::IFramebufferResizeEvent
    {
    public:
        FramebufferResizeEvent(int width, int height);
        ~FramebufferResizeEvent() override;

        int GetWidth() const override;
        int GetHeight() const override;

        bool IsInCategory(EventCategory category) override;
        int GetCategoryFlags() const override;
        std::string GetName() const override;
        std::string ToString() const override;
        EventType GetEventType() const override;

    private:
        int m_width;
        int m_height;
    };
}

#endif // WINDOW__FRAMEBUFFER_EVENTS__HPP
