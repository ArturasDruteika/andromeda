#ifndef WINDOW__FRAMEBUFFER_EVENTS__HPP
#define WINDOW__FRAMEBUFFER_EVENTS__HPP


#include "event_base.hpp"
#include "andromeda/window/events/event_type.hpp"
#include "andromeda/window/events/i_frame_buffer_events.hpp"

#include <string>


namespace andromeda::window
{
    class WindowResizeEvent
        : public EventBase
        , public virtual IWindowResizeEvent
    {
    public:
        WindowResizeEvent(int width, int height);
        ~WindowResizeEvent() override;

        int get_width() const override;
        int get_height() const override;

        bool is_in_category(EventCategory category) override;
        int get_category_flags() const override;
        std::string get_name() const override;
        std::string to_string() const override;
        EventType get_event_type() const override;

    private:
        int m_width;
        int m_height;
    };

    class WindowCloseEvent
        : public EventBase
        , public virtual IWindowCloseEvent
    {
    public:
        WindowCloseEvent();
        ~WindowCloseEvent() override;

        bool is_in_category(EventCategory category) override;
        int get_category_flags() const override;
        std::string get_name() const override;
        std::string to_string() const override;
        EventType get_event_type() const override;
    };

    class FramebufferResizeEvent
        : public EventBase
        , public virtual IFramebufferResizeEvent
    {
    public:
        FramebufferResizeEvent(int width, int height);
        ~FramebufferResizeEvent() override;

        int get_width() const override;
        int get_height() const override;

        bool is_in_category(EventCategory category) override;
        int get_category_flags() const override;
        std::string get_name() const override;
        std::string to_string() const override;
        EventType get_event_type() const override;

    private:
        int m_width;
        int m_height;
    };
}


#endif // WINDOW__FRAMEBUFFER_EVENTS__HPP